struct KMP {
    int n;
    vector<int> s;  // string
    vector<int> b;  // border
    void init() {
        // n = ::n;
        // s.assign(::s, ::s + n);
        b.resize(n);
    }
    void build() {
        for (int j = 0, i = 1; i < n; i++) {
            while (j > 0 && s[j] != s[i]) j = b[j - 1];
            if (s[j] == s[i]) ++j;
            b[i] = j;
        }
    }
    int trans(int k, int c) {
        if (k == n) k = b[k - 1];
        while (k > 0 && s[k] != c) k = b[k - 1];
        if (s[k] == c) ++k;
        return k;
    }
} kmp;
