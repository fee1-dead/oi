import java.util.Scanner;

public class MakeEqual {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        outer: for (int i = 0; i < t; i++) {
            int size = sc.nextInt();
            int[] arr = new int[size];
            int sum = 0;
            for(int pos = 0; pos < size; pos++) {
                arr[pos] = sc.nextInt();
                sum += arr[pos];
            }

            int average = sum / size;
            int excess = 0;
            for (int pos = 0; pos < size; pos++) {
                excess += arr[pos] - average;
                if (excess < 0) {
                    System.out.println("no");
                    continue outer;
                }
            }
            System.out.println("yes");
        }
    }
}
