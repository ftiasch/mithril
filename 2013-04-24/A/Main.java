import java.io.*;
import java.util.*;
import java.math.*;

class Main {
    BufferedReader reader;
    StringTokenizer tokenizer;
    PrintWriter writer;

    Main() {
        reader = new BufferedReader(new InputStreamReader(System.in));
        tokenizer = new StringTokenizer("");
        writer = new PrintWriter(System.out);
    }

    String next() throws IOException {
        while (!tokenizer.hasMoreTokens()) {
            tokenizer = new StringTokenizer(reader.readLine());
        }
        return tokenizer.nextToken();
    }

    int nextInt() throws IOException {
        return Integer.parseInt(next());
    }

    int n, s;

    BigInteger b(long value) {
        return BigInteger.valueOf(value);
    }

    class Coin implements Comparable <Coin> {
        int id, x, y, v, c;

        Coin(int id, int x, int y, int v, int c) {
            this.id = id;
            this.x = x;
            this.y = y;
            this.v = v;
            this.c = c;
        }

        public int compareTo(Coin other) {
            BigInteger d = b(other.v).multiply(b((long)v * x - (long)s * y))
                .subtract(b(v).multiply(b((long)other.v * other.x - (long)s * other.y)));
            if (d.signum() != 0) {
                return d.signum();
            }
            d = b(other.v).multiply(b((long)v * x + (long)s * y))
                .subtract(b(v).multiply(b((long)other.v * other.x + (long)s * other.y)));
            return -d.signum();
        }
    }

    class ByY implements Comparator <Coin> {
        public int compare(Coin a, Coin b) {
            BigInteger d = b(b.v).multiply(b((long)a.v * a.x + (long)s * a.y))
                .subtract(b(a.v).multiply(b((long)b.v * b.x + (long)s * b.y)));
            return d.signum();
        }
    }

    ArrayList <Coin> unique(ArrayList <Coin> array) {
        ArrayList <Coin> newArray = new ArrayList <Coin>();
        ByY comparator = new ByY();
        for (Coin coin : array) {
            if (newArray.isEmpty() || comparator.compare(newArray.get(newArray.size() - 1), coin) != 0) {
                newArray.add(coin);
            }
        }
        return newArray;
    }

    ArrayList <Coin> coins;

    int find(ArrayList <Coin> values, Coin coin) {
        ByY comparator = new ByY();
        int low = 0;
        int high = values.size() - 1;
        while (low < high) {
            int middle = low + high + 1 >> 1;
            if (comparator.compare(values.get(middle), coin) <= 0) {
                low = middle;
            } else {
                high = middle - 1;
            }
        }
        return low;
    }

    public void run() {
        try {
            n = nextInt();
            s = nextInt();
            coins = new ArrayList <Coin>();
            for (int i = 0; i < n; ++ i) {
                int x = nextInt();
                int y = nextInt();
                int v = nextInt();
                int c = nextInt();
                if ((long)Math.abs(x) * v <= (long)s * y) {
                    coins.add(new Coin(i, x, y, v, c));
                }
            }
        } catch (IOException ex) {
        }
        if (coins.isEmpty()) {
            writer.println(0);
            writer.println(0);
            writer.println();
        } else {
            Collections.sort(coins);
            ArrayList <Coin> values = (ArrayList <Coin>)coins.clone();
            Collections.sort(values, new ByY());
            values = unique(values);
            long[] maximum = new long[coins.size()];
            int[] back = new int[coins.size()];
            long[] memory = new long[values.size()];
            Arrays.fill(memory, 0);
            int[] choice = new int[values.size()];
            Arrays.fill(choice, -1);
            for (int i = 0; i < coins.size(); ++ i) {
                Coin coin = coins.get(i);
                int id = find(values, coin);
                maximum[i] = coin.c;
                back[i] = -1;
                for (int k = id; k < values.size(); k += ~k & k + 1) {
                    if (memory[k] + coin.c > maximum[i]) {
                        maximum[i] = memory[k] + coin.c;
                        back[i] = choice[k];
                    }
                }
                for (int k = id; k >= 0; k -= ~k & k + 1) {
                    if (maximum[i] > memory[k]) {
                        memory[k] = maximum[i];
                        choice[k] = i;
                    }
                }
            }
            int i = 0;
            for (int k = 0; k < coins.size(); ++ k) {
                if (maximum[k] > maximum[i]) {
                    i = k;
                }
            }
            writer.println(maximum[i]);
            ArrayList <Integer> answer = new ArrayList <Integer>();
            while (i != -1) {
                answer.add(coins.get(i).id);
                i = back[i];
            }
            writer.println(answer.size());
            for (int k = 0; k < answer.size(); ++ k) {
                writer.print(String.format("%d%c", answer.get(k) + 1, k == answer.size() - 1 ? '\n' : ' '));
            }
        }
        writer.close();
    }

    public static void main(String[] args) {
        new Main().run();
    }
}
