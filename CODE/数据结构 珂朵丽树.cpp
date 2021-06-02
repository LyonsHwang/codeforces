struct CTL {
    map<int,ll> arr; 
    void init(int l,int r) {
        arr.clear();
        arr[l]=arr[r+1]=0;
    }
    auto split(int x) -> decltype(arr.end()) {
        auto zx(--arr.upper_bound(x));
        if(zx->first!=x) 
            arr[x]=zx->second,++zx;
        return zx;
    }
    void assign(int l,int r,ll v) {
        auto zl=split(l),zr=split(r+1);
        for((zl++)->second=v;zl!=zr;)
            arr.erase(zl++);
    }
    void operate(int l,int r,void op(ll &v,int c)) {
        auto zl=split(l),zr=split(r+1);
        while(zl!=zr) {
            auto lv=zl++;
            op(lv->second,zl->first-lv->first);
        }
    }
};
