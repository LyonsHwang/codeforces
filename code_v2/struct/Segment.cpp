struct Segment {
    int n;
    vector<ll> t;
    void init(int n) {
        this->n = n;
        t.assign(2 * n, 0);
    }
    void make(int x, ll v) {
        for (t[x += n] = v; x > 1; x >>= 1) t[x >> 1] = max(t[x], t[x ^ 1]);
    }
    ll calc(int l, int r) {
        ll res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) umax(res, t[l++]);
            if (r & 1) umax(res, t[--r]);
        }
        return res;
    }
};
