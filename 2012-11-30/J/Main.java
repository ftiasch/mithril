import java.util.*;
import java.io.*;
import java.math.*;

public class Main implements Runnable {

    final static int STATE_BAD = -1;
    final static int STATE_CLEAN = 0;
    final static int STATE_APPEAR = 1;
    final static int STATE_FORBID = 2;

    int transit(int st, boolean appeared) {
        if (st == STATE_CLEAN) {
            if (appeared) {
                return STATE_APPEAR;
            } else {
                return STATE_CLEAN;
            }
        } else if (st == STATE_APPEAR) {
            if (appeared) {
                return STATE_APPEAR;
            } else {
                return STATE_FORBID;
            }
        } else { // STATE_FORBID
            if (appeared) {
                return STATE_BAD;
            } else {
                return STATE_FORBID;
            }
        }
    }

    BigInteger choose(int n, int m) {
        BigInteger ret = BigInteger.ONE;
        for (int i = 0; i < m; i++) {
            ret = ret.multiply(BigInteger.valueOf(n - i));
            ret = ret.divide(BigInteger.valueOf(i + 1));
        }
        return ret;
    }

    BigInteger calc(int n, int m) {
        BigInteger[][][] wys = new BigInteger[n + 1][3][3];
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j < 3; j++) {
                Arrays.fill(wys[i][j], BigInteger.ZERO);
            }
        }
        wys[0][STATE_CLEAN][STATE_CLEAN] = BigInteger.ONE;
        BigInteger ret = BigInteger.ZERO;
        for (int i = 0; i <= n; i++) {
            for (int ls = 0; ls < 3; ls++) {
                for (int rs = 0; rs < 3; rs++) {
                    if (i == n) {
                        ret = ret.add(wys[i][ls][rs]);
                        continue;
                    }
                    for (int k = 0; k <= m; k++) {
                        int nls = transit(ls, k > 0);
                        int nrs = transit(rs, k < m);
                        if (nls != STATE_BAD && nrs != STATE_BAD) {
                            wys[i + 1][nls][nrs] = wys[i + 1][nls][nrs].add(wys[i][ls][rs]);
                        }
                    }
                }
            }
        }
        return ret;
    }

    BigInteger solve(int n, int m) {
        BigInteger ans = calc(n, m).add(calc(m, n)).subtract(choose(m + n, n).shiftLeft(1));
        return ans;
    }

    public void run() {
        try {
            in = new BufferedReader(new InputStreamReader(System.in));
            out = new PrintWriter(System.out);
            st = null;
            int m = nextInt();
            int n = nextInt();
            BigInteger res = solve(n, m);
            System.out.println(res);
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
        while (st == null || !st.hasMoreTokens()) {
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
