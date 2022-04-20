struct Fenwick {
    int n;
    vector<ll> a;
    void init(int n) {
        this->n = n;
        a.assign(n, 0);
    }
    void add(int x, ll v) {
        for (++x; x <= n; x += x & -x) a[x - 1] += v;
    }
    ll sum(int x) {
        ll res = 0;
        for (; x > 0; x -= x & -x) res += a[x - 1];
        return res;
    }
};
