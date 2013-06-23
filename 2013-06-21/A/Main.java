
import java.util.*;
import java.math.*;

class Complex {
    BigInteger real, imag;

    Complex(BigInteger real) {
        this.real = real;
        this.imag = BigInteger.ZERO;
    }

    Complex(BigInteger real, BigInteger imag) {
        this.real = real;
        this.imag = imag;
    }

    Complex multiply(Complex o) {
        return new Complex(real.multiply(o.real).subtract(imag.multiply(o.imag)), 
                real.multiply(o.imag).add(imag.multiply(o.real)));
    }

    boolean equals(Complex o) {
        return real.equals(o.real) && imag.equals(o.imag);
    }

    Complex pow(int n) {
        Complex ret = new Complex(BigInteger.ONE);
        for (int i = 0; i < n; i++) {
            ret = ret.multiply(this);
        }
        return ret;
    }
}

public class Main implements Runnable {

    Complex nextComplex(Scanner sc) {
        BigInteger real = sc.nextBigInteger();
        BigInteger imag = sc.nextBigInteger();
        return new Complex(real, imag);
    }

    public void run() {
        try {
            Scanner sc = new Scanner(System.in);
            Complex xn = nextComplex(sc);
            int n = sc.nextInt();
            Complex xm = nextComplex(sc);
            int m = sc.nextInt();
            int g = BigInteger.valueOf(n).gcd(BigInteger.valueOf(m)).intValue();
            if (xn.pow(m / g).equals(xm.pow(n / g))) { 
                System.out.println(g);
            } else {
                System.out.println(0);
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
