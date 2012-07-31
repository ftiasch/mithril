import java.util.*;
import java.io.*;
import java.math.*;

public class Main implements Runnable {

    void solve(int n) {
        BigInteger[][] choose = new BigInteger[n + 1][];
        for (int i = 0; i <= n; i++) {
            choose[i] = new BigInteger[i + 1];
            choose[i][0] = choose[i][i] = BigInteger.ONE;
            for (int j = 1; j < i; j++) {
                choose[i][j] = choose[i-1][j-1].add(choose[i-1][j]);
            }
        }
        int[] ans1 = new int[n + 1];
        ans1[1] = 0;
        for (int i = 2; i <= n; i++) {
            ans1[i] = ans1[i / 2] + ans1[(i + 1) / 2] + i - 1;
        }
        out.println(ans1[n]);
        int[][] ans2 = new int[n + 1][];
        ans2[1] = new int[]{0};
        for (int i = 2; i <= n; i++) {
            int sz = 0;
            ans2[i] = new int[i];
            int ls = (i + 1) / 2, rs = i / 2;
            for (int j : ans2[ls]) {
                ans2[i][sz++] = j == ls - 1 ? i - 2 : j;
            }
            for (int j : ans2[rs]) {
                ans2[i][sz++] = j == rs - 1 ? i - 1 : j + ls - 1;
            }
        }
        for (int i = 0; i < n; i++) {
            if (i > 0) {
                out.print(' ');
            }
            out.print(ans2[n][i] + 1);
        }
        out.println();
        BigInteger[] ans3 = new BigInteger[n + 1];
        ans3[1] = BigInteger.ONE;
        for (int i = 2; i <= n; i++) {
            int ls = (i + 1) / 2, rs = i / 2;
            ans3[i] = ans3[ls].multiply(ans3[rs]).shiftLeft(1);
            ans3[i] = ans3[i].multiply(choose[ls + rs - 2][ls - 1]);
        }
        out.println(ans3[n]);
    }

    public void run() {
        try {
            in = new BufferedReader(new InputStreamReader(System.in));
            out = new PrintWriter(System.out);
            st = new StringTokenizer("");
            int n = nextInt();
            solve(n);
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

