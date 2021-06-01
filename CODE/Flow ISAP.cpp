struct ISAP {
    int n,s,t;
    struct edge { int to,rev; ll c; };
    vector<vector<edge>> adj;
    vector<int> gap,cur,h;
    void init(int n_,int s_,int t_) {
        n=n_,s=s_,t=t_;
        adj.assign(n,{});
        cur.assign(n,0);
        gap.assign(n,0);
        h.assign(n,0);
    }
    void add(int fr,int to,ll c,bool d=true) {
        adj[fr].push_back({to,(int)adj[to].size(),c});
        adj[to].push_back({fr,(int)adj[fr].size()-1,d?0:c});
    }
    void bfs() {
        for(int i=0;i<n;i++) h[i]=INF;
        queue<int> q({t}); h[t]=0;
        while(!q.empty()) {
            int v=q.front(); q.pop(); ++gap[h[v]];
            for(auto &e: adj[v]) {
                if(h[e.to]==INF&&adj[e.to][e.rev].c>0) {
                    q.push(e.to); 
                    h[e.to]=h[v]+1;
                }
            }
        }
    }
    ll dfs(int u,ll cap) {
        if(u==t) return cap;
        ll res=0;
        for(auto &i=cur[u];i<adj[u].size();i++) {
            auto &e=adj[u][i];
            if(e.c>0&&h[u]==h[e.to]+1) {
                ll foo=dfs(e.to,min(cap,e.c));
                res+=foo; cap-=foo;
                e.c-=foo; adj[e.to][e.rev].c+=foo;
                if(!cap) return res;
            }
        }
        if(h[s]<INF) {
            if(!(--gap[h[u]])) h[s]=INF;
            else ++gap[++h[u]], cur[u]=0;
        }
        return res;
    }
    ll flow() {
        ll ans=0;
        for(bfs();h[s]<INF;ans+=dfs(s,INF64));
        return ans;
    }
};
