import java.io.*;
import java.util.*;
import java.math.*;

public class Main implements Runnable {

    BufferedReader reader;
    PrintWriter writer;
    StringTokenizer tokenizer;

    Main() {
        reader = new BufferedReader(new InputStreamReader(System.in));
        writer = new PrintWriter(System.out);
        tokenizer = new StringTokenizer("");
    }

    public void run() {
        try {
            int n = nextInt();
            int m = nextInt();
            int kk = nextInt();
            int c = nextInt();
            int l = nextInt();
            String[] wheels = new String[n];
            for (int i = 0; i < n; ++ i) {
                wheels[i] = nextToken();
            }
            String[] figures = new String[c];
            int[] score = new int[c];
            for (int i = 0; i < c; ++ i) {
                figures[i] = nextToken();
                score[i] = nextInt();
            }
//for (int i = 0; i < n; ++ i) {
//    System.out.println(wheels[i]);
//}
//for (int i = 0; i < c; ++ i) {
//    System.out.println(figures[i]);
//}
            Fraction result = new Fraction(BigInteger.ZERO, BigInteger.ONE);
            for (int j = 0; j < c; ++ j) {
                Fraction probability = new Fraction(BigInteger.ONE, BigInteger.ONE);
                for (int i = 0; i < n; ++ i) {
                    int count = 0;
                    for (int k = 0; k < m; ++ k) {
                        if (figures[j].charAt(i) == '*' || figures[j].charAt(i) == wheels[i].charAt(k)) {
                            count ++;
                        }
                    }
                    probability = probability.multiply(new Fraction(BigInteger.valueOf(count), BigInteger.valueOf(m)));
                }
                result = result.add(probability.multiply(new Fraction(BigInteger.valueOf(score[j]), BigInteger.ONE)));
            }
            result.numerator = result.numerator.subtract(result.denominator);
            if (result.numerator.compareTo(BigInteger.ZERO) <= 0) {
                writer.println("0/1");
                writer.println("0");
            } else {
                writer.println(String.format("%d/%d", result.numerator, result.denominator));
                writer.println("1");
                writer.println("1");
            }
            writer.flush();
        } catch (IOException e) {
        }
    }

    public static void main(String[] args) {
        new Thread(new Main()).run();
    }

    String nextToken() throws IOException {
        while (!tokenizer.hasMoreTokens()) {
            tokenizer = new StringTokenizer(reader.readLine());
        }
        return tokenizer.nextToken();
    }

    int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }
}

class Fraction {
    BigInteger numerator, denominator;

    Fraction(BigInteger numerator, BigInteger denominator) {
        BigInteger g = numerator.gcd(denominator);
        this.numerator = numerator.divide(g);
        this.denominator = denominator.divide(g);
    }

    Fraction add(Fraction other) {
        return new Fraction(numerator.multiply(other.denominator).add(other.numerator.multiply(denominator)), denominator.multiply(other.denominator));
    }

    Fraction multiply(Fraction other) {
        return new Fraction(numerator.multiply(other.numerator), denominator.multiply(other.denominator));
    }
}
