struct Match {
    int n1,n2;
    vector<vector<int>> g;
    vector<int> mat,vis;
    void init(int n1_,int n2_) {
        n1=n1_; n2=n2_;
        g.assign(n1,{});
    }
    void add(int u,int v) {
        g[u].push_back(v);
    }
    int find(int x) {
        if(vis[x]) return 0;
        vis[x]=1;
        for(auto y: g[x])
            if(mat[y]==-1||find(mat[y])) 
                return mat[y]=x, 1;
        return 0;
    }
    int work() {
        int res=0;
        mat.assign(n2,-1);
        loop(i,n1) {
            vis.assign(n1,0);
            res+=find(i);
        }
        return res;
    }
};
