struct EulerSieve {
    vector<int> ps;
    vector<int> mn;
    void init(int n) {
        ps.clear();
        mn.assign(n, 0);
        rep(i, 2, n) {
            if (mn[i] == 0) ps.push_back(i);
            for (auto p : ps) {
                if (i * p >= n) break;
                mn[i * p] = p;
                if (i % p == 0) break;
            }
        }
    }
};
