import java.util.*;
import java.io.*;
import java.math.*;

public class Main implements Runnable {

    BigInteger solve(int n, int[] c) {
        BigInteger[] wys = new BigInteger[n + 1];
        Arrays.fill(wys, BigInteger.ZERO);
        wys[0] = BigInteger.ONE;
        for (int ci : c) {
            BigInteger[] nwys = new BigInteger[n + 1];
            Arrays.fill(nwys, BigInteger.ZERO);
            for (int i = 0; i <= n; i++) {
                BigInteger now = wys[i];
                for (int j = 0; j <= ci && i + j <= n; j++) {
                    nwys[i + j] = nwys[i + j].add(now);
                    now = now.multiply(BigInteger.valueOf(i + j + 1));
                    now = now.divide(BigInteger.valueOf(j + 1));
                }
            }
            wys = nwys;
        }
        return wys[n];
    }

	public void run() {
		try {
			in = new BufferedReader(new InputStreamReader(System.in));
			out = new PrintWriter(System.out);
			st = null;
            int m = nextInt();
            int n = nextInt();
            int[] c = new int[m];
            for (int i = 0; i < m; i++) {
                c[i] = nextInt();
            }
            BigInteger res = solve(n, c);
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
		while (st == null || !st.hasMoreTokens()) {
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
