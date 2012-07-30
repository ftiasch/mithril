import java.util.*;
import java.io.*;
import java.math.*;

public class Main implements Runnable {

    boolean check(int[] a, String s) {
        int carry = 0;
        int ptr = s.length();
        for (int i = a.length - 1; i >= 0 || carry > 0; i--) {
            if (ptr == 0) {
                return false;
            }
            ptr --;
            if (i >= 0) {
                carry += a[i];
            }
            if (carry % 10 != (int)(s.charAt(ptr) - '0')) {
                return false;
            }
            carry /= 10;
        }
        while (ptr > 0 && s.charAt(ptr - 1) == '0') {
            ptr --;
        }
        return ptr == 0;
    }

    BigInteger solve(int n, String[] sum) {
        int[] wys = new int[19];
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                wys[i + j] ++;
            }
        }
        int[] digits = new int[1 << (n - 1)];
        int carry = 0;
        if (sum[n - 1].length() == digits.length) {
            for (int i = 0; i < digits.length; i++) {
                digits[i] = sum[n - 1].charAt(i) - '0';
            }
            carry = 0;
        } else if (sum[n - 1].length() == digits.length + 1) {
            for (int i = 0; i < digits.length; i++) {
                digits[i] = sum[n - 1].charAt(i + 1) - '0';
            }
            carry = sum[n - 1].charAt(0) - '0';
        } else {
            return BigInteger.ZERO;
        }
        int[][] digitsSum = new int[n][];
        for (int i = 0; i < n; i++) {
            digitsSum[i] = new int[1 << i];
        }
        int len = 1 << (n - 1);
        BigInteger ret = BigInteger.ZERO;
        for (int i = 0; i < (1 << (len - 1)); i++) {
            int c = carry;
            boolean valid = true;
            long w = 1;
            for (int j = 0; j < len; j++) {
                c = c * 10 + digits[j];
                int nc = 0;
                if (j + 1 < len && (i >> j & 1) != 0) {
                    nc ++;
                    c --;
                }
                if (c < 0 || c > 18) {
                    valid = false;
                    break;
                }
                w *= wys[c];
                digitsSum[n - 1][j] = c;
                c = nc;
            }
            if (c != 0) {
                valid = false;
            }
            if (valid) {
                for (int j = n - 2; j >= 0; j--) {
                    for (int k = 0; k < (1 << j); k++) {
                        digitsSum[j][k] = digitsSum[j + 1][k] + digitsSum[j + 1][k + (1 << j)];
                    }
                    if (!check(digitsSum[j], sum[j])) {
                        valid = false;
                        break;
                    }
                }
                if (valid) {
                    ret = ret.add(BigInteger.valueOf(w));
                }
            }
        }
        return ret;
    }

    public void run() {
        try {
            in = new BufferedReader(new InputStreamReader(System.in));
            out = new PrintWriter(System.out);
            st = new StringTokenizer("");
            int n = nextInt();
            String[] sum = new String[n];
            for (int i = 0; i < n; i++) {
                sum[i] = next();
                while (sum[i].length() < (1 << i)) {
                    sum[i] = "0" + sum[i];
                }
            }
            System.out.println(solve(n, sum));
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

