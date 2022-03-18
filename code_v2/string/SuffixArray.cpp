// Problem:     https://www.luogu.com.cn/problem/U103231
// Submission:  https://www.luogu.com.cn/record/71635168

struct SuffixArray {
    int n;  // length
    int m;  // charset
    vector<int> s, x, y, c;
    vector<int> sa, rk;
    vector<int> h, g[20];
    void init() {
        // n = ::n, m = 128;
        sa.resize(n);
        rk.resize(n);
        c.resize(max(n, m));
        s.resize(n + 1);
        x.resize(n + 1);
        y.resize(n + 1);
        s[n] = x[n] = y[n] = -1;
        // loop(i, n) s[i] = ::s[i];
    }
    void build_sa() {
        loop(i, m) c[i] = 0;
        loop(i, n) c[x[i] = s[i]]++;
        rep(i, 1, m) c[i] += c[i - 1];
        lback(i, n) sa[--c[x[i]]] = i;
        for (int w = 1, prv = m, cur = 1; cur < n; w <<= 1) {
            cur = 0;
            rep(i, n - w, n) y[cur++] = i;
            loop(i, n) if (sa[i] >= w) y[cur++] = sa[i] - w;
            loop(i, prv) c[i] = 0;
            loop(i, n) c[x[y[i]]]++;
            rep(i, 1, prv) c[i] += c[i - 1];
            lback(i, n) sa[--c[x[y[i]]]] = y[i];
            swap(x, y);
            cur = 1, x[sa[0]] = 0;
            rep(i, 1, n) {
                if (y[sa[i - 1]] != y[sa[i]] || y[sa[i - 1] + w] != y[sa[i] + w]) ++cur;
                x[sa[i]] = cur - 1;
            }
            prv = cur;
        }
        loop(i, n) rk[sa[i]] = i;
    }
    void build_h() {
        h.resize(n);
        int k = 0;
        loop(i, n) {
            if (k) k--;
            if (rk[i]) {
                int j = sa[rk[i] - 1];
                while (s[i + k] == s[j + k]) k++;
            }
            h[rk[i]] = k;
        }
    }
    void build_rmq() {
        g[0] = h;
        for (int u = 1, w = 2; w < n; u++, w <<= 1) {
            g[u].resize(n - w + 1);
            loop(i, n - w + 1) g[u][i] = min(g[u - 1][i], g[u - 1][i + w / 2]);
        }
    }
    int lcp(int x, int y) {
        if (x == y) return n - x;
        x = rk[x], y = rk[y];
        if (x > y) swap(x, y);
        ++x;
        int k = log2(y - x + 1);
        return min(g[k][x], g[k][y - (1 << k) + 1]);
    }
    void build() {
        build_sa();
        build_h();
        build_rmq();
    }
};
