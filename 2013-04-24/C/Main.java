
import java.io.*;
import java.math.*;
import java.util.*;

class Line {
    long k, b;

    Line(long k, long b) {
        this.k = k;
        this.b = b;
    }

    long eval(long y) {
        return k * y + b;
    }

    BigInteger sigma(long lo, long hi) {
        BigInteger unit = BigInteger.valueOf(lo + hi);
        unit = unit.multiply(BigInteger.valueOf(hi - lo + 1));
        unit = unit.shiftRight(1);
        return unit.multiply(BigInteger.valueOf(k)).add(BigInteger.valueOf(b).multiply(BigInteger.valueOf(hi - lo + 1)));
    }
}

public class Main implements Runnable {

    void addSepTo(Set<Long> sets, Line small, Line large, long ymin, long ymax) {
        long K = large.k - small.k;
        long B = small.b - large.b;
        if (K == 0) {
            return;
        }
        if (K < 0) {
            K = -K;
            B = -B;
        }
        long y1 = (B - (B % K + K) % K) / K;
        long y2 = y1 + 1;
        if (ymin <= y1 && y1 <= ymax) {
            sets.add(y1);
        }
        if (ymin <= y2 && y2 <= ymax) {
            sets.add(y2);
        }
    }

    BigInteger integrate(long lo, long hi, Line small, Line large) {
        return large.sigma(lo, hi).subtract(small.sigma(lo, hi)).add(BigInteger.valueOf(hi - lo + 1));
    }

    public void run() {
        try {
            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
            while (true) {
                String line = br.readLine();
                if (line == null || line.length() == 0) {
                    break;
                }
                StringTokenizer st = new StringTokenizer(line);
                if (!st.hasMoreTokens()) {
                    break;
                }
                long xmin = Long.parseLong(st.nextToken());
                long xmax = Long.parseLong(st.nextToken());
                long ymin = Long.parseLong(st.nextToken());
                long ymax = Long.parseLong(st.nextToken());
                long smin = Long.parseLong(st.nextToken());
                long smax = Long.parseLong(st.nextToken());
                long dmin = Long.parseLong(st.nextToken());
                long dmax = Long.parseLong(st.nextToken());
                // enumerate y
                // xmin <= x <= xmax
                // smin - y <= x <= smax - y
                // dmin + y <= x <= dmax + y
                Line[] lhs = new Line[]{new Line(0, xmin), new Line(-1, smin), new Line(1, dmin)};
                Line[] rhs = new Line[]{new Line(0, xmax), new Line(-1, smax), new Line(1, dmax)};
                TreeSet<Long> sets = new TreeSet<Long>();
                sets.add(ymin);
                sets.add(ymax);
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        if (i != j) {
                            addSepTo(sets, lhs[i], lhs[j], ymin, ymax);
                            addSepTo(sets, rhs[i], rhs[j], ymin, ymax);
                        }
                        addSepTo(sets, lhs[i], rhs[j], ymin, ymax);
                    }
                }
                sets.add(ymax + 1);
                Long[] seps = sets.toArray(new Long[0]);
                BigInteger sum = BigInteger.ZERO;
                for (int i = 0; i + 1 < seps.length; i++) {
                    long lo = seps[i], hi = seps[i + 1] - 1;
                    long[] lhsX = new long[3];
                    long[] rhsX = new long[3];
                    for (int j = 0; j < 3; j++) {
                        lhsX[j] = lhs[j].eval(lo) + lhs[j].eval(hi);
                        rhsX[j] = rhs[j].eval(lo) + rhs[j].eval(hi);
                    }
                    int lMax = 0, rMin = 0;
                    for (int j = 1; j < 3; j++) {
                        if (lhsX[j] > lhsX[lMax]) {
                            lMax = j;
                        }
                        if (rhsX[j] < rhsX[rMin]) {
                            rMin = j;
                        }
                    }
                    if (lhsX[lMax] > rhsX[rMin]) {
                        continue;
                    }
                    sum = sum.add(integrate(lo, hi, lhs[lMax], rhs[rMin]));
                }
                System.out.println(sum);
            }
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    static void debug(Object...os) {
        System.err.println(Arrays.deepToString(os));
    }

    public static void main(String[] args) {
        new Thread(new Main()).start();
    }
}
