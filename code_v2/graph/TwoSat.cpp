struct TwoSat {
    int n;                  // thesis
    int m;                  // propositions
    int k;                  // dfs clock
    vector<vector<int>> g;  // implication
    vector<int> ans;        // solution
    vector<int> dfn;        // dfs order
    vector<int> com;        // component
    vector<int> vis;        // status: 0(unvisited), 1(in stack), 2(done)
    stack<int> s;
    void init() {
        // n = ::n;
        m = 2 * n;
        g.resize(m);
        ans.resize(n);
        vis.resize(m);
        com.resize(m);
        dfn.resize(m);
        loop(i, m) g[i].clear();
    }
    int index(int x) { return x >= 0 ? 2 * x : -2 * x - 1; }
    void add(int x, int y) {
        x = index(x);
        y = index(y);
        g[x].push_back(y);
        g[y ^ 1].push_back(x ^ 1);
    }
    void add_or(int x, int y) { add(~x, y); }
    void add_ne(int x, int y) { add_or(x, y), add_or(~x, ~y); }
    void add_eq(int x, int y) { add_ne(~x, y); }
    int dfs(int x) {
        int low = dfn[x] = k++;
        s.push(x), vis[x] = 1;
        for (int y : g[x])
            if (!vis[y])
                umin(low, dfs(y));
            else if (vis[y] == 1)
                umin(low, dfn[y]);
        if (low == dfn[x])
            for (int u;;) {
                u = s.top(), s.pop();
                vis[u] = 2, com[u] = x;
                if (ans[u >> 1] == -1) ans[u >> 1] = ~u & 1;
                if (u == x) break;
            }
        return low;
    }
    bool check() {
        loop(i, n) ans[i] = -1;
        loop(i, m) vis[i] = 0;
        loop(i, m) if (!vis[i]) dfs(i);
        loop(i, n) if (com[i << 1] == com[i << 1 | 1]) return false;
        return true;
    }
};
