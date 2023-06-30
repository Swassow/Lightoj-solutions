#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
#include <string.h>
//#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define INF (ll)1e9
#define MOD (ll)1000000007
#define pb push_back
#define all(v) v.begin(),v.end()
#define rep(i,n) for (int i = 1; i < n; i++)
#define scc(n) scanf("%d",&n);
#define sccc(n) scanf("%lld",&n);
#define printi(n) printf("%d",n);
#define printll(n) printf("%lld\n",n);
#define ya cout<<"Yes\n";
#define no cout<<"No\n";
#define pii pair<int,int>
#define pll pair<ll,ll>
#define ff  first
#define ss  second
#define endl "\n"
#define f ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
const int N=300000;
vector<int>gr[N],flat;
bool vis[N];
int pos[N],cnt[N],seg_ara[N],neg[N],level[N],par[N],table[20][N],seg_ara2[N];
vector<ll>seg;
void dfs(int node,int l)
{
    level[node]=l;
    vis[node]=true;
    flat.pb(node);
    for(auto it:gr[node])
    {
        if(!vis[it])
        {
            par[it]=node;
            dfs(it, l+1);
        }
    }
    flat.pb(node);
}
void build(int n)
{
    for(int i=0;i<n;i++)
        table[0][i]=par[i];
    for(int i=1;i<20;i++)
    {
        for(int j=0;j<n;j++)
            table[i][j]=table[i-1][table[i-1][j]];
    }
}
int lca(int u,int v)
{
    if(level[u]>level[v])
        swap(u,v);
    int k=level[v]-level[u];
    for(int i=19;i>=0;i--)
    {
        int mask=1<<i;
        if(k&mask)
            v=table[i][v];
    }
    if(u==v)
        return v;
    for(int i=19;i>=0;i--)
    {
        int up=table[i][u];
        int vp=table[i][v];
        if(up!=vp)
        {
            u=up;
            v=vp;
        }
    }
    return par[u];
}

ll tree[4*N];
 
void built(int root,int left,int right)
{
    if(left == right)
    {
        tree[root] = seg[left];
        return ;
    }
    built(2*root,left,(left+right)/2);
    built(2*root+1,((left+right)/2) + 1,right);
    tree[root] = tree[2*root] + tree[2*root + 1];
}
 
long long query(int root,int left,int right,int l,int r)
{
    if(r < left || l > right) return 0;
    if(left >= l && right <= r)
    {
        return tree[root];
    }
    long long sumLeft = query(2*root,left,(left+right)/2,l,r);
    long long sumRight = query(2*root + 1,((left+right)/2) + 1,right,l,r);
    return sumLeft + sumRight;
}
 
void update(int root,int left,int right,int k,int u)
{
    if(k < left || k > right) return;
    if(left == k && right == k)
    {
        tree[root] = u;
        return;
    }
    update(2*root,left,(left+right)/2,k,u);
    update(2*root+1,((left+right)/2) + 1,right,k,u);
    tree[root] = tree[2*root] + tree[2*root + 1];
}


void solve()
{
    int n,u,v;
    cin>>n;
    for(int i=0;i<=n;i++)
    {
        gr[i].clear();
        vis[i]=false;
        cnt[i]=0;
    }
    seg.clear();
    flat.clear();
    int ara[n];
    for(int i=0;i<n;i++)
        cin>>ara[i];
    for(int i=0;i<n-1;i++)
    {
        cin>>u>>v;
        gr[u].pb(v);
        gr[v].pb(u);
    }
    dfs(0,1);
    build(n);
//    for(auto it:flat)
//        cout<<it<<" ";
//    cout<<endl;
    for(int i=0;i<flat.size();i++)
    {
        if(cnt[flat[i]]==0)
        {
            pos[flat[i]]=i;
            cnt[flat[i]]++;
            seg_ara[i]=ara[flat[i]];
        }
        else
        {
            seg_ara[i]=-ara[flat[i]];
            neg[flat[i]]=i;
        }
    }
    seg.pb(0);
    for(int i=0;i<flat.size();i++)
        seg.pb(seg_ara[i]);
    int q,type;
    cin>>q;
    built(1, 1, seg.size());
    while(q--)
    {
        cin>>type;
        if(type==0)
        {
            cin>>u>>v;
            ll ans=0;
            int Lca=lca(u, v);
            ans+=query(1, 1, seg.size(), pos[Lca]+1, pos[u]+1);
            ans+=query(1, 1, seg.size(), pos[Lca]+1, pos[v]+1);
            ans-=query(1, 1, seg.size(), pos[Lca]+1, pos[Lca]+1);
            cout<<ans<<endl;
        }
        else
        {
            cin>>u>>v;
            //cout<<seg[pos[u]+1]<<" "<<seg[neg[u]+1]<<endl;
            update(1,1,seg.size(),pos[u]+1,v);
            update(1,1,seg.size(),neg[u]+1,-v);
        }
    }
}
int main()
{
    f
    int t=1;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        cout<<"Case "<<i<<":"<<endl;
        solve();
    }
}
/*
 //for calculating nCr mod M where M is prime.
 ll power(ll x,ll y, ll p)
 {
     ll res = 1;
     x = x % p;
     while (y > 0)
     {
         if (y & 1)
             res = (res * x) % p;
         y = y >> 1;
         x = (x * x) % p;
     }
     return res;
 }
 ll factorial[N];
 void fact()
 {
     factorial[0]=1;
     for(ll i=1;i<=N;i++)
     {
         factorial[i]=(factorial[i-1]%MOD*i%MOD)%MOD;
     }
 }
 ll modInverse(ll n,ll p)
 {
     return power(n, p - 2, p);
 }
 ll nCrModPFermat(ll n,ll r, ll p)
 {
     if (n < r)
         return 0;
     if (r == 0)
         return 1;
     ll ans=factorial[n];
     ll x=(factorial[n-r]%p*factorial[r]%p)%p;
     ans=(ans%p* modInverse(x, p)%p)%p;
     return ans;
 }
 */

/*
 //for calculating nCr less than 10^18
 ll gcd(ll a,ll b)
 {
     if(b==0)
         return a;
     return gcd(b,a%b);
 }
 ll nCr(ll n,ll r)
 {
     ll p=1,q=1;
     if(n-r<r)
         r=n-r;
     while(r)
     {
         p*=n;
         q*=r;
         ll g=gcd(p,q);
         p/=g;
         q/=g;
         n--;
         r--;
     }
     return p;
 }
 */
/*
 ll power(ll x,ll y, ll p)
 {
     ll res = 1;
     x = x % p;
     while (y > 0)
     {
         if (y & 1)
             res = (res * x) % p;
         y = y >> 1;
         x = (x * x) % p;
     }
     return res;
 }
 ll power(ll x,ll y)
 {
     ll res = 1;
     while (y > 0)
     {
         if (y & 1)
             res = (res * x);
         y = y >> 1;
         x = (x * x);
     }
     return res;
 }
 bool fl[N+1];
 vector<ll> sieve(ll n)
 {
     vector<ll> primes;
     for(ll i=3; i*i<=n; i+=2)
         for(ll j=i*i; j<=n; j+=i+i)
             fl[j]=true;

     primes.pb(2);
     for(ll i=3; i<=n; i+=2) if(!fl[i]) primes.pb(i);
     return primes;
 }
 vector<ll> p=(sieve(N));
 vector<pll> prime_fact(ll n)
  {
     vector<pll>v;
     for(ll i=0;i<p.size()&& p[i]*p[i]<=n;i++)
      {
          if(n%p[i]==0)
          {
              ll cnt=0;
              while(n%p[i]==0)
              {
                  cnt++;
                  n/=p[i];
              }
              v.pb({p[i],cnt});
          }
      }
      if(n>1)
          v.pb({n,1});
     return v;
  }

*/

/*
 prime fact using log(n) upto 10^7
 int prime[N];
 void seive()
 {
     for(int i=2;i<N;i++)
         prime[i]=i;
     prime[1]=1;
     for(int i=4;i<N;i+=2)
         prime[i]=2;
     for(int i=3;i*i<N;i++)
     {
         if(prime[i]==i)
         {
             for(int j=i*i;j<N;j+=i)
                 prime[j]=i;
         }
     }
 }
 vector<int>prime_fact(int n)
 {
     vector<int>v;
     while(n!=1)
     {
         v.pb(prime[n]);
         n/=prime[n];
     }
     return v;
 }
 */
/*
 //Direction of a point from a line segment
 
 struct point{
     double x,y;
 };
 point subtract(point p1,point p2)
 {
     point res;
     res.x=p1.x-p2.x;
     res.y=p1.y-p2.y;
     return res;
 }
 int get_dir(point a,point b,point c)
 {
     b=subtract(b,a);
     c=subtract(c,a);
     double res=b.x*c.y-b.y*c.x;
     if(res>0)
         return -1; //left
     else if (res<0)
         return 1; //right
     else
         return 0; //on the line
     
 }
 */


/*
//nCr mod m (where m is not a prime)
//code for:
//nC1 nC2 nC3.... which are divisible by m and which are not.
 
 ll n,m;
 cin>>n>>m;
 vector<pll>need;
 for(i=2;i*i<=m;i++)
 {
     if(m%i==0)
     {
         ll cnt=0;
         while(m%i==0)
         {
             cnt++;
             m/=i;
         }
         need.pb({i,cnt});
     }
 }
 if(m>1)
     need.pb({m,1});
 vector<pll>have=need;
 for(auto &it:have)
     it.ss=0;
 vector<ll>ans;
 for(i=1;i<=n;i++)
 {
     ll x=n-i+1;
     for(auto &it:have)
     {
         while(x%it.ff==0)
         {
             it.ss++;
             x/=it.ff;
         }
     }
     x=i;
     for(auto &it:have)
     {
         while(x%it.ff==0)
         {
             it.ss--;
             x/=it.ff;
         }
     }
     bool flag=true;
     for(j=0;j<need.size();j++)
     {
         if(have[j].ss<need[j].ss)
         {
             flag=false;
             break;
         }
     }
     if(flag)
         ans.pb(i+1);
 }
 
 
 */
