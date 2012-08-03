import java.util.*;
import java.io.*;
import java.math.*;

public class Main implements Runnable {

    void solve(int n, int[] a) {
        while (n > 0 && a[n - 1] == 0) {
            n --;
        }
        int[] s = new int[n + 1];
        s[0] = 0;
        for (int i = 0; i < n; i++) {
            s[i + 1] = s[i] + a[i];
        }
        BigInteger[][] choose = new BigInteger[256][];
        for (int i = 0; i < choose.length; i++) {
            choose[i] = new BigInteger[i + 1];
            choose[i][0] = choose[i][i] = BigInteger.ONE;
            for (int j = 1; j < i; j++) {
                choose[i][j] = choose[i-1][j-1].add(choose[i-1][j]);
            }
        }
        BigInteger[][] f = new BigInteger[n + 1][s[n] + 1];
        for (int i = 0; i <= n; i++) {
            Arrays.fill(f[i], BigInteger.ZERO);
        }
        
        if (a[0]==0) {
            out.println("0");
            return;
        }
        f[1][1] = BigInteger.ONE;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= s[i]; j++) {
                f[i][j] = f[i][j].add(f[i][j-1]);
            }
            if (i == n) {
                continue;
            }
            for (int j = i+1; j <= s[i] + 1; j++) {
                BigInteger wys = a[i] == 0 ? BigInteger.ZERO : choose[s[i] - j + a[i]][s[i] - j + 1];
                f[i+1][j] = f[i+1][j].add(f[i][j-1].multiply(wys));
            }
        }
        out.println(f[n][s[n]]);
    }

    public void run() {
        try {
            in = new BufferedReader(new InputStreamReader(System.in));
            out = new PrintWriter(System.out);
            st = new StringTokenizer("");
            int n = nextInt();
            int[] a = new int[n];
            for (int i = 0; i < n; i++) {
                a[i] = nextInt();
            }
            solve(n, a);
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

