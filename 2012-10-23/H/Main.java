import java.util.*;
import java.io.*;
import java.math.*;

public class Main implements Runnable {

    BigInteger solve(int n) {
        BigInteger[][] choose = new BigInteger[n + 1][];
        for (int i = 0; i <= n; i++) {
            choose[i] = new BigInteger[i + 1];
            choose[i][i] = choose[i][0] = BigInteger.ONE;
            for (int j = 1; j < i; j++) {
                choose[i][j] = choose[i-1][j-1].add(choose[i-1][j]);
            }
        }
        BigInteger sum = BigInteger.ZERO;
        for (int i = 0; i <= n; i++) {
            int nodes = n - i;
            int edges = nodes * (nodes - 1) / 2;
            BigInteger graphs = BigInteger.ONE.shiftLeft(edges);
            if (i % 2 == 0) {
                sum = sum.add(graphs.multiply(choose[n][i]));
            } else {
                sum = sum.subtract(graphs.multiply(choose[n][i]));
            }
        }
        return sum;
    }

    public void run() {
        try {
            in = new BufferedReader(new InputStreamReader(System.in));
            out = new PrintWriter(System.out);
            st = new StringTokenizer("");
            int n = nextInt();
            BigInteger res = solve(n);
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

