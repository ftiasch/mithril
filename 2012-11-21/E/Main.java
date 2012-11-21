
import java.util.*;
import java.io.*;
import java.math.*;

public class Main { 

    long inverse(long a, int mod) {
        return a <= 1 ? a : (mod - mod / a) * inverse(mod % a, mod) % mod;
    }

    boolean check(int n, int[][] matrix, int mod) {
        long[][] ma = new long[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                ma[i][j] = (matrix[i][j] % mod + mod) % mod;
            }
        }
        long det = 1;
        for (int i = 0; i < n; i++) {
            int pivot = i;
            while (pivot < n && ma[pivot][i] == 0) {
                pivot ++;
            }
            if (pivot == n) {
                return false;
            }
            if (pivot != i) {
                det = (mod - det) % mod;
                long[] tmp = ma[i];
                ma[i] = ma[pivot];
                ma[pivot] = tmp;
            }
            det = det * ma[i][i] % mod;
            long inv = inverse(ma[i][i], mod);
            for (int j = i + 1; j < n; j ++) {
                long times = ma[j][i] * inv % mod;
                for (int k = i; k < n; k++) {
                    ma[j][k] = (ma[j][k] - ma[i][k] * times % mod + mod) % mod;
                }
            }
        }
        return det == 1 || det + 1 == mod;
    }

    boolean isPrime(int prime) {
        for (int f = 2; f * f <= prime; f++) {
            if (prime % f == 0) {
                return false;
            }
        }
        return true;
    }

    boolean check(int n, int[][] matrix) {
        int prime = 987654321;
        for (int it = 0; it < 10; ++it) {
            for (++prime; !isPrime(prime); ) {
                ++prime;
            }
            if (!check(n, matrix, prime)) {
                return false;
            }
        }
        return true;
    }

    public void run() {
        try {
            Scanner sc = new Scanner(System.in);
            int n = sc.nextInt();
            int[][] matrix = new int[n][n];
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    matrix[i][j] = sc.nextInt();
                }
            }
            if (check(n, matrix)) {
                System.out.println("Death");
            } else {
                System.out.println("Power of magic saves lives");
            }
        } catch (Exception ex) {
            ex.printStackTrace();
            System.exit(-1);
        }
    }

    public static void main(String[] args) {
        new Main().run();
    }
}
