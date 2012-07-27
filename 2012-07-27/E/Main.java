import java.util.*;
import java.io.*;
import java.math.*;

public class Main implements Runnable {
    final static BigInteger INF = BigInteger.valueOf(2000000000000000000L);

    int n, m, source, edgeCount;
    int[] firstEdge, to, nextEdge;
    BigInteger[] length, dist;

    void addEdge(int u, int v, long w) {
        to[edgeCount] = v;
        length[edgeCount] = BigInteger.valueOf(w);
        nextEdge[edgeCount] = firstEdge[u];
        firstEdge[u] = edgeCount ++;
    }

    public void run() {
        try {
            in = new BufferedReader(new InputStreamReader(System.in));
            out = new PrintWriter(System.out);
            st = new StringTokenizer("");
            n = nextInt();
            m = nextInt();
            source = nextInt() - 1;
            firstEdge = new int[n];
            to = new int[m];
            length = new BigInteger[m];
            nextEdge = new int[m];
            edgeCount = 0;
            Arrays.fill(firstEdge, -1);
            for (int i = 0; i < m; ++ i) {
                int a = nextInt() - 1;
                int b = nextInt() - 1;
                long c = nextLong();
                addEdge(a, b, c);
            }
            dist = new BigInteger[n];
            for (int i = 0; i < n; ++ i) {
                dist[i] = INF;
            }
            dist[source] = BigInteger.ZERO;
            int size = n + 1;
            int[] queue = new int[size];
            int head = 0;
            int tail = 0;
            queue[tail ++] = source;
            boolean[] visit = new boolean[n];
            Arrays.fill(visit, false);
            int[] count = new int[n];
            Arrays.fill(count, 0);
            while (head != tail) {
                int u = queue[head];
                head = (head + 1) % size;
                visit[u] = false;
                for (int iter = firstEdge[u]; iter != -1; iter = nextEdge[iter]) {
                    BigInteger tmp = dist[u].add(length[iter]);
                    if (tmp.compareTo(dist[to[iter]]) < 0) {
                        dist[to[iter]] = tmp;
                        if (!visit[to[iter]] && count[to[iter]] <= n) {
                            visit[to[iter]] = true;
                            count[to[iter]] ++;
                            queue[tail] = to[iter];
                            tail = (tail + 1) % size;
                        }
                    }
                }
            }
            head = tail = 0;
            Arrays.fill(visit, false);
            for (int i = 0; i < n; ++ i) {
                if (count[i] > n) {
                    visit[i] = true;
                    queue[tail ++] = i;
                }
            }
            while (head != tail) {
                int u = queue[head ++];
                for (int iter = firstEdge[u]; iter != -1; iter = nextEdge[iter]) {
                    if (!visit[to[iter]]) {
                        visit[to[iter]] = true;
                        queue[tail ++] = to[iter];
                    }
                }
            }
            for (int i = 0; i < n; ++ i) {
                if (visit[i]) {
                    out.println("-");
                } else if (dist[i].compareTo(INF) < 0) {
                    out.println(dist[i]);
                } else {
                    out.println("*");
                }
            }
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

