struct ZKW {
    int w;
    vector<ll> v;
    void init(int n) {
        for(w=1;w<n+2;w<<=1);
        v.resize(w<<1);
        v.assign(w<<1,0);
    }
    ll query(int L,int R) {
        ll res=0;
        for(int l=w+L-1,r=w+R+1;l^r^1;l>>=1,r>>=1) {
            if(~l&1) res=max(res,v[l^1]);
            if(r&1) res=max(res,v[r^1]);
        }
        return res;
    }
};
