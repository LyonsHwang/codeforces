struct EBCC {
    struct edge {
        int to,id;
    };
    int n;
    vector<int> low,dfn,stk,bel,pos;
    vector<vector<int>> bcc;
    vector<vector<edge>> go;
    void init(int n_) {
        n=n_;
        stk.clear();
        pos.clear();
        bcc.clear();
        go.assign(n,{});
        low.assign(n,-1);
        dfn.assign(n,-1);
        bel.assign(n,-1);
    }
    void add(int u,int v,int id) {
        go[u].push_back({v,id});
        go[v].push_back({u,id});
    }
    void ins(int x) {
        int b=isz(bcc),y;
        bcc.push_back({});
        lyons do {
            y=stk.back();
            stk.pop_back();
            bel[y]=b;
            bcc[b].push_back(y);
        } while(x!=y);
    }
    void dfs(int x,int fr) {
        low[x]=dfn[x]=isz(pos);
        pos.push_back(x);
        stk.push_back(x);
        for(auto &e: go[x]) {
            if(dfn[e.to]==-1) {
                dfs(e.to,e.id);
                umin(low[x],low[e.to]);
            } else if(e.id!=fr) {
                umin(low[x],dfn[e.to]);
            }
        }
        if(low[x]==dfn[x]) ins(x);
    }
    int work() {
        loop(i,n) if(dfn[i]==-1) dfs(i,-1);
        return isz(bcc);
    }
};
