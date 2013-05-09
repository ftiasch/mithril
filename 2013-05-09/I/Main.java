
import java.math.*;
import java.util.*;
import java.io.*;

public class Main implements Runnable { 

    BigInteger[] ways;
    int n;

    class State {
        int[][] parts;

        State(int[] order) {
            parts = new int[1][];
            parts[0] = order.clone();
        }

        State(int[][] parts) {
            this.parts = parts;
        }

        void splitBy(int i, int[] splits, int[] num) {
            int[][] nparts = new int[parts.length - 1 + (num[0] > 0 ? 1 : 0) + (num[1] > 0 ? 1 : 0) + (num[2] > 0 ? 1 : 0)][];
            int sz = 0;
            for (int u = 0; u < parts.length; u++) {
                if (u != i) {
                    nparts[sz++] = parts[u];
                }
            }
            for (int u = 0; u < 3; u++) {
                if (num[u] > 0) {
                    nparts[sz] = new int[num[u]];
                    for (int v = 0; v < num[u]; v++) {
                        nparts[sz][v] = parts[i][(splits[u] + 1 + v) % parts[i].length];
                    }
                    sz++;
                }
            }
            assert sz == nparts.length;
            parts = nparts;
        }

        BigInteger splitBy(BigInteger ret, int[] triple) {
            assert ret.signum() >= 0;
            int x = Integer.MAX_VALUE;
            for (int[] part : parts) {
                for (int value : part) {
                    if (value < x) {
                        x = value;
                    }
                }
            }
            for (int i = 0; i < parts.length; i++) {
                boolean foundX = false;
                for (int p : parts[i]) {
                    if (p == x) {
                        foundX = true;
                    }
                }
                if (!foundX) {
                    continue;
                }
                BigInteger mul = BigInteger.ONE;
                for (int j = 0; j < parts.length; j++) {
                    if (i != j) {
                        mul = mul.multiply(ways[parts[j].length / 3]);
                    }
                }
                int[] posInPart = new int[n * 3];
                Arrays.fill(posInPart, -1);
                for (int j = 0; j < parts[i].length; j++) {
                    posInPart[parts[i][j]] = j;
                }
                int[] sorted = parts[i].clone();
                Arrays.sort(sorted);
                assert x == sorted[0];
                int m = sorted.length;
                for (int j = 1; j < m; j++) {
                    for (int k = j + 1; k < m; k++) {
                        int[] splits = new int[]{posInPart[sorted[0]], posInPart[sorted[j]], posInPart[sorted[k]]};
                        Arrays.sort(splits);
                        int[] num = new int[]{splits[1] - splits[0] - 1, splits[2] - splits[1] - 1, splits[0] - splits[2] - 1 + m};
                        if (num[0] % 3 == 0 && num[1] % 3 == 0 && num[2] % 3 == 0) {
                            BigInteger delta = ways[num[0] / 3].multiply(ways[num[1] / 3]).multiply(ways[num[2] / 3]).multiply(mul);
                            if (ret.compareTo(delta) < 0) {
                                splitBy(i, splits, num);
                                triple[0] = sorted[0];
                                triple[1] = sorted[j];
                                triple[2] = sorted[k];
                                return ret;
                            } else {
                                ret = ret.subtract(delta);
                            }
                        }
                    }
                }
                assert false;
            }
            assert false;
            return null;
        }

        BigInteger splitBy(int x, int y, int z) {
            assert x < y && y < z;
            for (int i = 0; i < parts.length; i++) {
                boolean foundX = false, foundY = false, foundZ = false;
                for (int p : parts[i]) {
                    if (p == x) {
                        foundX = true;
                    } else if (p == y) {
                        foundY = true;
                    } else if (p == z) {
                        foundZ = true;
                    }
                }
                if (!foundX) {
                    continue;
                }
                assert foundY && foundZ;
                BigInteger mul = BigInteger.ONE;
                for (int j = 0; j < parts.length; j++) {
                    if (i != j) {
                        mul = mul.multiply(ways[parts[j].length / 3]);
                    }
                }
                int[] posInPart = new int[n * 3];
                Arrays.fill(posInPart, -1);
                for (int j = 0; j < parts[i].length; j++) {
                    posInPart[parts[i][j]] = j;
                }
                int[] sorted = parts[i].clone();
                Arrays.sort(sorted);
                assert x == sorted[0];
                BigInteger ret = BigInteger.ZERO;
                int m = sorted.length;
                for (int j = 1; j < m; j++) {
                    for (int k = j + 1; k < m; k++) {
                        int[] splits = new int[]{posInPart[sorted[0]], posInPart[sorted[j]], posInPart[sorted[k]]};
                        Arrays.sort(splits);
                        int[] num = new int[]{splits[1] - splits[0] - 1, splits[2] - splits[1] - 1, splits[0] - splits[2] - 1 + m};
                        if (num[0] % 3 == 0 && num[1] % 3 == 0 && num[2] % 3 == 0) {
                            if (sorted[j] == y && sorted[k] == z) {
                                splitBy(i, splits, num);
                                return ret;
                            } else {
                                ret = ret.add(ways[num[0] / 3].multiply(ways[num[1] / 3]).multiply(ways[num[2] / 3]).multiply(mul));
                            }
                        }
                    }
                }
                assert false;
            }
            assert false;
            return null;
        }
    }

    public void run() {
        try {
            Scanner sc = new Scanner(new FileReader("triconnect.in"));
            PrintWriter out = new PrintWriter(new FileWriter("triconnect.out"));
            n = sc.nextInt();
            ways = new BigInteger[n + 1];
            ways[0] = BigInteger.ONE;
            for (int i = 1; i <= n; i++) {
                ways[i] = BigInteger.ZERO;
                for (int x = 1; x < i * 3; x += 3) {
                    for (int y = x + 1; y < i * 3; y += 3) {
                        ways[i] = ways[i].add(ways[(x - 0) / 3].multiply(ways[(y - x) / 3]).multiply(ways[(i * 3 - y) / 3]));
                    }
                }
            }
            int[] orderA = new int[n * 3];
            int[][] partitionA = new int[n][3];
            int[] orderB = new int[n * 3];
            for (int i = 0; i < n * 3; i++) {
                orderA[i] = sc.nextInt() - 1;
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < 3; j++) {
                    partitionA[i][j] = sc.nextInt() - 1;
                }
            }
            for (int i = 0; i < n * 3; i++) {
                orderB[i] = sc.nextInt() - 1;
            }
            BigInteger orderNum = BigInteger.ZERO;
            State s = new State(orderA);
            for (int[] triple : partitionA) {
                orderNum = orderNum.add(s.splitBy(triple[0], triple[1], triple[2]));
            }
            int[][] partitionB = new int[n][3];
            s = new State(orderB);
            for (int i = 0; i < n; i++) {
                orderNum = s.splitBy(orderNum, partitionB[i]);
            }
            for (int i = 0; i < n; i++) {
                out.println((1 + partitionB[i][0]) + " " + (1 + partitionB[i][1]) + " " + (1 + partitionB[i][2]));
            }
            out.close();
        } catch (Exception ex) {
            ex.printStackTrace();
            System.exit(-1);
        }
    }

    static void debug(Object...os) {
        System.err.println(Arrays.deepToString(os));
    }

    public static void main(String[] args) {
        new Thread(new Main()).start();
    }
}
