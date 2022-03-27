struct SuffixAutomaton {
    int m;  // index
    vector<int> fa;
    vector<int> ln;
    vector<alpha<int>> go;
    void init() {
        m = 1;
        fa.resize(m);
        ln.resize(m);
        go.resize(m);
        emplace(0, 0, go[0]);
    }
    int emplace(int f, int l, alpha<int> &g) {
        fa.push_back(f);
        ln.push_back(l);
        go.push_back(g);
        return m++;
    }
    int extend(int x, int c) {
        int y = go[x][c];
        int l = ln[x] + 1;
        if (y) {
            if (ln[y] == l) return y;
            int z = emplace(fa[y], l, go[y]);
            for (fa[y] = z; go[x][c] == y; x = fa[x]) go[x][c] = z;
            return z;
        }
        y = emplace(-1, l, go[0]);
        for (; x && !go[x][c]; x = fa[x]) go[x][c] = y;
        fa[y] = !x ? 1 : extend(x, c);
        return y;
    }
};
