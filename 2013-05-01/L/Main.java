import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
    Scanner scanner;

    Main() {
        scanner = new Scanner(System.in);
    }

    final static int MOD = 1000000000 + 7;

    int n;
    BigInteger[] fib;

    int[] factorize(BigInteger u) {
        int[] ret = new int[n + 1];
        for (int i = n; i >= 2; -- i) {
            if (u.compareTo(fib[i]) > 0) {
                u = u.subtract(fib[i]);
                ret[i] = 1;
            }
        }
        return ret;
    }

    public void run() {
        n = scanner.nextInt();
        if (n == 1 || n == 2) {
            System.out.println("0 1");
            return;
        }
        BigInteger u = new BigInteger(scanner.next());
        BigInteger v = new BigInteger(scanner.next());
        fib = new BigInteger[n + 1];
        fib[1] = fib[2] = BigInteger.ONE;
        for (int i = 3; i <= n; ++ i) {
            fib[i] = fib[i - 1].add(fib[i - 2]);
        }
        int[] fu = factorize(u);
        int[] fv = factorize(v);
        int dist = 0;
        ArrayList<Integer> diffPos = new ArrayList<Integer>();
        for (int i = 2; i <= n; ++ i) {
            if (fu[i] != fv[i]) {
                diffPos.add(i);
            }
        }
        Integer[] diff = diffPos.toArray(new Integer[0]);
        if (diff.length == 0) {
            System.out.println("0 1");
            return;
        }
        int[] wys = new int[]{1};
        for (int i = 1; i < diff.length; i++) {
            int flag = 0;
            if (diff[i - 1] + 1 == diff[i] && fu[diff[i - 1]] != fu[diff[i]]) {
                if (fu[diff[i]] == 1) {
                    // i first
                    flag = 1;
                } else {
                    // i - 1 first
                    flag = -1;
                }
            }
            int[] psum = new int[wys.length + 1];
            psum[0] = 0;
            for (int j = 0; j < wys.length; j++) {
                psum[j + 1] = (psum[j] + wys[j]) % MOD;
            }
            wys = new int[i + 1];
            if (flag == 0) {
                for (int j = 0; j <= i; j++) {
                    wys[j] = psum[i];
                }
            } else if (flag == 1) {
                for (int j = 0; j <= i; j++) {
                    wys[j] = (psum[i] - psum[j] + MOD) % MOD;
                }
            } else {
                for (int j = 0; j <= i; j++) {
                    wys[j] = psum[j];
                }
            }
        }
        int ans = 0;
        for (int wi : wys) {
            ans = (ans + wi) % MOD;
        }
        System.out.println(diff.length + " " + ans);
    }

    public static void main(String[] args) {
        new Main().run();
    }
}
