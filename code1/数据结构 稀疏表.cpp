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
};
