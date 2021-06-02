struct KMP {
    int n;
    string s;
    vector<int> len;
    vector<bool> suf;
    void init(string &s_) {
        s=s_,n=s.size();
        len.assign(n,0);
        for(int j=0,i=1;i<n;i++) {
            while(j>0&&s[j]!=s[i]) j=len[j-1];
            if(s[j]==s[i]) ++j;
            len[i]=j;
        }
    }
    void suffix() {
        suf.assign(n+1,0);
        suf[n]=suf[0]=true;
        for(int i=len[n-1];i;i=len[i-1]) suf[i]=true;
    }
    int trans(int k,int c) {
        while(k==n||(k>0&&s[k]!=c)) k=len[k-1];
        if(s[k]==c) ++k;
        return k;
    }
};
