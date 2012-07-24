
import java.util.*;
import java.io.*;
import java.math.*;

public class Main implements Runnable {

    BigInteger solve(long p, int n) {
        BigInteger[] cnt = new BigInteger[n + 1];
        for (int i = 0; i <= n; i++) {
            cnt[i] = BigInteger.valueOf(p).pow(n - i);
        }
        for (int i = n; i >= 0; i--) {
            for (int j = i + 1; j <= n; j++) {
                cnt[i] = cnt[i].subtract(cnt[j]);
            }
        }
        BigInteger[] sum = new BigInteger[n + 1];
        Arrays.fill(sum, BigInteger.ZERO);
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                int k = Math.min(n, i + j);
                sum[k] = sum[k].add(cnt[i].multiply(cnt[j]));
            }
        }
        BigInteger ret = BigInteger.ZERO;
        for (int i = 0; i <= n; i++) {
            sum[i] = sum[i].divide(cnt[i]);
            ret = ret.add(sum[i].multiply(sum[i]).multiply(cnt[i]));
        }
        return ret;
    }

    BigInteger solve(long n) {
        BigInteger all = BigInteger.valueOf(n).pow(4);
        BigInteger ret = BigInteger.ONE;
        for (long i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                int cnt = 0;
                while (n % i == 0) {
                    n /= i;
                    cnt ++;
                }
                ret = ret.multiply(solve(i, cnt));
            }
        }
        if (n > 1) {
            ret = ret.multiply(solve(n, 1));
        }
        return all.subtract(ret);
    }

    long bruteForce(int n) {
        long[] cnt = new long[n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cnt[i * j % n] ++;
            }
        }
        long ret = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    ret += cnt[i] * cnt[j];
                }
            }
        return ret;
    }

    public void run() {
        Scanner sc = new Scanner(System.in);
        long n = sc.nextLong();
        System.out.println(solve(n).mod(sc.nextBigInteger()));
    }

    void debug(Object...os) {
        System.err.println(Arrays.deepToString(os));
    }

    public static void main(String[] args) {
        new Thread(new Main()).start();
    }
}
