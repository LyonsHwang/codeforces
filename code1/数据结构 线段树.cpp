struct Seg {
    struct node {
        ll val,tag;
        int sz;
    };
    vector<node> t;
    int Ln,Rn,L,R,G;
    ll V;
    void init(int l,int r) {
        Ln=l; Rn=r;
        t.resize((Rn-Ln)<<2);
    }
    void adj(int x,ll v) {
        t[x].val+=t[x].sz*v;
        t[x].tag+=v;
    }
    void push(int x) {
        if(!t[x].tag) return;
        adj(lson,t[x].tag);
        adj(rson,t[x].tag);
        t[x].tag=0;
    }
    void pull(int x) {
        t[x].val=t[lson].val+t[rson].val;
    }
    void bld(int x,int l,int r) {
        t[x]={0,0,r-l};
        if(r-l==1) return;
        bld(lson,l,mid);
        bld(rson,mid,r);
        pull(x);
    }
    void build() {
        bld(1,Ln,Rn);
    }
    void upd(int x,int l,int r) {
        if(r-l==1) { t[x].val=V; return; }
        push(x);
        if(G<mid) upd(lson,l,mid);
        else upd(rson,mid,r);
        pull(x);
    }
    void update(int g,ll v) {
        return G=g, V=v, upd(1,Ln,Rn);
    }
    ll qry(int x,int l,int r) {
        if(L<=l&&r<=R) return t[x].val;
        push(x);
        ll res=0;
        if(L<mid) res+=qry(lson,l,mid);
        if(R>mid) res+=qry(rson,mid,r);
        return res;
    }
    ll query(int l,int r) {
        return L=l, R=r, qry(1,Ln,Rn);
    }
    void inc(int x,int l,int r) {
        if(L<=l&&r<=R) return adj(x,V);
        push(x);
        if(L<mid) inc(lson,l,mid);
        if(R>mid) inc(rson,mid,r);
        pull(x);
    }
    void increase(int l,int r,ll v) {
        return L=l, R=r, V=v, inc(1,Ln,Rn);
    }
};
