import java.util.*;
import java.math.*;

class Rational {

    public BigInteger p, q;

    public static Rational ZERO = new Rational(BigInteger.ZERO);
    public static Rational ONE = new Rational(BigInteger.ONE);

    public static Rational valueOf(int a) {
        return new Rational(BigInteger.valueOf(a));
    }

    Rational(BigInteger p, BigInteger q) {
        this.p = p;
        this.q = q;
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
        if (q.equals(BigInteger.ONE)) {
            return p.toString();
        }
        return p + "/" + q;
    }
}

class Polynomial {
    Rational[] coeff;

    Polynomial(Rational[] coeff) {
        this.coeff = coeff;
    }

    Polynomial add(Polynomial o) {
        Rational[] ncoeff = new Rational[Math.max(coeff.length, o.coeff.length)];
        Arrays.fill(ncoeff, Rational.ZERO);
        for (int i = 0; i < coeff.length; i++)
            ncoeff[i] = ncoeff[i].add(coeff[i]);
        for (int i = 0; i < o.coeff.length; i++)
            ncoeff[i] = ncoeff[i].add(o.coeff[i]);
        return new Polynomial(ncoeff);
    }

    Polynomial multiply(Polynomial o) {
        Rational[] ncoeff = new Rational[Math.max(0, coeff.length + o.coeff.length - 1)];
        Arrays.fill(ncoeff, Rational.ZERO);
        for (int i = 0; i < coeff.length; i++)
            for (int j = 0; j < o.coeff.length; j++)
                ncoeff[i + j] = ncoeff[i+j].add(coeff[i].multiply(o.coeff[j]));
        return new Polynomial(ncoeff);
    }

    Polynomial scale(Rational s) {
        Rational[] ncoeff = new Rational[coeff.length];
        Arrays.fill(ncoeff, Rational.ZERO);
        for (int i = 0; i < coeff.length; i++)
            ncoeff[i] = coeff[i].multiply(s);
        return new Polynomial(ncoeff);
    }
}

public class Main implements Runnable {

    Rational det(Rational[][] a) {
        int n = a.length;
        Rational ret = Rational.ONE;
        for (int i = 0; i < n; i++) {
            int r = i;
            while (r < n && a[r][i].signum() == 0) {
                r++;
            }
            if (r == n)
                return Rational.ZERO;
            if (r != i) {
                Rational[] tmp = a[i];
                a[i] = a[r];
                a[r] = tmp;
                ret = ret.negate();
            }
            ret = ret.multiply(a[i][i]);
            for (int j = n - 1; j >= i; j--)
                a[i][j] = a[i][j].divide(a[i][i]);
            for (int j = i + 1; j < n; j++) {
                for (int k = n - 1; k >= i; k--) {
                    a[j][k] = a[j][k].subtract(a[i][k].multiply(a[j][i]));
                }
            }
        }
        return ret;
    }

    public void run() {
        try {
            Scanner sc = new Scanner(System.in);
            while (sc.hasNextInt()) {
                int n = sc.nextInt();
                int[][] a = new int[n][n];
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        a[i][j] = sc.nextInt();
                    }
                }
                Rational[] x = new Rational[n + 1];
                Rational[] y = new Rational[n + 1];
                for (int i = 0; i <= n; i++) {
                    x[i] = Rational.valueOf(i * i);
                    Rational[][] ma = new Rational[n][n];
                    for (int u = 0; u < n; u++) {
                        for (int v = 0; v < n; v++) {
                            ma[u][v] = Rational.valueOf(a[u][v]);
                            if (u == v)
                                ma[u][v] = ma[u][v].subtract(x[i]);
                        }
                    }
                    y[i] = det(ma);
                }
                Polynomial ret = new Polynomial(new Rational[0]);
                for (int i = 0; i <= n; i++) {
                    Rational mul = Rational.ONE;
                    for (int j = 0; j <= n; j++) {
                        if (i != j) {
                            mul = mul.multiply(x[i].subtract(x[j]));
                        }
                    }
                    Polynomial mul2 = new Polynomial(new Rational[]{Rational.ONE});
                    for (int j = 0; j <= n; j++) {
                        if (i != j) {
                            mul2 = mul2.multiply(new Polynomial(new Rational[]{ x[j].negate(), Rational.ONE}));
                        }
                    }
                    ret = ret.add(mul2.scale(y[i].divide(mul)));
                }
                for (int i = n; i >= 0; i--) {
                    System.out.println(ret.coeff[i]);
                }
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
