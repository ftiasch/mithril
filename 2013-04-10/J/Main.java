import java.io.*;
import java.util.*;
import java.math.*;

class Rational {

    BigInteger num;
    BigInteger den;

    Rational(BigInteger val) {
        this.num = val;
        this.den = BigInteger.ONE;
    }

    Rational(BigInteger num, BigInteger den) {
        this.num = num;
        this.den = den;
        normalize();
    }

    static Rational valueOf(int val) {
        return new Rational(BigInteger.valueOf(val));
    }

    void normalize() {
        if (den.signum() == 0) {
            throw new RuntimeException("normalize: den == 0");
        }
        if (den.signum() < 0) {
            den = den.negate();
            num = num.negate();
        }
        BigInteger g = num.abs().gcd(den);
        num = num.divide(g);
        den = den.divide(g);
    }

    Rational add(Rational o) {
        return new Rational(num.multiply(o.den).add(o.num.multiply(den)), den.multiply(o.den));
    }

    Rational subtract(Rational o) {
        return new Rational(num.multiply(o.den).subtract(o.num.multiply(den)), den.multiply(o.den));
    }

    Rational multiply(Rational o) {
        return new Rational(num.multiply(o.num), den.multiply(o.den));
    }

    Rational divide(Rational o) {
        return new Rational(num.multiply(o.den), den.multiply(o.num));
    }

    int signum() {
        return num.signum();
    }

    Rational abs() {
        return new Rational(num.abs(), den);
    }

    Rational negate() {
        return new Rational(num.negate(), den);
    }

    @Override
    public String toString() {
        return num + "/" + den;
    }
}

class Point {
    Rational x;
    Rational y;

    Point(Rational x, Rational y) {
        this.x = x;
        this.y = y;
    }

    Rational det(Point a, Point b) {
        Rational lhs = a.x.subtract(x).multiply(b.y.subtract(y));
        Rational rhs = a.y.subtract(y).multiply(b.x.subtract(x));
        return lhs.subtract(rhs);
    }

    Point cut(Point b, Rational wa, Rational wb) {
        Rational nx = x.multiply(wb).add(b.x.multiply(wa));
        Rational ny = y.multiply(wb).add(b.y.multiply(wa));
        return new Point(nx.divide(wa.add(wb)), ny.divide(wa.add(wb)));
    }

    static Point intersect(Point a1, Point a2, Point b1, Point b2) {
        Rational x1 = a1.det(a2, b1);
        Rational x2 = a1.det(a2, b2);
        if (x1.signum() * x2.signum() >= 0) {
            return null;
        }
        x1 = b1.det(b2, a1);
        x2 = b1.det(b2, a2);
        if (x1.signum() * x2.signum() >= 0) {
            return null;
        }
        return a1.cut(a2, x1, x2.negate());
    }
}

public class Main extends Thread {

    Scanner sc;

    Rational readRational() {
        return new Rational(sc.nextBigInteger());
    }

    Point readPoint() {
        Rational x = readRational();
        Rational y = readRational();
        return new Point(x, y);
    }

    public void run() {
        try {
            sc = new Scanner(System.in);
            int tests = sc.nextInt();
            for (int cas = 0; cas < tests; cas++) {
                Point a = readPoint();
                Point b = readPoint();
                Point c = readPoint();
                Rational k1 = readRational();
                Rational k2 = readRational();
                Rational k3 = readRational();
                Point a1 = a.cut(c, k1, Rational.valueOf(1));
                Point c1 = c.cut(b, k2, Rational.valueOf(1));
                Point b1 = b.cut(a, k3, Rational.valueOf(1));
                Point ab = Point.intersect(a, c1, b, a1);
                Point bc = Point.intersect(b, a1, c, b1);
                Point ca = Point.intersect(c, b1, a, c1);
                Rational areaBig = a.det(b, c).abs();
                Rational areaSmall = ab.det(bc, ca).abs();
                Rational ratio = areaSmall.divide(areaBig);
                System.out.println(ratio);
            }
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }

    public static void main(String[] args) {
        new Thread(new Main()).start();
    }
}
