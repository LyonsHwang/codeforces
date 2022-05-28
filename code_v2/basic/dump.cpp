#ifndef INCLUDE_DUMP
#define INCLUDE_DUMP

#define promising

using namespace std;

#define ALL(x) (x).begin(), (x).end()

template <typename Iter> ostream &_out(ostream &s, Iter b, Iter e);

// int128
ostream &operator<<(ostream &s, const __int128 &i) { return s << (long long)i; }

// pair
template <typename A, typename B> ostream &operator<<(ostream &s, const pair<A, B> &p) { return s << "(" << p.first << "," << p.second << ")"; }

// vector
template <typename T> ostream &operator<<(ostream &s, const vector<T> &c) { return _out(s, ALL(c)); }

// array
template <typename T, size_t N> ostream &operator<<(ostream &s, const array<T, N> &c) { return _out(s, ALL(c)); }

// set
template <typename T> ostream &operator<<(ostream &s, const set<T> &c) { return _out(s, ALL(c)); }

// map
template <typename A, typename B> ostream &operator<<(ostream &s, const map<A, B> &c) { return _out(s, ALL(c)); }

// name
template <typename T> void _dump(const char *s, T &&head) { cerr << s << "=" << head << endl; }

// iterate
template <typename Iter> ostream &_out(ostream &s, Iter b, Iter e) {
    s << "[";
    for (auto it = b; it != e; it++) s << (it == b ? "" : " ") << *it;
    s << "]";
    return s;
}

template <typename T> void _arr(T *b, T *e) {
    cerr << "[";
    for (auto it = b; it != e; it++) cerr << (it == b ? "" : " ") << *it;
    cerr << "]"<<endl;
}

// one by one
template <typename T, typename... Args> void _dump(const char *s, T &&head, Args &&...tail) {
    int c = 0;
    while (*s != ',' || c != 0) {
        if (*s == '(' || *s == '[' || *s == '{') c++;
        if (*s == ')' || *s == ']' || *s == '}') c--;
        cerr << *s++;
    }
    cerr << "=" << head << ", ";
    _dump(s + 1, tail...);
}

// add name
#define dump(...)                                                   \
    do {                                                            \
        fprintf(stderr, "%s:%d - ", __PRETTY_FUNCTION__, __LINE__); \
        _dump(#__VA_ARGS__, __VA_ARGS__);                           \
    } while (0);
#endif
