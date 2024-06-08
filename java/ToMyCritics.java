import java.util.Scanner;

public class ToMyCritics {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        for (int i = 0; i < t; i++) {
            int a = sc.nextInt();
            int b = sc.nextInt();
            int c = sc.nextInt();
            if (a + b >= 10 || a + c >= 10 || b + c >= 10)
                System.out.println("yes");
            else
                System.out.println("no");
        }
    }
}