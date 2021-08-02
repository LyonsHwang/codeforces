struct Blossom {
    int n,mkn;
    vector<int> fa,mk,mat,pre,sta;
    vector<vector<int>> go;
    queue<int> que;
    void init(int n_) {
        n=n_;
        go.assign(n,{});
        mat.assign(n,-1);
        fa.resize(n);
        mk.resize(n);
        sta.resize(n);
        pre.resize(n);
    }
    void add(int u,int v) {
        go[u].push_back(v);
        go[v].push_back(u);
    }
    int get(int x) {
        while(fa[x]!=x) x=fa[x]=fa[fa[x]];
        return x;
    }
    int lca(int u,int v) {
        for(++mkn;;swap(u,v)) if(u!=-1) {
            if(mk[u=get(u)]==mkn)
                return u;
            mk[u]=mkn;
            u=(mat[u]==-1)?-1:pre[mat[u]];
        }
    }
    void shrink(int u,int v) {
        for(int x,y; u!=v; u=y) {
            x=mat[u], y=pre[x];
            if(get(y)!=v) pre[y]=x;
            if(fa[x]==x) fa[x]=v;
            if(fa[u]==u) fa[u]=v;
            if(!sta[x]) que.push(x), sta[x]=1;
            if(!sta[y]) que.push(y), sta[y]=1;
        }
    }
    bool augment(int s) {
        loop(i,n) pre[i]=-1,sta[i]=-1,fa[i]=i;
        que=queue<int>();
        que.push(s); sta[s]=1;
        while(mat[s]==-1&&!que.empty()) {
            int x=que.front(); que.pop();
            for(auto y: go[x]) if(get(y)!=get(x)) {
                if(sta[y]==-1) {
                    if(mat[y]==-1) {
                        for(int z; x!=-1; x=pre[y=z]) {
                            z=mat[x], mat[y]=x, mat[x]=y;
                            if(z==-1) break;
                        }
                        return true;
                    } else {
                        pre[y]=x; sta[y]=0;
                        que.push(mat[y]); sta[mat[y]]=1; 
                    }
                } else if(sta[y]==1) {
                    int z=lca(x,y);
                    if(get(x)!=z) pre[x]=y, shrink(x,z);
                    if(get(y)!=z) pre[y]=x, shrink(y,z);
                }
            }
        }
        return false;
    }
    int greedy() {
        int ans=0;
        loop(i,n) if(mat[i]==-1) 
            for(auto j: go[i]) if(mat[j]==-1) {
                ++ans, mat[i]=j, mat[j]=i;
                break;
            }
        return ans;
    }
    int match() {
        int ans=greedy();
        loop(i,n) if(mat[i]==-1) ans+=augment(i);
        return ans;
    }
};
