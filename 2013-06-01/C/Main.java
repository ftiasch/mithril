
import java.util.*;
import java.math.*;

class Rational implements Comparable<Rational> {

    public BigInteger p, q;

    public static Rational ZERO = new Rational(BigInteger.ZERO);
    public static Rational ONE = new Rational(BigInteger.ONE);

    public static Rational valueOf(int a) {
        return new Rational(BigInteger.valueOf(a));
    }

    Rational(String s) {
        String[] sp = s.split("[/]");
        this.p = new BigInteger(sp[0]);
        this.q = new BigInteger(sp[1]);
        normalize();
    }

    Rational(BigInteger p, BigInteger q) {
        this.p = p;
        this.q = q;
        normalize();
    }

    void normalize() {
        if (this.q.signum() < 0) {
            this.p = this.p.negate();
            this.q = this.q.negate();
        }
        BigInteger g = this.p.abs().gcd(this.q);
        if (!g.equals(BigInteger.ONE)) {
            this.p = this.p.divide(g);
            this.q = this.q.divide(g);
        }
    }

    Rational(BigInteger p) {
        this.p = p;
        this.q = BigInteger.ONE;
    }

    Rational add(Rational o) {
        return new Rational(p.multiply(o.q).add(q.multiply(o.p)), q.multiply(o.q));
    }

    Rational subtract(Rational o) {
        return new Rational(p.multiply(o.q).subtract(q.multiply(o.p)), q.multiply(o.q));
    }

    Rational multiply(Rational o) {
        return new Rational(p.multiply(o.p), q.multiply(o.q));
    }

    Rational divide(Rational o) {
        return new Rational(p.multiply(o.q), q.multiply(o.p));
    }

    Rational abs() {
        return new Rational(p.abs(), q);
    }

    Rational negate() {
        return new Rational(p.negate(), q);
    }

    int signum() {
        return p.signum();
    }

    public String toString() {
        return p + "/" + q;
    }

    public int compareTo(Rational o) {
        return p.multiply(o.q).compareTo(o.p.multiply(q));
    }

    Rational min(Rational o) {
        return compareTo(o) < 0 ? this : o;
    }

    Rational max(Rational o) {
        return compareTo(o) > 0 ? this : o;
    }
}


public class Main implements Runnable {


    public void run() {
        try {
            Scanner sc = new Scanner(System.in);
            int n = sc.nextInt();
            Rational[][] minv = new Rational[n][n];
            Rational[][] maxv = new Rational[n][n];
            for (int i = 0; i < n; i ++) {
                for (int j = 0; j < n; j++) {
                    minv[i][j] = new Rational(sc.next());
                    maxv[i][j] = new Rational(sc.next());
                }
            }
            boolean valid = true;
            Rational[][] a = new Rational[n][n];
            Rational[][] b = new Rational[n][n];
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (i == j) {
                        if (maxv[i][j].compareTo(Rational.ONE) < 0) {
                            valid = false;
                        }
                        if (minv[i][j].compareTo(Rational.ONE) > 0) {
                            valid = false;
                        }
                        a[i][j] = Rational.ONE;
                    } else {
                        a[i][j] = Rational.ONE.divide(maxv[j][i]).max(minv[i][j]);
                    }
                }
            }
            for (int k = 0; k < n; k++) {
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        b[i][j] = a[i][j];
                    }
                }
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        a[i][j] = a[i][j].max(b[i][k].multiply(b[k][j]));
                    }
                }
            }
            for (int i = 0; i < n; i++) {
                if (a[i][i].compareTo(Rational.ONE) > 0) {
                    valid = false;
                }
            }
            if (valid) {
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        if (j > 0) {
                            System.out.print(' ');
                        }
                        System.out.print(a[0][j].divide(a[0][i]));
                    }
                    System.out.println();
                }
            } else {
                System.out.println("Impossible");
            }
        } catch (Exception ex) {
            ex.printStackTrace();
            System.exit(-1);
        }
    }

    public static void main(String[] args) {
        new Thread(new Main()).start();
    }
}
