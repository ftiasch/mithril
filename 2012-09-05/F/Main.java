import java.util.*;
import java.io.*;
import java.math.*;

public class Main implements Runnable {

    final static int MAXN = 1024;

    static boolean[] isPrime = new boolean[MAXN];
    static int[] prime = new int[MAXN];
    static int primes;

    static {
        Arrays.fill(isPrime, true);
        isPrime[0] = isPrime[1] = false;
        for (int i = 2; i * i < MAXN; i++) {
            if (!isPrime[i]) {
                continue;
            }
            for (int j = i * i; j < MAXN; j += i) {
                isPrime[j] = false;
            }
        }
        primes = 0;
        for (int i = 2; i < MAXN; i++) {
            if (isPrime[i]) {
                prime[primes++] = i;
            }
        }
    }

    BigInteger[][] memo = new BigInteger[MAXN][MAXN];

    BigInteger count(int n, int p) {
        if (prime[p] > n) {
            return BigInteger.ONE;
        }
        if (memo[n][p] != null) {
            return memo[n][p];
        }
        BigInteger ret = count(n, p + 1);
        for (int i = prime[p]; i <= n; i *= prime[p]) {
            ret = ret.add(count(n - i, p + 1));
        }
        return memo[n][p] = ret;
    }

    public void run() {
        try {
            in = new BufferedReader(new InputStreamReader(System.in));
            out = new PrintWriter(System.out);
            st = new StringTokenizer("");
            while (true) {
                String line = in.readLine();
                if (line == null || line == "") {
                    break;
                }
                int n = Integer.parseInt(line);
                System.out.println(count(n, 0));
            }
            in.close();
            out.close();
        } catch (IOException ex) {
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

