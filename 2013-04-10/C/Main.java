import java.io.*;
import java.util.*;
import java.math.*;

public class Main extends Thread {

    public void run() {
        try {
            Scanner sc = new Scanner(System.in);
            int n = sc.nextInt();
            int m = sc.nextInt();
            BigInteger val = sc.nextBigInteger();
            BigInteger cnm = BigInteger.ONE;
            for (int i = 0; i < m; i++) {
                cnm = cnm.multiply(BigInteger.valueOf(n - i)).divide(BigInteger.valueOf(i + 1));
            }
            while (n > 0) {
                BigInteger cn1m1 = cnm.multiply(BigInteger.valueOf(m)).divide(BigInteger.valueOf(n));
                BigInteger cn1m = cnm.subtract(cn1m1);
                n --;
                if (val.compareTo(cn1m) < 0) {
                    System.out.print('0');
                    cnm = cn1m;
                } else {
                    System.out.print('1');
                    val = val.subtract(cn1m);
                    cnm = cn1m1;
                    m --;
                }
            }
            System.out.println();
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }

    public static void main(String[] args) {
        new Thread(new Main()).start();
    }
}
