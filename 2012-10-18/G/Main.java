import java.util.*;
import java.io.*;
import java.math.*;

public class Main implements Runnable {

    boolean[] fst, snd, add, sub;

    int dfs(int n, int depth) {
        if (depth == 3) {
            return 1;
        }
        int ret = 0;
        for (int x = 0; x < n; x++) {
            for (int y = 0; y < n; y++) {
                if (fst[x] || snd[y] || add[x + y] || sub[x + n - y]) {
                    continue;
                }
                fst[x] = snd[y] = add[x + y] = sub[x + n - y] = true;
                ret += dfs(n, depth + 1);
                fst[x] = snd[y] = add[x + y] = sub[x + n - y] = false;
            }
        }
        return ret;
    }

    int bruteForce(int n) {
        fst = new boolean[n];
        snd = new boolean[n];
        add = new boolean[n * 2];
        sub = new boolean[n * 2];
        return dfs(n, 0);
    }

    BigInteger solve(int[] a, int n) {
        if (n < a.length) {
            return BigInteger.valueOf(a[n]);
        }
        BigInteger[][] table = new BigInteger[a.length + 1][n + 1];
        for (int i = 0; i < a.length; i++) {
            table[a.length][i] = BigInteger.valueOf(a[i]);
        }
        for (int i = a.length - 1; i >= 1; i--) {
            for (int j = 0; j < i; j++) {
                table[i][j] = table[i + 1][j + 1].subtract(table[i + 1][j]);
            }
        }
        for (int i = 1; i <= n; i++) {
            table[1][i] = table[1][0];
        }
        for (int i = 2; i <= a.length; i++) {
            for (int j = i; j <= n; j++) {
                table[i][j] = table[i - 1][j - 1].add(table[i][j - 1]);
            }
        }
        return table[a.length][n];
    }

    BigInteger solve(int n) {
        if (n % 2 == 1) {
            return solve(odds, n / 2);
        } else {
            return solve(evens, n / 2);
        }
    }

    final static int[] odds = new int[]{0, 0, 1224, 21768, 150576, 647280, 2088120, 5557944, 12888288, 26941536};
    final static int[] evens = new int[]{0, 0, 144, 6144, 61920, 326400, 1196400, 3475584, 8589504, 18846720};

    public void run() {
        try {
            in = new BufferedReader(new InputStreamReader(System.in));
            out = new PrintWriter(System.out);
            st = new StringTokenizer("");
            int n = nextInt();
            System.out.println(solve(n).divide(BigInteger.valueOf(6)));
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

