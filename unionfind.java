import java.util.*;

class UnionFind {
    int[] parent, rank;

    UnionFind(int n) {
        parent = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 1;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void union(int x, int y) {
        int xr = find(x), yr = find(y);
        if (xr != yr) {
            if (rank[xr] > rank[yr]) {
                parent[yr] = xr;
            } else if (rank[xr] < rank[yr]) {
                parent[xr] = yr;
            } else {
                parent[yr] = xr;
                rank[xr]++;
            }
        }
    }

    boolean connected(int x, int y) {
        return find(x) == find(y);
    }
}

public class unionfind {
    public static void main(String[] args) {
        Scanner inputtt = new Scanner(System.in);
        int n = inputtt.nextInt();
        int q = inputtt.nextInt();
        UnionFind uf = new UnionFind(n);
        StringBuilder sb = new StringBuilder();
        while (q-- > 0) {
            int t = inputtt.nextInt(), u = inputtt.nextInt(), v = inputtt.nextInt();
            if (t == 0) {
                uf.union(u, v);
            } else {
                sb.append(uf.connected(u, v) ? "1\n" : "0\n");
            }
        }
        System.out.print(sb);
    }
}


