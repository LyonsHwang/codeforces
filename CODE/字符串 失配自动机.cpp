struct ACM {
    struct state {
        int fa;
        vector<int> nxt;
        state() { fa=0; nxt=vector<int>(26); }
    };
    vector<state> m;
    vector<int> V;
    void init() {
        m.assign(1,{});
        V.assign(1,0);
    }
    int add() {
        m.push_back({});
        V.push_back(0);
        return m.size()-1;
    }
    int extend(const string &s) {
        int x=0;
        for(auto c_: s) {
            int c=c_-'a';
            int &y=m[x].nxt[c];
            x=y? y: y=add();
        }
        return x;
    }
    void build() {
        queue<int> q;
        for(auto x: m[0].nxt) if(x) q.push(x);
        while(!q.empty()) {
            int x=q.front(); q.pop();
            loop(i,26) {
                int &y=m[x].nxt[i];
                int z=m[m[x].fa].nxt[i];
                if(y) m[y].fa=z, q.push(y);
                else y=z;
            }
        }
    }
    void count() {
        vector<vector<int>> g;
        g.resize(isz(m));
        rep(i,1,isz(m)) g[m[i].fa].push_back(i);
        function<void(int)> dfs=[&](int x) {
            for(auto y: g[x]) dfs(y),V[x]+=V[y];
        };
        dfs(0);
    }
} ac;
