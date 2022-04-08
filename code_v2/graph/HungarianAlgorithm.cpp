// int n;
// vector<int> g[maxn];
namespace Hungarian {
int m;        // match count
int a[maxn];  // match
int c[maxn];  // visit
bool find(int x) {
    if (c[x]) return 0;
    c[x] = 1;
    for (auto y : g[x])
        if (a[y] == -1 || find(a[y])) {
            a[y] = x, a[x] = y;
            return true;
        }
    return false;
}
bool augment(int x) {
    loop(i, n) c[i] = 0;
    return find(x);
}
int match() {
    m = 0;
    loop(i, n) a[i] = -1;
    loop(i, n) if (a[i] == -1) m += augment(i);
    return m;
}
}  // namespace Hungarian
