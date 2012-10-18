import java.util.*;
import java.io.*;
import java.math.*;

public class Main implements Runnable {

    final static int MAXN = 1024;
    final static long INF = 1000000000L * 1000000000L + 100;
    static long[][] choose;

    static {
        choose = new long[MAXN][];
        for (int i = 0; i < MAXN; i++) {
            choose[i] = new long[i + 1];
            choose[i][0] = choose[i][i] = 1;
            for (int j = 1; j < i; j++) {
                choose[i][j] = Math.min(INF, choose[i-1][j-1] + choose[i-1][j]);
            }
        }
    }

    BigInteger combine(int n, long sum) {
        if (sum < 0) {
            return BigInteger.ZERO;
        }
        if (n + sum < MAXN) {
            return BigInteger.valueOf(choose[n + (int)sum][n]);
        }
        BigInteger ret = BigInteger.valueOf(1);
        for (int i = 1; i <= n; i ++) {
            ret = ret.multiply(BigInteger.valueOf(sum + i));
            ret = ret.divide(BigInteger.valueOf(i));
        }
        return ret;
    }

    long[] solve(int n, long k) {
        long[] ret = new long[n];
        long lo = 0, hi = 1;
        while (combine(n, hi).compareTo(BigInteger.valueOf(k)) <= 0) {
            hi = hi * 2;
        }
        while (lo < hi) {
            long mid = (lo + hi) / 2;
            if (combine(n, mid).compareTo(BigInteger.valueOf(k)) >= 0) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        long sum = lo;
        k -= combine(n, sum - 1).longValue();
        for (int i = 0; i < n; i++) {
            BigInteger all = combine(n - i - 1, sum);
            BigInteger K = BigInteger.valueOf(k);
            lo = 0;
            hi = sum;
            while (lo < hi) {
                long mid = (lo + hi) / 2;
                if (all.subtract(combine(n - i - 1, sum - (mid + 1))).compareTo(K) >= 0) {
                    hi = mid;
                } else {
                    lo = mid + 1;
                }
            }
            k -= all.subtract(combine(n - i - 1, sum - lo)).longValue();
            ret[i] = lo;
            sum -= lo;
        }
        return ret;
    }

    public void run() {
        try {
            in = new BufferedReader(new InputStreamReader(System.in));
            out = new PrintWriter(System.out);
            st = new StringTokenizer("");
            int cas = 0;
            while (true) {
                int n = nextInt();
                long k = nextLong() + 1;
                if (n == 0 && k == 1) {
                    break;
                }
                long[] ans = solve(n, k);
                System.out.print("Case " + (++cas) + ":");
                for (long ai : ans) {
                    System.out.print(" " + ai);
                }
                System.out.println();
            }
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

