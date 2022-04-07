// int n1, n2;
// vector<int> g[maxn];
namespace Hungarian {
int m;        // match count
int a[maxn];  // vertex match
int b[maxn];  // vertex match
int c[maxn];  // visited
bool find(int x) {
    if (c[x]) return 0;
    c[x] = 1;
    for (auto y : g[x])
        if (b[y] == -1 || find(b[y])) {
            b[y] = x;
            a[x] = y;
            return true;
        }
    return false;
}
int match() {
    m = 0;
    loop(i, n1) a[i] = -1;
    loop(i, n2) b[i] = -1;
    loop(i, n1) {
        loop(j, n1) c[j] = 0;
        m += find(i);
    }
    return m;
}
}  // namespace Hungarian
