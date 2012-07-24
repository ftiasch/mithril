import java.io.*;
import java.util.*;
import java.math.*;

public class Main implements Runnable {
    public void run() {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int m = scanner.nextInt();
        int limit = scanner.nextInt();
        int[] count = new int[m + 1];
        Arrays.fill(count, 0);
        for (int i = 0; i < n; ++ i) {
            int c = scanner.nextInt();
            count[c] ++;
        }
        BigInteger[][] choose = new BigInteger[n + 1][n + 1];
        for (int i = 0; i <= n; ++ i) {
            for (int j = 0; j <= n; ++ j) {
                choose[i][j] = BigInteger.ZERO;
            }
        }
        for (int i = 0; i <= n; ++ i) {
            choose[i][0] = BigInteger.ONE;
            for (int j = 1; j <= i; ++ j) {
                choose[i][j] = choose[i - 1][j].add(choose[i - 1][j - 1]);
            }
        }
        BigInteger[][] ways = new BigInteger[m + 1][limit + 1];
        for (int i = 0; i <= m; ++ i) {
            for (int j = 0; j <= limit; ++ j) {
                ways[i][j] = BigInteger.ZERO;
            }
        }
        ways[0][0] = BigInteger.ONE;
        for (int i = 1; i <= m; ++ i) {
            for (int j = 0; j <= limit; ++ j) {
                for (int k = 0; k <= count[i] && k <= j; ++ k) {
                    ways[i][j] = ways[i][j].add(ways[i - 1][j - k].multiply(choose[j][k]));
                }
            }
        }
        System.out.println(ways[m][limit]);
    }

    public static void main(String[] args) {
        new Thread(new Main()).run();
    }
}
