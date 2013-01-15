import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
    public void run() {
        Scanner scanner = new Scanner(System.in);
        int k = scanner.nextInt();
        int n = scanner.nextInt();
        BigInteger[][] ways = new BigInteger[n + 1][k + 1];
        for (int i = 0; i <= n; ++ i) {
            Arrays.fill(ways[i], BigInteger.ZERO);
        }
        ways[0][0] = BigInteger.ONE;
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j <= k; ++ j) {
                ways[i + 1][j] = ways[i + 1][j].add(ways[i][j].multiply(BigInteger.valueOf(j)));
                if (j + 1 <= k) {
                    ways[i + 1][j + 1] = ways[i + 1][j + 1].add(ways[i][j].multiply(BigInteger.valueOf(k - j)));
                }
            }
        }
        System.out.println(ways[n][k]);
    }

    public static void main(String[] args) {
        new Main().run();
    }
}
