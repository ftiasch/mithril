import java.util.*;
import java.io.*;
import java.math.*;

public class Main implements Runnable {
    int m, n;

    void clear(BigInteger[][][] ways) {
        for (int bMask = 0; bMask < (1 << m); ++ bMask) {
            for (int vMask = 0; vMask < (1 << (m - 1)); ++ vMask) {
                for (int hMask = 0; hMask < 2; ++ hMask) {
                    ways[bMask][vMask][hMask] = BigInteger.ZERO;
                }
            }
        }
    }

    public void run() {
        try {
            in = new BufferedReader(new InputStreamReader(System.in));
            out = new PrintWriter(System.out);
            st = new StringTokenizer("");
            
            m = nextInt();
            n = nextInt();
            BigInteger[][][] ways = new BigInteger[1 << m][1 << (m - 1)][2];
            clear(ways);
            ways[0][(1 << (m - 1)) - 1][0] = BigInteger.ONE;
            for (int i = 0; i < n; ++ i) {
                for (int j = 0; j < m; ++ j) {
                    BigInteger[][][] newWays = new BigInteger[1 << m][1 << (m - 1)][2];
                    clear(newWays);
                    for (int bMask = 0; bMask < (1 << m); ++ bMask) {
                        for (int vMask = 0; vMask < (1 << (m - 1)); ++ vMask) {
                            for (int hMask = 0; hMask < 2; ++ hMask) {
                                if (i > 1 && j == 0 && hMask > 0) {
                                    continue;
                                }
                                BigInteger v = ways[bMask][vMask][hMask];
                                int newH = (i > 0 && j == 0)? 1: hMask;
                                if ((bMask >> j & 1) == 0) {
                                    newWays[bMask | (1 << j)][vMask][newH] = newWays[bMask | (1 << j)][vMask][newH].add(v);
                                }
                                if (j > 0 && (bMask >> (j - 1) & 1) == 1 && (bMask >> j & 1) == 0) {
                                    newWays[bMask & ~(1 << (j - 1))][vMask & ~(1 << (j - 1))][newH] = newWays[bMask & ~(1 << (j - 1))][vMask & ~(1 << (j - 1))][newH].add(v);
                                }
                                if ((bMask >> j & 1) == 1) {
                                    newWays[bMask & ~(1 << j)][vMask][0] = newWays[bMask & ~(1 << j)][vMask][0].add(v);
                                }
                            }
                        }
                    }
                    ways = newWays;
                }
            }
            out.println(String.format("%d", ways[0][0][0]));
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

