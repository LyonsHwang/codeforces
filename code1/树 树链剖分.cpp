struct Tree {
    struct edge {
        int to; ll c;
    };
    int n,root;
    vector<ll> len;
    vector<vector<edge>> go;
    vector<int> fa,sz,dep,son,top,lno,rno,pos;
    void init(int n_,int root_) {
        n=n_; root=root_;
        pos.clear();
        fa.assign(n,-1);
        sz.assign(n,1);
        go.assign(n,{});
        dep.assign(n,0);
        len.assign(n,0);
        son.assign(n,-1);
        top.assign(n,-1);
        lno.assign(n,-1);
        rno.assign(n,-1);
    }
    void add(int u,int v,ll w=1) {
        go[u].push_back({v,w});
        go[v].push_back({u,w});
    }
    void read() {
        int u,v;
        loop(i,n-1) cin>>u>>v, add(u-1,v-1);
    }
    int deg(int x) {
        return go[x].size();
    }
    int lca(int x,int y) {
        for(;top[x]!=top[y];x=fa[top[x]])
            if(dep[top[x]]<dep[top[y]])
                swap(x,y);
        if(dep[x]>dep[y]) swap(x,y);
        return x;
    }
    ll dist(int x,int y) {
        return len[x]+len[y]-2*len[lca(x,y)];
    }
    bool multison(int x) {
        return ((x==root)&&(deg(x)>=2))||(deg(x)>=3);
    }
    bool isleave(int x) {
        return ((x!=root)&&(deg(x)==1));
    }
    void _dfs1(int x) {
        for(auto &e: go[x]) if(e.to!=fa[x]) {
            dep[e.to]=dep[x]+1;
            len[e.to]=len[x]+e.c;
            fa[e.to]=x;
            _dfs1(e.to);
            sz[x]+=sz[e.to];
            if(son[x]==-1||sz[e.to]>sz[son[x]]) son[x]=e.to;
        }
    }
    void _dfs2(int x) {
        lno[x]=isz(pos);
        pos.push_back(x);
        if(~son[x]) {
            top[son[x]]=top[x];
            _dfs2(son[x]);
            for(auto &e: go[x])
                if(e.to!=fa[x]&&e.to!=son[x])
                    _dfs2(top[e.to]=e.to);
        }
        rno[x]=isz(pos);
    }
    void build() {
        _dfs1(root);
        _dfs2(top[root]=root);
    }
};
