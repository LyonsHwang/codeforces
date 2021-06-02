struct MSEG {
    struct node {
        int l,r,sum;
    };
    vector<node> t;
    int Ln,Rn,G,L,R,V;
    void init(int l,int r) {
        Ln=l; Rn=r;
        t.assign(1,{0,0,0});
    }
    int add() {
        t.resize(t.size()+1);
        return t.size()-1;
    }
    void pushup(int x) {
        t[x].sum=t[t[x].l].sum+t[t[x].r].sum;
    }
    int upd(int o,int l,int r) {
        int x=add(); t[x]=t[o];
        if(l==r) t[x].sum=V;
        else {
            int mid=(l+r)>>1;
            if(G<=mid) t[x].l=upd(t[x].l,l,mid);
            else t[x].r=upd(t[x].r,mid+1,r);
            pushup(x);
        }
        return x;
    }
    int update(int o,int g,int v) {
        return G=g, V=v, upd(o,Ln,Rn);
    }
    int merge(int o1,int o2) {
        if(!o1||!o2) return o1+o2;
        int x=add(); {
            int l=merge(t[o1].l,t[o2].l);
            int r=merge(t[o1].r,t[o2].r);
            int sum=t[o1].sum+t[o2].sum;
            t[x]={l,r,sum};
        }
        return x;
    }
    int qry(int x,int l,int r) {
        if(L<=l&&r<=R) return t[x].sum;
        int mid=(l+r)>>1,res=0;
        if(L<=mid) res+=qry(t[x].l,l,mid);
        if(R>mid) res+=qry(t[x].r,mid+1,r);
        return res;
    }
    int query(int x,int l,int r) {
        return L=l, R=r, qry(x,Ln,Rn);
    }
};
