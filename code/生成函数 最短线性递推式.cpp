struct BM {
    vector<ll> a,f,g;
    int n,m;
    ll d,b;
    void init() {
        n=m=0;
        f=g={b=1};
        a.clear();
    }
    bool add(int x) {
        a.resize(++n,x); ++m; d=0;
        loop(i,isz(f)) d=(d+f[i]*a[n-1-i])%P;
        if(!d) return false;
        if(isz(f)<isz(g)+m) {
            g.insert(g.begin(),m,0);
            m=0; swap(f,g); swap(b,d);
        }
        ll c=(P-d)*power(b,P-2)%P;
        loop(i,isz(g)) f[i+m]=(f[i+m]+c*g[i])%P;
        return true;
    }
    void norm() {
        ll k=power(f[0],P-2);
        loop(i,isz(f)) f[i]=f[i]*k%P;
    }
    ll solve() {
        int k=isz(f);
        vector<ll> pre(k-1);
        loop(i,k-1) loop(j,i+1) pre[i]=(pre[i]+a[j]*f[i-j])%P;
        ll p=0,q=0;
        loop(i,k-1) p=(p+pre[i])%P;
        loop(i,k) q=(q+f[i])%P;
        return p*power(q,P-2)%P;
    }
    ll calc(vector<ll> &h, ll m) {
        int k=isz(f);
        vector<ll> a(2*k),b(2*k),d(2*k);
        auto mul=[&](vector<ll> &a, vector<ll> &b, vector<ll>&c) {
            loop(i,2*k) d[i]=0;
            loop(i,k) loop(j,k)
                d[i+j]=(d[i+j]+a[i]*b[j])%P;
            rback(i,k-1,2*k) if(d[i]) lback(j,k)
                d[i-j]=(d[i-j]+(P-d[i])*f[j])%P;
            loop(i,2*k) c[i]=d[i];
        };
        for(a[0]=b[1]=1;m;m>>=1,mul(b,b,b)) if(m&1) mul(a,b,a);
        ll res=0;
        loop(i,k) res=(res+h[i]*a[i])%P;
        return res;
    }
};
