struct PSeg {
    struct node {
        int l,r;
        ll sum;
    };
    vector<node> t;
    int Ln,Rn,L,R,G;
    ll V;
    void init(int l,int r) {
        Ln=l; Rn=r;
        t.assign(1,{0,0,0});
        t.reserve(40000000);
    }
    int add() {
        t.resize(t.size()+1);
        return t.size()-1;
    }
    void pushup(int x) {
        int l=t[x].l,r=t[x].r;
        t[x].sum=t[l].sum+t[r].sum;
    }
    int upd(int o,int l,int r) {
        int x=add(); t[x]=t[o];
        if(l==r) {
            t[x].sum=V;
        } else {
            int mid=(l+r)>>1;
            if(G<=mid) t[x].l=upd(t[x].l,l,mid);
            else t[x].r=upd(t[x].r,mid+1,r);
            pushup(x);
        }
        return x;
    }
    int update(int x,int g,ll v) {
        G=g; V=v;
        return upd(x,Ln,Rn);
    }
    ll qry(int x,int l,int r) {
        if(L<=l&&r<=R) return t[x].sum;
        ll res=0;
        int mid=(l+r)>>1;
        if(L<=mid) res+=qry(t[x].l,l,mid);
        if(R>mid) res+=qry(t[x].r,mid+1,r);
        return res;
    }
    ll query(int x,int l,int r) {
        L=l; R=r;
        return qry(x,Ln,Rn);
    }
};
