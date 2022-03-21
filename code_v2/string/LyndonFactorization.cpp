// Problem:     https://www.luogu.com.cn/problem/P6114
// Submission:  https://www.luogu.com.cn/record/71977036
// Tutorial:    https://www.xht37.com/lyndon-分解-学习笔记/

struct LyndonFactorization {
    int n;
    vector<int> s;
    vector<int> r;
    void init() {
        // n = ::n;
        // s.assign(::s, ::s + n);
    }
    void solve() {
        for (int i = 0, j, k; i < n;) {
            for (j = i, k = i + 1; k < n && s[j] <= s[k]; j++, k++)
                if (s[j] < s[k]) j = i - 1;
            while (i <= j) i += k - j, r.push_back(i);
        }
    }
};
