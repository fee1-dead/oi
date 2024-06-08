import java.util.Scanner;

public class BlankSpace {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        for (int i = 0; i < t; i++) {
            int size = sc.nextInt();
            int counter = 0;
            int max = 0;
            for (int a = 0; a < size; a++) {
                if (sc.nextInt() == 0) {
                    counter++;
                } else {
                    max = Math.max(max, counter);
                    counter = 0;
                }
            }
            max = Math.max(max, counter);
            System.out.println(max);
        }
    }
}
