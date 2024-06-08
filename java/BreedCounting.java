import java.io.File;
import java.io.PrintStream;
import java.util.Scanner;

public class BreedCounting {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(new File("bcount.in"));
        System.setOut(new PrintStream(new File("bcount.out")));
        int n = sc.nextInt();
        int q = sc.nextInt();
        // element of these arrays present the sum from 1..1, 1..2, 1..3, 1..4
        int[] ones = new int[n+1];
        int[] twos = new int[n+1];
        int[] threes = new int[n+1];
        for (int i = 1; i <= n; i++) {
            int kind = sc.nextInt();
            ones[i] = ones[i-1];
            twos[i] = twos[i-1];
            threes[i] = threes[i-1];
            if (kind == 1) ones[i]++;
            else if (kind == 2) twos[i]++;
            else threes[i]++;
        }
        for (int i = 0; i < q; i++) {
            int l = sc.nextInt() - 1;
            int r = sc.nextInt();
            System.out.println((ones[r] - ones[l]) + " " + (twos[r] - twos[l]) + " " + (threes[r] - threes[l]));
        }
    }
}
