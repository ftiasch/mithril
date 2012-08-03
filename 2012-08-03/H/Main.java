import java.util.*;
import java.io.*;
import java.math.*;

class Rational implements Comparable<Rational> {

    long p, q;

    private static long gcd(long a, long b) {
        while (b > 0) {
            long r = a % b;
            a = b;
            b = r;
        }
        return a;
    }

    Rational(long p, long q) {
        long g = gcd(Math.abs(p), Math.abs(q));
        p = p / g;
        q = q / g;
        if (q == 0) {
            throw new RuntimeException("divided by zero");
        }
        if (q < 0) {
            this.p = -p;
            this.q = -q;
        } else {
            this.p = p;
            this.q = q;
        }
    }
    
    Rational(long p) {
        this.p = p;
        this.q = 1;
    }

    static Rational valueOf(int a) {
        return new Rational(a);
    }

    final static Rational ONE = new Rational(1);
    final static Rational ZERO = new Rational(0);

    Rational add(Rational o) {
        return new Rational(p * o.q + q * o.p, q * o.q);
    }

    Rational subtract(Rational o) {
        return new Rational(p * o.q - q * o.p, q * o.q);
    }

    Rational multiply(Rational o) {
        return new Rational(p * o.p, q * o.q);
    }

    Rational divide(Rational o) {
        return new Rational(p * o.q, q * o.p);
    }

    int signum() {
        return p < 0 ? -1 : p > 0 ? 1 : 0;
    }

    Rational negate() {
        return new Rational(-p, q);
    }

    public boolean equals(Rational o) {
        return p == o.p && q == o.q;
    }

    public int compareTo(Rational o) {
        return Double.compare((double)p / q, (double)o.p / o.q);
    }

    public String toString() {
        return p + "/" + q;
    }
}

class Point {

    Rational x;
    Rational y;

    Point(Rational x, Rational y) {
        this.x = x;
        this.y = y;
    }

    Point add(Point o) {
        return new Point(x.add(o.x), y.add(o.y));
    }

    Point subtract(Point o) {
        return new Point(x.subtract(o.x), y.subtract(o.y));
    }

    Point multiply(Rational scale) {
        return new Point(x.multiply(scale), y.multiply(scale));
    }

    Point divide(Rational scale) {
        return new Point(x.divide(scale), y.divide(scale));
    }

    Rational det(Point a, Point b) {
        Rational z1 = a.x.subtract(x).multiply(b.y.subtract(y));
        Rational z2 = b.x.subtract(x).multiply(a.y.subtract(y));
        return z1.subtract(z2);
    }

    public boolean equals(Point o) {
        return x.equals(o.x) && y.equals(o.y);
    }

    public String toString() {
        return "(" + x  + "," + y + ")";
    }
}

interface Segment {
    public Point newDirection(Point direction);
    public Rational getIntersect(Point origin, Point direction);
}

class SegmentX implements Segment {

    Rational x;
    Rational y1, y2;

    SegmentX(int x, int y1, int y2) {
        this.x = Rational.valueOf(x);
        this.y1 = Rational.valueOf(Math.min(y1, y2));
        this.y2 = Rational.valueOf(Math.max(y1, y2));
    }

    public Point newDirection(Point direction) {
        return new Point(direction.x.negate(), direction.y);
    }

    public Rational getIntersect(Point origin, Point direction) {
        if (direction.x.signum() == 0) {
            return null;
        }
        Rational ret = x.subtract(origin.x).divide(direction.x);
        if (ret.signum() < 0) {
            return null;
        }
        Rational y = origin.y.add(direction.y.multiply(ret));
        if (y.compareTo(y1) >= 0 && y.compareTo(y2) <= 0) {
            return ret;
        }
        return null;
    }
}

class SegmentY implements Segment {

    Rational y;
    Rational x1, x2;

    SegmentY(int y, int x1, int x2) {
        this.y = Rational.valueOf(y);
        this.x1 = Rational.valueOf(Math.min(x1, x2));
        this.x2 = Rational.valueOf(Math.max(x1, x2));
    }

    public Point newDirection(Point direction) {
        return new Point(direction.x, direction.y.negate());
    }

    public Rational getIntersect(Point origin, Point direction) {
        if (direction.y.signum() == 0) {
            return null;
        }
        Rational ret = y.subtract(origin.y).divide(direction.y);
        if (ret.signum() < 0) {
            return null;
        }
        Rational x = origin.x.add(direction.x.multiply(ret));
        if (x.compareTo(x1) >= 0 && x.compareTo(x2) <= 0) {
            return ret;
        }
        return null;
    }
}


public class Main implements Runnable {

    Point nextPoint() throws IOException {
        int x = nextInt();
        int y = nextInt();
        return new Point(Rational.valueOf(x), Rational.valueOf(y));
    }

    Segment nextSegment() throws IOException {
        int x1 = nextInt();
        int y1 = nextInt();
        int x2 = nextInt();
        int y2 = nextInt();
        if (x1 == x2) {
            return new SegmentX(x1, y1, y2);
        } else if (y1 == y2) {
            return new SegmentY(y1, x1, x2);
        }
        throw new RuntimeException("non hor/ver segments");
    }

    int solve(int n, Point src, Point target, Point lastDir, Segment[] mirrors) {
        Point direction = lastDir;
        int ans = Integer.MAX_VALUE;
        for (int dx = 0; dx < 2; dx ++) {
            direction = new Point(direction.x.negate(), direction.y);
            for (int dy = 0; dy < 2; dy++) {
                direction = new Point(direction.x, direction.y.negate());
                boolean[] used = new boolean[n];
                Point now = src, dir = direction;
                int reflects = 0;
                while (true) {
                    Rational minT = null;
                    int id = -1;
                    for (int i = 0; i < n; i++) {
                        if (!used[i]) {
                            Rational t = mirrors[i].getIntersect(now, dir);
                            if (t != null) {
                                if (minT == null || minT.compareTo(t) > 0) {
                                    minT = t;
                                    id = i;
                                }
                            }
                        }
                    }
                    if (now.det(now.add(dir), target).signum() == 0) {
                        Rational t = null;
                        if (dir.x.signum() != 0) {
                            t = target.x.subtract(now.x).divide(dir.x);
                        } else if (dir.y.signum() != 0) {
                            t = target.y.subtract(now.y).divide(dir.y);
                        } else {
                            throw new RuntimeException("direction is zero");
                        }
                        if (t.signum() >= 0) {
                            if (minT == null || t.compareTo(minT) <= 0) {
                                if (dir.equals(lastDir)) {
                                    break;
                                }
                            }
                        }
                    }
                    if (minT == null) {
                        reflects = -1;
                        break;
                    }
                    used[id] = true;
                    reflects ++;
                    now = now.add(dir.multiply(minT));
                    dir = mirrors[id].newDirection(dir);
                }
                if (reflects >= 0) {
                    ans = Math.min(ans, reflects);
                }
            }
        }
        return ans;
    }

    public void run() {
        try {
            in = new BufferedReader(new InputStreamReader(System.in));
            out = new PrintWriter(System.out);
            st = new StringTokenizer("");
            int n = nextInt();
            Point src = nextPoint();
            Point target = nextPoint();
            Point direction = nextPoint();
            Segment[] mirrors = new Segment[n];
            for (int i = 0; i < n; i++) {
                mirrors[i] = nextSegment();
            }
            int res = solve(n, src, target, target.subtract(direction), mirrors);
            if (res == Integer.MAX_VALUE) {
                res = -1;
            }
            out.println(res);
            in.close();
            out.close();
        } catch (IOException ex) {
            ex.printStackTrace();
        } catch (Exception ex) {
            ex.printStackTrace();
            System.exit(-1);
        } catch (Throwable t) {
            t.printStackTrace();
        }
    }

    public static void debug(Object...os) {
        System.err.println(Arrays.deepToString(os));
    }

    String next() throws IOException {
        while (!st.hasMoreTokens()) {
            String line = in.readLine();
            if (line == null) {
                throw new IOException("end of file");
            }
            st = new StringTokenizer(line);
        }
        return st.nextToken();
    }

    int nextInt() throws IOException {
        return Integer.parseInt(next());
    }

    long nextLong() throws IOException {
        return Long.parseLong(next());
    }

    double nextDouble() throws IOException {
        return Double.parseDouble(next());
    }

    BufferedReader in;
    StringTokenizer st;
    PrintWriter out;

    public static void main(String[] args) {
        new Thread(new Main()).start();
    }
}

