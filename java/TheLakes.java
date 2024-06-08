import java.util.Scanner;

public class TheLakes {
    static int n, m;
    static boolean[][] visited;
    static int[][] depths;
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        for (int i = 0; i < t; i++) {
            testcase(sc);
        }
    }
    public static void testcase(Scanner sc) {
        n = sc.nextInt();
        m = sc.nextInt();
        visited = new boolean[n][m];
        depths = new int[n][m];
        for (int x = 0; x < n; x++) {
            for (int y = 0; y < m; y++) {
                depths[x][y] = sc.nextInt();
            }
        }
        int maxsize = 0;
        for (int x = 0; x < n; x++) {
            for (int y = 0; y < m; y++) {
                maxsize = Math.max(maxsize, dfs(x, y, 0));
            }
        }
        System.out.println(maxsize);
    }
    public static int dfs(int x, int y, int size) {
        if (visited[x][y]) return size;
        if (depths[x][y] == 0) return size;
        size += depths[x][y];
        visited[x][y] = true;
        if (x != 0)
            size = dfs(x - 1, y, size);
        if (x < n - 1)
            size = dfs(x + 1, y, size);
        if (y != 0)
            size = dfs(x, y - 1, size);
        if (y < m - 1)
            size = dfs(x, y + 1, size);    
        return size;
    }
}
