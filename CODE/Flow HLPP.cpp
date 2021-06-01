struct HLPP {
    int n,s,t,hi;
    struct edge { int to,rev; ll c; };
    vector<deque<int>> lis;
    vector<vector<edge>> adj;
    vector<int> h,gap;
    vector<ll> r;

    inline edge& rev(const edge &x) {
        return adj[x.to][x.rev];
    }
    void init(int n_,int s_,int t_) {
        n=n_,s=s_,t=t_;
        adj.assign(n,{});
        lis.assign(n,{});
        gap.assign(n,0);
        r.assign(n,0);
        h.assign(n,0);
    }
    void add(int fr,int to,ll c,bool d=true) {
        adj[fr].push_back({to,(int)adj[to].size(),c});
        adj[to].push_back({fr,(int)adj[fr].size()-1,d?0:c});
    }
    void label(int v,int nh) {
        if(h[v]!=INF) gap[h[v]]--; 
        if(h[v]=nh, nh!=INF) {
            gap[hi=nh]++;
            if(r[v]>0) lis[nh].push_back(v);
        }
    }
    void relabel() {
        for(int i=0;i<n;i++) h[i]=INF;
        queue<int> q({t}); h[t]=0;
        while(!q.empty()) {
            int v=q.front(); q.pop(); hi=h[v];
            for(auto &e: adj[v]) {
                if(h[e.to]==INF&&rev(e).c>0)
                    q.push(e.to), label(e.to,h[v]+1);
            }
        }
    }
    void push(int v,edge &e) {
        if(!r[e.to]) lis[h[e.to]].push_back(e.to);
        ll foo=min(r[v],e.c);
        e.c-=foo; rev(e).c+=foo;
        r[v]-=foo; r[e.to]+=foo;
    }
    void push(int v) {
        int nh=INF;
        for(auto &e: adj[v]) if(e.c>0) {
            if(h[v]==h[e.to]+1) {
                push(v,e);
                if(!r[v]) return;
            } else nh=min(nh,h[e.to]+1);
        }
        if(gap[h[v]]>1) label(v,nh); 
        else {
            for(int i=0;i<n;i++)
                if(h[i]>=hi&&h[i]<INF) label(i,INF);
        }
    }
    ll flow() {
        for(int i=0;i<n;i++) r[i]=0;
        r[s]=INF64; r[t]=0;
        relabel();
        for(auto &e: adj[s]) push(s,e);
        label(s,INF);
        for(;hi;hi--) {
            while(!lis[hi].empty()) {
                int v=lis[hi].back();
                lis[hi].pop_back();
                if(h[v]!=INF) push(v);
            }
        }
        return r[t];
    }
};
