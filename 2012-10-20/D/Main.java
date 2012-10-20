import java.util.*;
import java.io.*;
import java.math.*;

public class Main implements Runnable {

    long[][][][] memo;
    boolean[][][][] seen;
    int k;

    long go(int x, int y, int lx, int ly) {
        if (y > k) {
            y = 0;
            if (++x > k) {
                return lx == 0 && ly == 0 ? 1L : 0;
            }
        }
        if (seen[x][y][lx][ly]) {
            return memo[x][y][lx][ly];
        }
        seen[x][y][lx][ly] = true;
        long ret = 0;
        if (lx >= x && ly >= y) {
            ret += go(x, y, lx - x, ly - y);
        }
        ret += go(x, y + 1, lx, ly);
        return memo[x][y][lx][ly] = ret;
    }

    long solveK(int k) {
        this.k = k;
        memo = new long[k + 1][k + 1][k + 1][k + 1];
        seen = new boolean[k + 1][k + 1][k + 1][k + 1];
        return go(0, 1, k, k) - 1;
    }

    long solveN(long n) {
        BigInteger N = BigInteger.valueOf(n);
        for (int k = 60; k >= 1; k--) {
            BigInteger lo = BigInteger.ONE;
            BigInteger hi = BigInteger.ONE;
            while (hi.pow(k).compareTo(N) <= 0) {
                hi = hi.shiftLeft(1);
            }
            while (lo.compareTo(hi) < 0) {
                BigInteger mid = lo.add(hi).shiftRight(1);
                if (mid.add(BigInteger.ONE).pow(k).compareTo(N) <= 0) {
                    lo = mid.add(BigInteger.ONE);
                } else {
                    hi = mid;
                }
            }
            if (lo.pow(k).equals(N)) {
                return solveK(k);
            }
        }
        return 0;
    }

    public void run() {
        try {
            in = new BufferedReader(new InputStreamReader(System.in));
            out = new PrintWriter(System.out);
            st = new StringTokenizer("");
            long n = nextLong();
            System.out.println(solveN(n));
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

