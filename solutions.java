import java.util.*;

public class AllCppToJavaConverted {

    /* ===================== 1. Penalty Count ===================== */
    static void penaltyCount() {
        String s = "NNYNNYnyNYYY";
        int cl = 7;
        int pen = 0;

        for (int i = 0; i < s.length(); i++) {
            char c = Character.toUpperCase(s.charAt(i));
            if (i < cl) {
                if (c == 'N') pen++;
            } else {
                if (c == 'Y') pen++;
            }
        }
        System.out.println("Penalty Count: " + pen);
    }

    /* ===================== 2. Minimum Penalty Index ===================== */
    static void minPenaltyIndex() {
        String c = "YYNY";
        List<Integer> list = new ArrayList<>();

        int p = 0;
        for (char ch : c.toCharArray()) if (ch == 'Y') p++;
        list.add(p);

        for (char ch : c.toCharArray()) {
            if (ch == 'Y') p--;
            else p++;
            list.add(p);
        }

        int minIndex = 0;
        for (int i = 1; i < list.size(); i++) {
            if (list.get(i) < list.get(minIndex)) minIndex = i;
        }

        System.out.println("Min Penalty Index: " + minIndex);
    }

    /* ===================== 3. BEGIN-END Parser ===================== */
    static void beginEndParser() {
        String s = "BEGIN BEGIN BEGIN Y Y N Y END N N N N N END Y Y Y Y END";
        String[] tokens = s.split(" ");

        Stack<String> stack = new Stack<>();
        List<String> logs = new ArrayList<>();

        for (String t : tokens) {
            if (!t.equals("END")) {
                stack.push(t);
            } else {
                StringBuilder temp = new StringBuilder();
                while (!stack.isEmpty() && !stack.peek().equals("BEGIN")) {
                    temp.append(stack.pop());
                }
                if (!stack.isEmpty()) stack.pop();
                logs.add(temp.reverse().toString());
            }
        }

        System.out.print("BEGIN-END Output: ");
        for (String a : logs) {
            int countY = 0;
            for (char ch : a.toCharArray()) if (ch == 'Y') countY++;
            System.out.print(countY + " ");
        }
        System.out.println();
    }

    /* ===================== 4. Evaluate Division ===================== */
    static Map<String, Map<String, Double>> graph = new HashMap<>();

    static double dfsDivision(String a, String b, Set<String> vis) {
        if (a.equals(b)) return 1.0;
        vis.add(a);

        for (Map.Entry<String, Double> e : graph.get(a).entrySet()) {
            if (!vis.contains(e.getKey())) {
                double val = dfsDivision(e.getKey(), b, vis);
                if (val != -1) return e.getValue() * val;
            }
        }
        return -1;
    }

    static void evaluateDivision() {
        String[][] eq = {{"a", "b"}, {"b", "c"}};
        double[] val = {2.0, 3.0};
        String[][] queries = {{"a", "c"}, {"b", "a"}, {"a", "e"}};

        for (int i = 0; i < eq.length; i++) {
            graph.computeIfAbsent(eq[i][0], k -> new HashMap<>()).put(eq[i][1], val[i]);
            graph.computeIfAbsent(eq[i][1], k -> new HashMap<>()).put(eq[i][0], 1.0 / val[i]);
        }

        System.out.print("Evaluate Division: ");
        for (String[] q : queries) {
            if (!graph.containsKey(q[0]) || !graph.containsKey(q[1])) {
                System.out.print("-1 ");
            } else {
                System.out.print(dfsDivision(q[0], q[1], new HashSet<>()) + " ");
            }
        }
        System.out.println();
    }

    /* ===================== 5. Brace Expansion II ===================== */
    static class BraceExpansion {
        void solve(String ex, Set<String> res) {
            int cb = ex.indexOf('}');
            if (cb == -1) {
                res.add(ex);
                return;
            }
            int ob = ex.lastIndexOf('{', cb);
            String first = ex.substring(0, ob);
            String mid = ex.substring(ob + 1, cb);
            String last = ex.substring(cb + 1);

            for (String token : mid.split(",")) {
                solve(first + token + last, res);
            }
        }

        List<String> expand(String ex) {
            Set<String> res = new TreeSet<>();
            solve(ex, res);
            return new ArrayList<>(res);
        }
    }

    /* ===================== 6. Shipping Cost ===================== */
    static Map<String, Map<String, Integer>> shipGraph = new HashMap<>();

    static int dfsShip(String x, String y, Set<String> vis) {
        if (x.equals(y)) return 0;
        vis.add(x);

        int min = Integer.MAX_VALUE;
        for (Map.Entry<String, Integer> e : shipGraph.get(x).entrySet()) {
            if (!vis.contains(e.getKey())) {
                int cost = dfsShip(e.getKey(), y, vis);
                if (cost != -1) min = Math.min(min, e.getValue() + cost);
            }
        }
        vis.remove(x);
        return min == Integer.MAX_VALUE ? -1 : min;
    }

    static void shippingCost() {
        String s = "US,UK,UPS,5:US,CA,FedEx,3:CA,UK,DHL,7";

        for (String part : s.split(":")) {
            String[] v = part.split(",");
            shipGraph.computeIfAbsent(v[0], k -> new HashMap<>())
                      .put(v[1], Integer.parseInt(v[3]));
        }

        System.out.println("Shipping Cost US->UK: " + dfsShip("US", "UK", new HashSet<>()));
    }

    /* ===================== 7. Brace Expansion DFS ===================== */
    static class BraceDFS {
        List<String> res = new ArrayList<>();
        List<List<Character>> groups = new ArrayList<>();

        List<String> expand(String s) {
            int i = 0;
            while (i < s.length()) {
                if (s.charAt(i) == '{') {
                    i++;
                    List<Character> temp = new ArrayList<>();
                    while (s.charAt(i) != '}') {
                        if (s.charAt(i) != ',') temp.add(s.charAt(i));
                        i++;
                    }
                    Collections.sort(temp);
                    groups.add(temp);
                    i++;
                } else {
                    groups.add(List.of(s.charAt(i)));
                    i++;
                }
            }
            dfs(0, new StringBuilder());
            Collections.sort(res);
            return res;
        }

        void dfs(int idx, StringBuilder cur) {
            if (idx == groups.size()) {
                res.add(cur.toString());
                return;
            }
            for (char c : groups.get(idx)) {
                cur.append(c);
                dfs(idx + 1, cur);
                cur.deleteCharAt(cur.length() - 1);
            }
        }
    }

    /* ===================== 8. Transaction Validator ===================== */
    static class TransactionValidator {
        static final double MIN = 1, MAX = 10000;
        static final Set<String> BLOCKED = Set.of("CRYPTO", "GIFT_CARD");

        static String bucket(double amt) {
            if (amt < 100) return "LOW";
            if (amt <= 1000) return "MEDIUM";
            return "HIGH";
        }
    }

    /* ===================== 9. Optimal Account Balancing ===================== */
    static class AccountBalance {
        int dfs(List<Integer> d, int i) {
            while (i < d.size() && d.get(i) == 0) i++;
            if (i == d.size()) return 0;

            int ans = Integer.MAX_VALUE;
            for (int j = i + 1; j < d.size(); j++) {
                if (d.get(i) * d.get(j) < 0) {
                    d.set(j, d.get(j) + d.get(i));
                    ans = Math.min(ans, 1 + dfs(d, i + 1));
                    d.set(j, d.get(j) - d.get(i));
                }
            }
            return ans;
        }
    }

    /* ===================== 10. Cheapest Flight ===================== */
    static class CheapestFlight {
        int findCheapestPrice(int n, int[][] flights, int src, int dst, int k) {
            int[] cost = new int[n];
            Arrays.fill(cost, Integer.MAX_VALUE);
            cost[src] = 0;

            for (int i = 0; i <= k; i++) {
                int[] tmp = cost.clone();
                for (int[] f : flights) {
                    if (cost[f[0]] != Integer.MAX_VALUE) {
                        tmp[f[1]] = Math.min(tmp[f[1]], cost[f[0]] + f[2]);
                    }
                }
                cost = tmp;
            }
            return cost[dst] == Integer.MAX_VALUE ? -1 : cost[dst];
        }
    }

    /* ===================== 11. Course Completion ===================== */
    static class CourseTime {
        int minimumTime(int n, int[][] relations, int[] time) {
            List<List<Integer>> g = new ArrayList<>();
            for (int i = 0; i < n; i++) g.add(new ArrayList<>());

            int[] indeg = new int[n];
            for (int[] r : relations) {
                g.get(r[0] - 1).add(r[1] - 1);
                indeg[r[1] - 1]++;
            }

            Queue<Integer> q = new LinkedList<>();
            int[] dp = new int[n];

            for (int i = 0; i < n; i++) {
                dp[i] = time[i];
                if (indeg[i] == 0) q.offer(i);
            }

            while (!q.isEmpty()) {
                int u = q.poll();
                for (int v : g.get(u)) {
                    dp[v] = Math.max(dp[v], dp[u] + time[v]);
                    if (--indeg[v] == 0) q.offer(v);
                }
            }

            int ans = 0;
            for (int x : dp) ans = Math.max(ans, x);
            return ans;
        }
    }

    public static void main(String[] args) {
        penaltyCount();
        minPenaltyIndex();
        beginEndParser();
        evaluateDivision();
        shippingCost();
    }
}
