struct Splay {
    struct node {
        int fa,ch[2],sz;
        ll val,tag;
        int side(int x) { return ch[1]==x; }
        void repl(int x,int y) { ch[side(x)]=y; }
        void flip() { swap(ch[0],ch[1]); tag^=1; }
    };
    vector<node> t;
    int root;
    int add() {
        t.push_back(t[0]);
        return t.size()-1;
    }
    void adj(int x) {
        if(!x) return;
        t[x].flip();
    }
    void push(int x) {
        if(!t[x].tag) return;
        adj(t[x].ch[0]);
        adj(t[x].ch[1]);
        t[x].tag=0;
    }
    void pull(int x) {
        if(!x) assert(0);
        t[x].sz=t[t[x].ch[0]].sz+t[t[x].ch[1]].sz+1;
    }
    void rotate(int x,int &o) {
        int y=t[x].fa,z=t[y].fa;
        int l=t[y].side(x);
        int &w=t[x].ch[!l];
        if(y==o) o=x; else t[z].repl(y,x);
        t[x].fa=z; t[y].fa=x; t[w].fa=y;
        t[y].ch[l]=w; w=y;
        pull(y);
    }
    void splay(int x,int &o) {
        stack<int> stk;
        for(int i=x;i!=o;i=t[i].fa) stk.push(i);
        for(push(o); stk.size(); stk.pop()) push(stk.top());
        for(; x!=o; rotate(x,o)) {
            int y=t[x].fa,z=t[y].fa;
            if(y!=o) rotate((t[y].side(x)^t[z].side(y))? x: y, o);
        }
        pull(x);
    }
    int find(int x,int k) {
        push(x);
        int l=t[x].ch[0],r=t[x].ch[1];
        if(t[l].sz+1==k) return x;
        return (k<=t[l].sz)? find(l,k): find(r,k-t[l].sz-1);
    }
    int find(int K) {
        return find(root,K+1);
    }
    void adjust(int L,int R) {
        int l=find(root,L);
        int r=find(root,R+1);
        splay(l,root);
        splay(r,t[l].ch[1]);
        adj(t[r].ch[0]);
    }
    int insert(int K) {
        int l=find(root,K);
        int r=find(root,K+1);
        splay(l,root);
        splay(r,t[l].ch[1]);
        int x=add();
        t[x].fa=r; t[r].ch[0]=x;
        return splay(x,root),x;
    }
    void init() {
        t.resize(1); add(); add();
        t[2].fa=1; t[1].ch[1]=2;
        splay(2,root=1);
    }
};
