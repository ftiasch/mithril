// Problem C -- Ballistic
// Author: Xiaoxu Guo
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.PrintWriter;
import java.util.StringTokenizer;
import java.math.BigInteger;

class Solver {
    BigInteger[][] multiply(BigInteger[][] a, BigInteger[][] b) {
        int n = a.length;
        BigInteger[][] c = new BigInteger[n][n];
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                c[i][j] = BigInteger.ZERO;
            }
        }
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                for (int k = 0; k < n; ++ k) {
                    c[i][j] = c[i][j].add(a[i][k].multiply(b[k][j]));
                }
            }
        }
        return c;
    }

    BigInteger getTrace(BigInteger[][] a) {
        int n = a.length;
        BigInteger result = BigInteger.ZERO;
        for (int i = 0; i < n; ++ i) {
            result = result.add(a[i][i]);
        }
        return result;
    }

    void run(InputReader in, PrintWriter out) throws IOException {
        int n = in.nextInt();
        BigInteger[][] a = new BigInteger[n][n];
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                a[i][j] = BigInteger.valueOf(in.nextInt());
            }
        }
        BigInteger[] trace = new BigInteger[n + 1];
        {
            BigInteger[][] m = a;
            for (int i = 1; i <= n; ++ i) {
                trace[i] = getTrace(m);
                m = multiply(m, a);
            }
        }
        BigInteger[] coefficient = new BigInteger[n + 1];
        coefficient[0] = BigInteger.ONE;
        coefficient[1] = trace[1].negate();
        for (int i = 2; i <= n; ++ i) {
            BigInteger result = trace[i].negate();
            for (int j = 1; j < i; ++ j) {
                result = result.subtract(trace[j].multiply(coefficient[i - j]));
            }
            coefficient[i] = result.divide(BigInteger.valueOf(i));
        }
        if ((n & 1) == 1) {
            for (int i = 0; i <= n; ++ i) {
                coefficient[i] = coefficient[i].negate();
            }
        }
        for (int i = 0; i <= n; ++ i) {
            out.println(coefficient[i]);
        }
        out.flush();
    }
}

public class Main {
    public static void main(String args[]) {
        try {
            new Solver().run(new InputReader(System.in), new PrintWriter(System.out));
        } catch (IOException e) {
        }
    }
}

class InputReader {
    BufferedReader reader;
    StringTokenizer tokenizer;

    InputReader(InputStream in) {
        reader = new BufferedReader(new InputStreamReader(in));
        tokenizer = new StringTokenizer("");
    }

    String nextToken() throws IOException {
        while (!tokenizer.hasMoreTokens()) {
            tokenizer = new StringTokenizer(reader.readLine());
        }
        return tokenizer.nextToken();
    }

    int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }
}
