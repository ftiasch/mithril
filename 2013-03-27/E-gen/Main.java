import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
    Scanner reader;

    Main() {
        reader = new Scanner(System.in);
    }

    final static int N = 150;

    static BigInteger[][] binom = new BigInteger[N + 1][];

    static {
        for (int i = 0; i <= N; i++) {
            binom[i] = new BigInteger[i + 1];
            binom[i][0] = binom[i][i] = BigInteger.ONE;
            for (int j = 1; j < i; j++) {
                binom[i][j] = binom[i-1][j-1].add(binom[i-1][j]);
            }
        }
    }

    BigInteger[][] memoTree = new BigInteger[N + 1][N + 1];

    BigInteger goTree(int nodes, int degreeLimit) {
        if (degreeLimit < 0) {
            return BigInteger.ZERO;
        }
        if (nodes == 0) {
            return BigInteger.ONE;
        }
        if (memoTree[nodes][degreeLimit] != null) {
            return memoTree[nodes][degreeLimit];
        }
        return memoTree[nodes][degreeLimit] = goTree(nodes, degreeLimit - 1).add(goTrees(nodes - 1, degreeLimit, degreeLimit));
    }

    BigInteger[][][] memoTrees = new BigInteger[N + 1][N + 1][N + 1];

    BigInteger goTrees(int nodes, int trees, int degreeLimit) {
        if (trees > nodes) {
            return BigInteger.ZERO;
        }
        if (trees == 0) {
            return nodes == 0 ? BigInteger.ONE : BigInteger.ZERO;
        }
        if (memoTrees[nodes][trees][degreeLimit] != null) {
            return memoTrees[nodes][trees][degreeLimit];
        }
        BigInteger ret = BigInteger.ZERO;
        for (int s = 1; s <= nodes; s++) {
            ret = ret.add(goTree(s, degreeLimit).multiply(goTrees(nodes - s, trees - 1, degreeLimit)).multiply(binom[nodes - 1][s - 1]));
        }
        return memoTrees[nodes][trees][degreeLimit] = ret;
    }

    public void run() {
        for (int n = 1; n <= N; n++) {
            System.out.println("ans[" + n + "]=\"" + goTree(n, n) + "\";");
        }
    }

    public static void main(String[] args) {
        new Main().run();
    }
}
