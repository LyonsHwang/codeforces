struct Matrix {
    vector2D<ll> v;
    int R() { return v.size(); }
    int C() { return v[0].size(); }
    Matrix() {}
    Matrix(vector2D<ll> v): v(v) {}
    Matrix(int n) {
        v.resize(n,vector<ll>(n));
        loop(i,n) v[i][i]=1;
    }
    Matrix(int n,int m) {
        v.resize(n,vector<ll>(m));
    }
    friend Matrix operator *(Matrix &a, Matrix &b) {
        Matrix c(a.R(),b.C());
        loop(i,a.R()) loop(j,a.C()) loop(k,b.C())
            c.v[i][k]=(c.v[i][k]+a.v[i][j]*b.v[j][k])%P;
        return c;
    }
    Matrix power(ll m) {
        Matrix a(R()), b(v);
        for(;m;m>>=1,b=b*b)
            if(m&1) a=a*b;
        return a;
    }
};
