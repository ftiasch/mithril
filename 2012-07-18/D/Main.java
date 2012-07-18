// Problem D -- Discussions
// Author: Bin Jin
import java.util.*;
import java.math.*;

public class Main implements Runnable {

    final static int MAXN = 300;

    static BigInteger[][] comb = new BigInteger[MAXN + 1][];
    static Map<BigInteger,Integer> getIndex = new HashMap<BigInteger,Integer>();

    static {
        for (int i = 0; i <= MAXN; i++) {
            comb[i] = new BigInteger[i + 1];
            comb[i][0] = comb[i][i] = BigInteger.ONE;
            for (int j = 1; j < i; j++) {
                comb[i][j] = comb[i-1][j-1].add(comb[i-1][j]);
                if (getIndex.get(comb[i][j]) == null) {
                    getIndex.put(comb[i][j], i);
                }
            }
        }
    }

    BigInteger calc(BigInteger n, int m) {
        BigInteger p = BigInteger.ONE, q = BigInteger.ONE;
        for (int i = 1; i <= m; i++) {
            p = p.multiply(n.subtract(BigInteger.valueOf(i - 1)));
        }
        return p;
    }

    BigInteger solve(BigInteger z) {
        if (z.equals(BigInteger.ONE))
            return BigInteger.ONE;
        if (getIndex.get(z) != null)
            return BigInteger.valueOf(getIndex.get(z));
        BigInteger ret = z, last = z;
        for (int m = 1; ; m++) {
            z = z.multiply(BigInteger.valueOf(m));
            BigInteger lo = BigInteger.valueOf(m);
            BigInteger hi = last;
            while (lo.compareTo(hi) < 0) {
                BigInteger mid = lo.add(hi).shiftRight(1);
                if (calc(mid, m).compareTo(z) >= 0) {
                    hi = mid;
                } else {
                    lo = mid.add(BigInteger.ONE);
                }
            }
            if (calc(lo, m).equals(z)) {
                ret = lo;
            }
            if (BigInteger.valueOf(m*2).compareTo(lo) > 0)
                break;
            if (lo.compareTo(BigInteger.valueOf(MAXN)) <= 0)
                break;
            last = lo;
        }
        return ret;
    }

    public void run() {
        try {
            Scanner sc = new Scanner(System.in);
            while (sc.hasNextBigInteger()) {
                BigInteger z = sc.nextBigInteger();
                System.out.println(solve(z));
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
