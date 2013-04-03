
import java.util.*;
import java.math.*;

public class Main extends Thread {

    final static int[] MAGIC = new int[]{0,0,1,3,6,11,22,52,105,62,425,621,1258,3426,2775,10872,7977,43469,116966,123788,354096,677326,1516496,3363284,2048443,6586003,24488513,35483999,123900646,230833035,216230681};

    boolean isPrime(int n) {
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                return false;
            }
        }
        return n >= 2;
    }

    BigInteger solve(int n) {
        int[] A = new int[n];
        int cnt = 0;
        for (int i = 2; cnt < n; i++) {
            if (isPrime(i)) {
                A[cnt++] = i;
            }
        }
        int mask = MAGIC[n];
        BigInteger a = BigInteger.ONE;
        BigInteger b = BigInteger.ONE;
        for (int i = 0; i < n; i++) {
            if ((mask >> i & 1) != 0) {
                a = a.multiply(BigInteger.valueOf(A[i]));
            } else {
                b = b.multiply(BigInteger.valueOf(A[i]));
            }
        }
        return a.min(b);
    }
    
    public void run() {
        try {
            Scanner sc = new Scanner(System.in);
            int cas = 0;
            while (true) {
                int n = sc.nextInt();
                if (n == 0) {
                    break;
                }
                System.out.println("Case #" + (++cas) + ": " + solve(n));
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
