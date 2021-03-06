#include <bits/stdc++.h>
#include <unordered_map>
#include <unordered_set>
using namespace std;

/*** Template Begins ***/

typedef long long                   ll;
typedef pair<ll,ll>                 PII;
typedef pair<ll, pair<int, int> >   PIII;
typedef vector<int>                 vi;
typedef vector<pair<int, int> >     vii;

#define endl         '\n'
#define pb           push_back
#define INF          INT_MAX/10
#define F            first
#define S            second
#define mp           make_pair
#define ios          ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define hell         1000000007
#define all(a)       (a).begin(),(a).end()
#define fr(i,a,b)    for(int i=a;i<=b;i++)
#define lp(i,a)      for(int i=0;i< a;i++)
ll power(ll x, ll y, ll p){ ll res = 1;x = x % p;while (y > 0){ if (y & 1) res = (res*x) % p;y = y>>1;x = (x*x) % p;} return res; } 

// Debug //

#define trace(x)                 cerr << #x << ": " << x << endl;
#define trace1(x)                cerr << #x << ": " << x << endl;
#define trace2(x, y)             cerr << #x << ": " << x << " | " << #y << ": " << y << endl;
#define trace3(x, y, z)          cerr << #x << ": " << x << " | " << #y << ": " << y << " | " << #z << ": " << z << endl;
#define trace4(a, b, c, d)       cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << endl;
#define trace5(a, b, c, d, e)    cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << " | " << #e << ": " << e << endl;
#define trace6(a, b, c, d, e, f) cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << " | " << #e << ": " << e << " | " << #f << ": " << f << endl;

// Constants //

const int N = 1e6+7;
const int NN = 1e4+7;
const int xinc[] = {0, 0, 1, -1};
const int yinc[] = {1, -1, 0, 0};
const long double PI = acos(-1.0);
const double EPS = 1e-9;

/*** Template Ends ***/

int a[NN], tree[4*NN], lval[4*NN], n, q, l, r, v, ty;
bool lazy[4*NN];

/* finding primes here */
bool prime[N];

void find_primes(){
    memset(prime, true, sizeof prime);
    
    for(ll i = 2; i*i < N; i++)
        if (prime[i])
            for(ll j = i*i; j < N; j+=i)    prime[j] = false;
}
/* primes found */

void build(int start, int end, int node){
    if (start == end){
        tree[node] = prime[a[start]];
        return;
    }
    int mid = (start+end)/2;
    build(start, mid, 2*node);
    build(mid+1, end, 2*node+1);
    tree[node] = tree[2*node] + tree[2*node+1];
}

void updateRange(int start, int end, int node, int l, int r, int v){
    if (lazy[node])
    {
        tree[node] = (end-start+1)*prime[lval[node]];
        if (start != end)
        {
            lazy[2*node] = true,    lval[2*node] = lval[node];
            lazy[2*node+1] = true,  lval[2*node+1] = lval[node];
        }
        lazy[node] = false;
    }
    if (r < start || end < l)   return;

    if (start >= l && end <= r)
    {
        tree[node] = (end-start+1)*prime[v];
        if (start != end)
        {
            lazy[2*node] = true,    lval[2*node] = v;
            lazy[2*node+1] = true,  lval[2*node+1] = v;
        }
        return;
    }
    int mid = (start+end)/2;
    updateRange(start, mid, 2*node, l, r, v);
    updateRange(mid+1, end, 2*node+1, l, r, v);
    tree[node] = tree[2*node] + tree[2*node+1];
}

int query(int start, int end, int node, int l, int r){
    if (lazy[node])
    {
        tree[node] = (end-start+1)*prime[lval[node]];
        if (start != end)
        {
            lazy[2*node] = true,    lval[2*node] = lval[node];
            lazy[2*node+1] = true,  lval[2*node+1] = lval[node];
        }
        lazy[node] = false;
    }
    if (r < start || end < l)   return 0;

    if (l <= start && end <= r) return tree[node];
    

    int mid = (start+end)/2;
    int p1 = query(start, mid, 2*node, l, r);
    int p2 = query(mid+1, end, 2*node+1, l, r);

    return p1+p2;
}

void solve(){
    
    memset(a, 0, sizeof a), memset(tree, 0, sizeof tree), memset(lval, 0, sizeof lval), memset(lazy, false, sizeof lazy);

    cin >> n >> q;
    lp(i, n)    cin >> a[i];
    build(0, n-1, 1);

    lp(i, q){
        cin >> ty;
        if (ty == 1)
        {
            cin >> l >> r;
            l--, r--;
            cout << query(0, n-1, 1, l, r) << endl;
        }
        else
        {
            cin >> l >> r >> v;
            l--, r--;
            updateRange(0, n-1, 1, l, r, v);
        }
    }
}

int main(){
    
    ios;
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    find_primes();
    int t;
    cin >> t;
    //t = 1;
    fr(i, 1, t){
        cout << "Case " << i << ":" << endl;
        solve();
    }
    return 0;
}
