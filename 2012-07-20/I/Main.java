import java.util.*;
import java.io.*;

class Triangle {
    int x;
    int y;

    Triangle(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public boolean equals(Object o) {
        if (o == null || !(o instanceof Triangle))
            return false;
        Triangle t = (Triangle)o;
        return x == t.x && y == t.y;
    }

    public int hashCode() {
        return x * 4423 + y;
    }

    boolean getSide() {
        return x % 2 == 0;
    }

    Triangle[] getNeighbors() {
        Triangle[] nears = new Triangle[3];
        nears[0] = new Triangle(x + 1, y);
        nears[1] = new Triangle(x - 1, y);
        if (x % 2 != 0) {
            nears[2] = new Triangle(x - 1, y + 1);
        } else {
            nears[2] = new Triangle(x + 1, y - 1);
        }
        return nears;
    }

    public String toString() {
        return "(" + x + ", " + y + ")";
    }
}

class DinicSolver {

    class Edge {
        int dest;
        int flow;
        int cap;

        Edge nextEdge;
        Edge revEdge;

        Edge(int dest, int cap, Edge nextEdge) {
            this.dest = dest;
            this.cap = cap;
            this.flow = 0;
            this.nextEdge = nextEdge;
            this.revEdge = null;
        }

        boolean isFull() {
            return cap == flow;
        }

        int capacity() {
            return cap - flow;
        }

        public String toString() {
            return revEdge.dest + "->" + dest + " (" + flow + "/" + cap + ")";
        }
    }

    int n;
    Edge[] firstEdge;

    public DinicSolver(int n) {
        this.n = n;
        this.firstEdge = new Edge[n];
        this.level = new int[n];
    }

    public Edge addEdge(int a, int b, int c, int bc) {
        Edge ab = new Edge(b, c, firstEdge[a]);
        Edge ba = new Edge(a, bc, firstEdge[b]);
        ab.revEdge = ba;
        ba.revEdge = ab;
        firstEdge[a] = ab;
        firstEdge[b] = ba;
        return ab;
    }


    public void clearFlow() {
        for (int i = 0; i < n; i++) {
            for (Edge e = firstEdge[i]; e != null; e = e.nextEdge) {
                e.flow = 0;
            }
        }
    }

    public int maxFlow(int src, int sink) {
        this.src = src;
        this.sink = sink;
        int ret = 0;
        while (bfs()) {
            curEdge = firstEdge.clone();
            ret += dfs(src, Integer.MAX_VALUE);
        }
        return ret;
    }

    private boolean bfs() {
        Arrays.fill(level, -1);
        level[sink] = 0;
        ArrayList<Integer> queue = new ArrayList<Integer>();
        queue.add(sink);
        for (int i = 0; i < queue.size(); i++) {
            int p = queue.get(i);
            for (Edge e = firstEdge[p]; e != null; e = e.nextEdge) {
                if (!e.revEdge.isFull()) {
                    int q = e.dest;
                    if (level[q] < 0) {
                        level[q] = level[p] + 1;
                        queue.add(q);
                        if (q == src) {
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }

    private int dfs(int p, int incoming) {
        int ret = 0;
        if (p == sink) {
            return incoming;
        }
        for (Edge e = curEdge[p]; e != null; curEdge[p] = e = e.nextEdge) {
            if (e.isFull() || level[p] != level[e.dest] + 1) {
                continue;
            }
            int pushed = dfs(e.dest, Math.min(incoming, e.capacity()));
            if (pushed >= 0) {
                incoming -= pushed;
                ret += pushed;
                e.flow += pushed;
                e.revEdge.flow -= pushed;
                if (incoming == 0) {
                    break;
                }
            }
        }
        return ret;
    }

    private int src, sink;
    private Edge[] curEdge;
    private int[] level;
}

public class Main implements Runnable {

    void solve(int n, Triangle[] triangles) {
        HashMap<Triangle, Integer> findIndex = new HashMap<Triangle, Integer>();
        for (int i = 0; i < n; i++) {
            findIndex.put(triangles[i], i);
        }
        DinicSolver graph = new DinicSolver(n + 4);
        int src = n, sink = n + 1;
        int superSrc = n + 2, superSink = n + 3;
        ArrayList<DinicSolver.Edge> edges = new ArrayList<DinicSolver.Edge>();
        for (int i = 0; i < n; i++) {
            Triangle p = triangles[i];
            if (p.getSide()) {
                graph.addEdge(src, i, 1, 0);
                graph.addEdge(superSrc, i, 1, 0);
                graph.addEdge(src, superSink, 1, 0);
                for (Triangle q : p.getNeighbors()) {
                    Integer j = findIndex.get(q);
                    if (j != null) {
                        edges.add(graph.addEdge(i, j, 1, 0));
                    }
                }
            } else {
                graph.addEdge(i, sink, 1, 0);
                graph.addEdge(superSrc, sink, 1, 0);
                graph.addEdge(i, superSink, 1, 0);
            }
        }
        graph.addEdge(sink, src, Integer.MAX_VALUE, 0);
        if (graph.maxFlow(superSrc, superSink) != n) {
            out.println("No solution");
            return;
        }
        ArrayList<Integer>[] adj = new ArrayList[n];
        for (int i = 0; i < n; i++) {
            adj[i] = new ArrayList<Integer>();
        }
        for (DinicSolver.Edge e : edges) {
            if (e.isFull()) {
                int p = e.dest;
                int q = e.revEdge.dest;
                adj[p].add(q);
                adj[q].add(p);
            }
        }
        for (int i = 0; i < n; i++) {
            assert adj[i].size() >= 1 && adj[i].size() <= 2;
        }
        int[] color = new int[n];
        int colors = 0;
        for (int i = 0; i < n; i++) {
            if (color[i] == 0) {
                int ptr1 = i, ptr2 = adj[i].get(0);
                while (true) {
                    if (adj[ptr2].size() == 1) {
                        // find chain
                        break;
                    }
                    int ptr3 = adj[ptr2].get(0) + adj[ptr2].get(1) - ptr1;
                    ptr1 = ptr2;
                    ptr2 = ptr3;
                    if (ptr1 == i) {
                        // find cycle, cut and change to a chain
                        adj[ptr1].remove(ptr2);
                        adj[ptr2].remove(ptr1);
                        ptr1 = adj[ptr2].get(0);
                        break;
                    }
                }
                ArrayList<Integer> chain = new ArrayList<Integer>();
                chain.add(ptr2);
                while (true) {
                    chain.add(ptr1);
                    if (adj[ptr1].size() == 1) {
                        break;
                    }
                    int ptr0 = adj[ptr1].get(0) + adj[ptr1].get(1) - ptr2;
                    ptr2 = ptr1;
                    ptr1 = ptr0;
                }
                int ptr = 0;
                if (chain.size() % 2 == 1) {
                    colors ++;
                    color[chain.get(ptr++)] = colors;
                    color[chain.get(ptr++)] = colors;
                    color[chain.get(ptr++)] = colors;
                }
                while (ptr + 2 <= chain.size()) {
                    colors ++;
                    color[chain.get(ptr++)] = colors;
                    color[chain.get(ptr++)] = colors;
                }
            }
        }
        out.println(colors);
        for (int i = 0; i < n; i++) {
            if (i > 0) {
                out.print(' ');
            }
            out.print(color[i]);
        }
        out.println();
    }

    public void run() {
        try {
            in = new BufferedReader(new InputStreamReader(System.in));
            out = new PrintWriter(System.out);
            st = null;
            int n = nextInt();
            Triangle[] triangles = new Triangle[n];
            for (int i = 0; i < n; i++) {
                int xi = nextInt();
                int yi = nextInt();
                triangles[i] = new Triangle(xi, yi);
            }
            solve(n, triangles);
            in.close();
            out.close();
        } catch (Exception ex) {
            ex.printStackTrace();
            System.exit(-1);
        }
    }

    public static void debug(Object...os) {
        System.err.println(Arrays.deepToString(os));
    }

    String next() throws IOException {
        while (st == null || !st.hasMoreTokens()) {
            st = new StringTokenizer(in.readLine());
        }
        return st.nextToken();
    }

    int nextInt() throws IOException {
        return Integer.parseInt(next());
    }

    BufferedReader in;
    StringTokenizer st;
    PrintWriter out;

    public static void main(String[] args) {
        new Thread(new Main()).start();
    }
}
