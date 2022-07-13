struct PalindromicAutomaton {
    int last;
    vector<int> ref;  // string
    vector<int> res;  // backup
    int m;            // index
    vector<int> len;
    vector<int> fail;
    vector<alpha<int>> child;
    vector<alpha<int>> quick;
    void init() {
        ref = {-1};
        res = {last = 0};
        m = 2;
        len = {0, -1};
        fail = {1, 0};
        child.resize(2);
        quick.resize(2);
        quick[0].fill(1);
        quick[1].fill(1);
    }
    void push_back(int c) {
        ref.push_back(c);
        int pos = ref.size() - 1;
        int pre = last;
        if (ref[pos - len[pre] - 1] != ref[pos]) pre = quick[pre][c];
        if (!child[pre][c]) {
            int gen = m++;
            len.push_back(len[pre] + 2);
            fail.push_back(child[quick[pre][c]][c]);
            quick.push_back(quick[fail[gen]]);
            child.push_back({});
            quick[gen][ref[pos - len[fail[gen]]]] = fail[gen];
            child[pre][c] = gen;
        }
        res.push_back(last = child[pre][c]);
    }
    void pop_back() {
        ref.pop_back();
        res.pop_back();
        last = res.back();
    }
};
