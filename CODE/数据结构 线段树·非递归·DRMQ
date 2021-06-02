struct DRMQ {
    int n;
    vector<ll> t;
    void init(int n_) {
        n=n_;
        t.assign(2*n,INF64);
    }
    void update(int g,ll v) {
        for(t[g+=n]=v;g>1;g>>=1)
            t[g>>1]=min(t[g],t[g^1]);
    }
    ll query(int l,int r) {
        ll res=INF64;
        for(l+=n,r+=n;l<r;l>>=1,r>>=1) {
            if(l&1) umin(res,t[l++]);
            if(r&1) umin(res,t[--r]);
        }
        return res;
    }
};
