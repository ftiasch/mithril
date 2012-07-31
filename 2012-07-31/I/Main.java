import java.util.*;
import java.io.*;
import java.math.*;

public class Main implements Runnable {
    public void run() {
        try {
            in = new BufferedReader(new InputStreamReader(System.in));
            out = new PrintWriter(System.out);
            st = new StringTokenizer("");
            int n = nextInt();
            int k = nextInt();
            BigInteger[][] ways = new BigInteger[n + 1][k + 1];
            ways[0][0] = BigInteger.ONE;
            for (int j = 1; j <= k; ++ j) {
                ways[0][j] = BigInteger.ZERO;
            }
            for (int i = 1; i <= n; ++ i) {
                ways[i][0] = BigInteger.ZERO;
                ways[i][1] = BigInteger.ONE;
                for (int j = 2; j <= k; ++ j) {
                    ways[i][j] = ways[i - 1][j - 1];
                    if (i >= j) {
                        ways[i][j] = ways[i][j].add(ways[i - j][j]);
                    }
                }
            }
            out.println(ways[n][k]);
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

