// Problem H -- Straight or Flush
// Author: Bin Jin
import java.util.*;
import java.math.*;

public class Main implements Runnable {

    final static int MAXN = 400;

    static BigInteger[][] comb = new BigInteger[MAXN + 1][];

    static {
        for (int i = 0; i <= MAXN; i++) {
            comb[i] = new BigInteger[i + 1];
            comb[i][0] = comb[i][i] = BigInteger.ONE;
            for (int j = 1; j < i; j++)
                comb[i][j] = comb[i-1][j-1].add(comb[i-1][j]);
        }
    }

    int r;
    int s;
    int d;
    int c;

    BigInteger solveFlush() {
        BigInteger[][][] wys = new BigInteger[s+1][d+1][2];
        for (int i = 0; i <= s; i++)
            for (int j = 0; j <= d; j++)
                Arrays.fill(wys[i][j], BigInteger.ZERO);
        wys[0][0][0] = BigInteger.ONE;
        for (int i = 0; i < s; i++)
            for (int j = 0; j <= d; j++)
                for (int k = 0; k < 2; k++) {
                    if (wys[i][j][k].signum() <= 0)
                        continue;
                    for (int z = 0; j + z <= d && z <= r; z++) {
                        int nk = k > 0 || z >= c ? 1 : 0;
                        wys[i+1][j+z][nk] = wys[i+1][j+z][nk].add(wys[i][j][k].multiply(comb[r][z]));
                    }
                }
        return wys[s][d][1];
    }

    BigInteger solveStraight() {
        BigInteger[][][][] wys = new BigInteger[r+1][d+1][c+1][2];
        for (int i = 0; i <= r; i++)
            for (int j = 0; j <= d; j++)
                for (int k = 0; k <= c; k++)
                    Arrays.fill(wys[i][j][k], BigInteger.ZERO);
        wys[0][0][0][0] = BigInteger.ONE;
        for (int i = 0; i < r; i++)
            for (int j = 0; j <= d; j++)
                for (int k = 0; k <= c; k++)
                    for (int l = 0; l < 2; l++) {
                        if (wys[i][j][k][l].signum() <= 0)
                            continue;
                        for (int z = 0; j + z <= d && z <= s; z++) {
                            int nk = z == 0 ? 0 : Math.min(k + 1, c);
                            int nl = l > 0 || nk == c ? 1 : 0;
                            wys[i+1][j+z][nk][nl] = wys[i+1][j+z][nk][nl].add(wys[i][j][k][l].multiply(comb[s][z]));
                        }
                    }
        BigInteger ret = BigInteger.ZERO;
        for (int i = 0; i <= c; i++)
            ret = ret.add(wys[r][d][i][1]);
        return ret;
    }

    void printFraction(BigInteger p, BigInteger q) {
        BigInteger g = p.gcd(q);
        System.out.println(p.divide(g) + "/" + q.divide(g));
    }

    public void run() {
        try {
            Scanner sc = new Scanner(System.in);
            boolean first = true;
            while (true) {
                if (!first) {
                    System.out.println();
                }
                first = false;
                r = sc.nextInt();
                s = sc.nextInt();
                d = sc.nextInt();
                c = sc.nextInt();
                if (r == 0 && s == 0 && d == 0 && c == 0)
                    break;
                BigInteger all = comb[r * s][d];
                BigInteger flush = solveFlush();
                BigInteger straight = solveStraight();
                printFraction(straight, all);
                printFraction(flush, all);
            }
        } catch (Exception ex) {
            ex.printStackTrace();
            System.exit(-1);
        }
    }

    public static void main(String[] args) {
        new Thread(new Main()).start();
    }
}
