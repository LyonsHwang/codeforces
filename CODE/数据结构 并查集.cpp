struct DSU {
    vector<int> fa,sz;
    void init(int n) {
        fa.resize(n);
        iota(all(fa),0);
        sz.assign(n,1);
    }
    int find(int x) {
        while(x!=fa[x]) x=fa[x]=fa[fa[x]];
        return x;
    }
    bool same(int x,int y) {
        return find(x)==find(y);
    }
    bool merge(int x,int y) {
        x=find(x);
        y=find(y);
        if(x==y) return false;
        sz[fa[y]=x]+=sz[y];
        return true;
    }
};
