struct Dijkstra {
    struct edge {
        int to; ll c;
    };
    vector<vector<edge>> go;
    vector<ll> dis;
    int n;
    int get() {
        go.push_back({});
        return n++;
    }
    void add(int u,int v,ll w) {
        go[u].push_back({v,w});
        // go[v].push_back({u,w});
    }
    void init(int n_) {
        n=n_;
        go.assign(n,{});
    }
    ll run(int s,int t) {
        dis.assign(n,INF64);
        dis[s]=0;
        priority_queue<pli,vector<pli>,greater<pli>> pq;
        pq.push(pli(0,s));
        while(!pq.empty()) {
            auto [d,x]=pq.top(); pq.pop();
            if(x==t) return d;
            if(d>dis[x]) continue;
            for(auto [to,c]: go[x])
                if(dis[to]>dis[x]+c) {
                    dis[to]=dis[x]+c;
                    pq.push(pli(dis[to],to));
                }
        }
        return dis[t];
    }
};
