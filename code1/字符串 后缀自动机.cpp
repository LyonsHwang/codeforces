struct SAM {
    struct state {
        int fa,len;
        vector<int> nxt;
    };
    vector<state> m;
    vector<int> R,idx,cnt;
    void init() {
        m.assign(2,{0,0,vector<int>(26)});
        R.assign(2,0);
    }
    int add() {
        m.resize(m.size()+1);
        R.push_back(0);
        return m.size()-1;
    }
    int touch(int x,int c) {
        int y=m[x].nxt[c],len=m[x].len+1;
        if(y) {
            if(m[y].len==len) return y;
            int z=add();
            m[z]={m[y].fa,len,m[y].nxt};
            for(m[y].fa=z;m[x].nxt[c]==y;x=m[x].fa) m[x].nxt[c]=z;
            return z;
        } else {
            y=add();
            for(;x&& !m[x].nxt[c];x=m[x].fa) m[x].nxt[c]=y;
            int fa=(!x)? 1: touch(x,c);
            m[y]={fa,len,m[0].nxt};
            return y;
        }
    }
    int extend(int x,int c) {
        int res=touch(x,c);
        return ++R[res],res;
    }
    void index() {
        idx.assign(m.size(),0);
        cnt.assign(m.size(),0);
        loop(i,m.size()) cnt[m[i].len]++;
        rep(i,1,m.size()) cnt[i]+=cnt[i-1];
        lback(i,m.size()) idx[--cnt[m[i].len]]=i;
    }
    void calcR() {
        rback(i,2,m.size()) R[m[idx[i]].fa]+=R[idx[i]];
    }
};
