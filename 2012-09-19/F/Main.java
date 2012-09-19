
import java.util.*;
import java.io.*;
import java.math.*;

public class Main implements Runnable {

    void solve(int n, int[][] m, BigInteger targetDet) {
        Rational[][] ma = new Rational[n][n * 2];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                ma[i][j] = Rational.valueOf(m[i][j]);
                ma[i][n + j] = i == j ? Rational.ONE : Rational.ZERO;
            }
        }
        Rational det = Rational.ONE;
        for (int i = 0; i < n; i++) {
            int r = i;
            while (r < n && ma[r][i].signum() == 0) {
                r ++;
            }
            assert r < n : "matrix is degenerate";
            if (r != i) {
                Rational[] tmp = ma[i];
                ma[i] = ma[r];
                ma[r] = tmp;
                det = det.negate();
            }
            det = det.multiply(ma[i][i]);
            for (int j = n * 2 - 1; j >= i; j--) {
                ma[i][j] = ma[i][j].divide(ma[i][i]);
            }
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    continue;
                }
                for (int k = n * 2 - 1; k >= i; k--) {
                    ma[j][k] = ma[j][k].subtract(ma[i][k].multiply(ma[j][i]));
                }
            }
        }
        BigInteger[][] coma = new BigInteger[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                Rational r = ma[j][i + n].multiply(det);
                assert r.q.equals(BigInteger.ONE) : "gxx is wrong";
                coma[i][j] = r.p;
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (coma[i][j].signum() == 0) {
                    continue;
                }
                BigInteger delta = targetDet.subtract(det.p).divide(coma[i][j]);
                if (det.p.add(coma[i][j].multiply(delta)).equals(targetDet)) {
                    out.println((i + 1) + " " + (j + 1) + " " + BigInteger.valueOf(m[i][j]).add(delta));
                    return;
                }
            }
        }
        out.println(-1);
    }

    public void run() {
        try {
            in = new BufferedReader(new FileReader("det.in"));
            out = new PrintWriter(new File("det.out"));
            st = new StringTokenizer("");
            int n = nextInt();
            int[][] ma = new int[n][n];
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    ma[i][j] = nextInt();
                }
            }
            BigInteger targetDet = new BigInteger(next());
            in.close();
            solve(n, ma, targetDet);
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

class Rational {

    BigInteger p, q;

    public Rational(BigInteger p, BigInteger q) {
        assert q.signum() != 0 : "divided by zero";
        BigInteger g = p.gcd(q);
        if (!q.equals(BigInteger.ONE)) {
            this.p = p.divide(g);
            this.q = q.divide(g);
        } else {
            this.p = p;
            this.q = q;
        }
        if (this.q.signum() < 0) {
            this.p = this.p.negate();
            this.q = this.q.negate();
        }
    }

    public Rational(BigInteger p) {
        this.p = p;
        this.q = BigInteger.ONE;
    }

    public static Rational valueOf(long p) {
        return new Rational(BigInteger.valueOf(p));
    }

    public static Rational ZERO = new Rational(BigInteger.ZERO);
    public static Rational ONE = new Rational(BigInteger.ONE);

    public Rational add(Rational o) {
        return new Rational(p.multiply(o.q).add(o.p.multiply(q)), q.multiply(o.q));
    }

    public Rational subtract(Rational o) {
        return new Rational(p.multiply(o.q).subtract(o.p.multiply(q)), q.multiply(o.q));
    }

    public Rational multiply(Rational o) {
        return new Rational(p.multiply(o.p), q.multiply(o.q));
    }

    public Rational divide(Rational o) {
        return new Rational(p.multiply(o.q), q.multiply(o.p));
    }

    public Rational negate() {
        return new Rational(p.negate(), q);
    }

    public Rational abs() {
        return new Rational(p.abs(), q);
    }

    public int signum() {
        return p.signum();
    }
}

