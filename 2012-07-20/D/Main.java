// Problem D -- Avoiding Partitions
// Author: Jingbo Shang
import java.io.*;
import java.util.*;
import java.math.*;

public class Main implements Runnable {

    int[] father;

    int Find(int p) {
        if (father[p] == p)
            return p;
        return (father[p] = Find(father[p]));
    }

    public void run() {
        try {
            Scanner scanner = new Scanner(System.in);
            int n = scanner.nextInt();
            int l = scanner.nextInt();
            int[][] a=new int[l][];

            father = new int[n + 1];
            for (int i=0;i<l;++i) {
                int m=scanner.nextInt();
                a[i]=new int[m];
                for (int j=0;j<m;++j)
                    a[i][j]=scanner.nextInt();
            }
            
            BigInteger[][] f=new BigInteger[n+1][n+1];
            BigInteger[] g=new BigInteger[n+1];
            for (int i=0;i<=n;++i){
                g[i]=BigInteger.ZERO;
                for (int j=0;j<=n;++j)
                    f[i][j]=BigInteger.ZERO;
            }
            f[1][1]=BigInteger.ONE;
            for (int i=1;i<=n;++i){
                for (int j=1;j<=i;++j){
                    if (i+1<=n){
                        f[i+1][j]=f[i+1][j].add(f[i][j].multiply(BigInteger.valueOf(j)));
                        f[i+1][j+1]=f[i+1][j+1].add(f[i][j]);
                    }
                    g[i]=g[i].add(f[i][j]);
                }
            }

            BigInteger ans = BigInteger.ZERO;
            
            for (int mask=0;mask<1<<l;++mask){
                for (int i=1;i<=n;++i) father[i]=i;
                int sign=1;
                for (int i=0;i<l;++i)if ((mask>>i&1)!=0){
                    for (int j=0;j<a[i].length;++j)
                        father[Find(a[i][j])]=Find(a[i][0]);
                    sign=-sign;
                }
                
                int N=0;
                for (int i=1;i<=n;++i)
                if (Find(i)==i) ++N;
                
                BigInteger mul=BigInteger.valueOf(sign);
                ans = ans.add(g[N].multiply(mul));
            }
            
            System.out.println(ans);
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }

    public static void main(String[] args) {
        new Thread(new Main()).run();
    }
}
