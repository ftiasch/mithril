import java.util.*;
import java.io.*;
import java.math.*;

public class Main implements Runnable {

    public void solve() throws IOException {
        int n = nextInt();
        if (n == 1) {
            System.out.println("0");
            return;
        }
        BigInteger[] factorials = new BigInteger[2 * n + 1];
        factorials[0] = BigInteger.ONE;
        for (int i = 1; i < factorials.length; i++) {
            factorials[i] = factorials[i - 1].multiply(BigInteger.valueOf(i));
        }
        BigInteger[][] choose = new BigInteger[n + 1][];
        for (int i = 0; i <= n; i++) {
            choose[i] = new BigInteger[i + 1];
            choose[i][0] = choose[i][i] = BigInteger.ONE;
            for (int j = 1; j < i; j++) {
                choose[i][j] = choose[i-1][j-1].add(choose[i-1][j]);
            }
        }
        BigInteger ans = BigInteger.ZERO;
        for (int i = 0; i <= n; i++) {
            BigInteger now = BigInteger.ONE;
            now = now.multiply(choose[n][i]);
            now = now.multiply(factorials[2 * n - i - 1]);
            now = now.multiply(BigInteger.valueOf(2 * n));
            now = now.shiftLeft(i);
            if ((i & 1) == 0) {
                ans = ans.add(now);
            } else {
                ans = ans.subtract(now);
            }
        }
        System.out.println(ans);
    }

    public void run() {
        try {
            in = new BufferedReader(new InputStreamReader(System.in));
            out = new PrintWriter(System.out);
            st = new StringTokenizer("");
            solve();
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

