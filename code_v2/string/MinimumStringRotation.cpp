// Problem:     https://www.luogu.com.cn/problem/P1368
// Submission:  https://www.luogu.com.cn/record/71977600
// Tutorial:    https://www.luogu.com.cn/blog/new2zy/solution-p1368

struct LyndonFactorization {
    int n;
    vector<int> s;
    void init() {
        // n = ::n << 1;
        // s.resize(n);
        // loop(i, n / 2) s[i] = s[i + n / 2] = ::s[i];
    }
    int solve() {
        int l = 0;
        for (int i = 0, j, k; i < n / 2;) {
            l = i;
            for (j = i, k = i + 1; k < n && s[j] <= s[k]; j++, k++)
                if (s[j] < s[k]) j = i - 1;
            while (i <= j) i += k - j;
        }
        return l;
    }
};
