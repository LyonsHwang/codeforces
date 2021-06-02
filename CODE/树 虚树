struct VTree {
    struct ST {
        int n,m;
        vector<int> key;
        vector2D<int> st;
        int lg(int x) {
            return 31-__builtin_clz(x);
        }
        int merge(int x,int y) {
            return (key[x]<key[y])? x: y;
        }
        void init(vector<int> &a, vector<int> &key_) {
            n=isz(a); m=lg(n-1)+1; key=key_;
            st.resize(m);
            st[0]=a;
            rep(i,1,m) st[i].resize(n-(1<<i)+1);
            rep(i,1,m) loop(j,isz(st[i]))
                st[i][j]=merge(st[i-1][j],st[i-1][j+(1<<(i-1))]);
        }
        int calc(int l,int r) {
            int k=lg(r-l);
            return merge(st[k][l],st[k][r-(1<<k)]);
        }
    } st;
    struct edge {
        int to; ll c;
    };
    int n,root;
    vector<ll> len;
    vector<vector<edge>> go;
    vector<int> fa,sz,dep,lno,rno,pos;
    vector<int> piv,vis;
    void init(int n_,int root_) {
        n=n_; root=root_;
        pos.clear();
        fa.assign(n,-1);
        sz.assign(n,1);
        go.assign(n,{});
        dep.assign(n,0);
        len.assign(n,0);
        lno.assign(n,-1);
        rno.assign(n,-1);
        piv.assign(n,0);
        vis.assign(n,0);
    }
    void read() {
        int u,v;
        loop(i,n-1) cin>>u>>v, add(u-1,v-1);
    }
    void add(int u,int v,ll w=1) {
        go[u].push_back({v,w});
        go[v].push_back({u,w});
    }
    void _dfs(int x) {
        lno[x]=isz(pos);
        pos.push_back(x);
        for(auto &e: go[x]) if(e.to!=fa[x]) {
            dep[e.to]=dep[x]+1;
            len[e.to]=len[x]+e.c;
            fa[e.to]=x;
            _dfs(e.to);
            sz[x]+=sz[e.to];
            pos.push_back(x);
        }
        rno[x]=isz(pos);
    }
    int lca(int x,int y) {
        x=lno[x]; y=lno[y];
        if(x>y) swap(x,y);
        return st.calc(x,y+1);
    }
    ll dist(int x,int y) {
        return len[x]+len[y]-2*len[lca(x,y)];
    }
    void build() {
        _dfs(root);
        st.init(pos,dep);
        loop(i,n) go[i].clear();
    }
    void solve(vector<int> a) {
        auto cmp=[&](int x,int y) { return lno[x]<lno[y]; };
        for(auto x: a) vis[x]=piv[x]=1;
        sort(all(a),cmp);
        lback(i,isz(a)-1) {
            int b=lca(a[i],a[i+1]);
            if(!vis[b]) a.push_back(b),vis[b]=1;
        }
        sort(all(a),cmp);
        vector<int> stk{a[0]};
        rep(i,1,isz(a)) {
            while(rno[stk.back()]<=lno[a[i]]) stk.pop_back();
            add(stk.back(),a[i]);
            stk.push_back(a[i]);
        }
        for(auto x: a) vis[x]=piv[x]=0, go[x].clear();
    }
};
