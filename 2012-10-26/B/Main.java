
import java.util.*;
import java.io.*;
import java.math.*;

public class Main {

    static BigInteger[][] choose;

    final static int MAXN = 222;

    static {
        choose = new BigInteger[MAXN][MAXN];
        for (int i = 0; i < MAXN; i++) {
            choose[i][i] = choose[i][0] = BigInteger.ONE;
            for (int j = 1; j < i; j++) {
                choose[i][j] = choose[i-1][j].add(choose[i-1][j-1]);
            }
        }
    }

    BigInteger solve(int p, int[][] children, int[] size) {
        size[p] = 1;
        BigInteger ret = BigInteger.ONE;
        int[] sz = new int[2];
        for (int i = 0; i < 2; i++) {
            int q = children[p][i];
            if (q >= 0) {
                ret = ret.multiply(solve(q, children, size));
                size[p] += size[q];
                sz[i] = size[q];
            } else {
                sz[i] = 0;
            }
        }
        ret = ret.multiply(choose[sz[0] + sz[1]][sz[0]]);
        return ret;
    }

    public void run() {
        try {
            Scanner sc = new Scanner(System.in);
            int n = sc.nextInt();
            int[][] children = new int[n][2];
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < 2; j++) {
                    children[i][j] = sc.nextInt() - 1;
                }
            }
            int[] size = new int[n];
            BigInteger res = solve(0, children, size);
            System.out.println(res);
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    public static void main(String[] args) {
        new Main().run();
    }
}
