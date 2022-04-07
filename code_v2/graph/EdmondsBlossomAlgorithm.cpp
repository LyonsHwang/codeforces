// int n;
// vector<int> g[maxn];
namespace EdmondsBlossom {
int m;             // match count
int t[maxn], tim;  // time tag
int a[maxn];       // vertex match
int b[maxn];       // vertex before
int f[maxn];       // odd cycle top
int s[maxn];       // status: -1(unvisited), 0(even), 1(odd)
queue<int> q;      // major memory
int fn(int x) { return x == f[x] ? x : f[x] = fn(f[x]); }
int fm(int x, int y) {
    for (++tim;; swap(x, y))
        if (~x) {
            if (t[x = fn(x)] == tim) return x;
            t[x] = tim;
            x = a[x] == -1 ? -1 : b[a[x]];
        }
    return -1;
}
void blossom(int x, int y, int z) {
    while (fn(x) != z) {
        b[x] = y, y = a[x];
        if (s[y] == 1) s[y] = 0, q.push(y);
        if (f[x] == x) f[x] = z;
        if (f[y] == y) f[y] = z;
        x = b[y];
    }
}
bool augment(int x) {
    while (q.size()) q.pop();
    loop(i, n) f[i] = i, b[i] = s[i] = -1;
    s[x] = 0, q.push(x);
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (auto v : g[u]) {
            if (s[v] == -1) {
                int w = a[v];
                if (w == -1)
                    for (;; u = b[v = w]) {
                        w = a[u], a[u] = v, a[v] = u;
                        if (w == -1) return true;
                    }
                b[v] = u, s[v] = 1;
                s[w] = 0, q.push(w);
            } else if (!s[v] && fn(v) != fn(u)) {
                int w = fm(u, v);
                blossom(v, u, w);
                blossom(u, v, w);
            }
        }
    }
    return false;
}
int match() {
    m = 0;
    loop(i, n) a[i] = -1;
    loop(i, n) if (a[i] == -1) m += augment(i);
    return m;
}
}  // namespace EdmondsBlossom
