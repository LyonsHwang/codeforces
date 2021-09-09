struct MSeg {
    struct node {
        int l,r,sum;
    };
    vector<node> t;
    int Ln,Rn,G,L,R,V;
    void init(int l,int r) {
        Ln=l; Rn=r;
        t.assign(1,{0,0,0});
    }
    int bld(int l,int r){ 
        int x=add();
        if(stop) t[x].sum=1;
        else {
            t[x].l=bld(l,mid);
            t[x].r=bld(mid,r);
            push(x);
        }
        return x;
    }
    int build(int l,int r) {
        return init(l,r),bld(l,r);
    }
    int add() {
        t.push_back(t[0]);
        return t.size()-1;
    }
    void push(int x) {
        t[x].sum=t[t[x].l].sum+t[t[x].r].sum;
    }
    int upd(int o,int l,int r) {
        if(G<l||G>=r) return o;
        int x=add(); t[x]=t[o];
        if(l+1==r) t[x].sum=V;
        else {
            t[x].l=upd(t[x].l,l,mid);
            t[x].r=upd(t[x].r,mid,r);
            push(x);
        }
        return x;
    }
    int update(int o,int g,int v) {
        return G=g, V=v, upd(o,Ln,Rn);
    }
    int cov(int o1,int o2,int l,int r) {
        if(!o1||r<=L||l>=R) return o2;
        if(L<=l&&r<=R) return o1;
        int x=add();
        t[x].l=cov(t[o1].l,t[o2].l,l,mid);
        t[x].r=cov(t[o1].r,t[o2].r,mid,r);
        return push(x), x;
    }
    int cover(int o1,int o2,int l,int r) {
        return L=l,R=r,cov(o1,o2,Ln,Rn);
    }
    int merge(int o1,int o2) {
        if(!o1||!o2) return o1+o2;
        int x=add();
        t[x].l=merge(t[o1].l,t[o2].l);
        t[x].r=merge(t[o1].r,t[o2].r);
        t[x].sum=t[o1].sum+t[o2].sum;
        return x;
    }
    int qry(int x,int l,int r) {
        if(!x) return 0;
        if(L<=l&&r<=R) return t[x].sum;
        int res=0;
        if(L<mid) res+=qry(t[x].l,l,mid);
        if(R>mid) res+=qry(t[x].r,mid,r);
        return res;
    }
    int query(int x,int l,int r) {
        return L=l, R=r, qry(x,Ln,Rn);
    }
};
