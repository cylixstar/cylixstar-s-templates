/**********************************
* The Area of Union of N-Dim Rectangle
* author: cylixstar
* date: 2010-09-20
************************************/
//There M of rects
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

struct scube{
    vector<int> low;
    vector<int> hi;
};

typedef long long ll;
const int MOD=14121413;
const int MAXM=100+10;
int n,m;
scube cs[MAXM];

bool isIn(const scube& s1,const scube& s2){
    int i;
    for(i=0;i<n;i++)
        if(s1.low[i]<s2.low[i] || s1.hi[i]>s2.hi[i])return false;
    return true;
}

//Make sure <hi> must higher than <low> 
ll divide_and_cal(scube& range,int dim,int pos){
    int i;
    for(i=0;i<n;i++)if(range.hi[i]==range.low[i])return 0;
    if(pos==m){
        ll ans=1;
        for(i=0;i<n;i++)
            ans=ans*(range.hi[i]-range.low[i])%MOD;
        return ans;
    }
    scube& cur=cs[pos];
    if(isIn(range,cur))return 0;
    int tlow,thi;
    if(dim==0){
        for(i=0;i<n;i++){
            tlow=max(range.low[i],cur.low[i]);
            thi=min(range.hi[i],cur.hi[i]);
            if(tlow>thi){
                return divide_and_cal(range,0,pos+1);
            }
        }
    }
    ll ans=0;
    int t1,t2;
    t1=max(range.low[dim],cur.low[dim]);
    t2=min(range.hi[dim],cur.hi[dim]);
    tlow=range.low[dim];
    thi=range.hi[dim];    

    range.low[dim]=t1,range.hi[dim]=t2;
    ans = (ans + divide_and_cal(range,dim+1,pos))%MOD;

    range.low[dim]=tlow,range.hi[dim]=t1;
    ans = (ans + divide_and_cal(range,0,pos+1))%MOD;

    range.low[dim]=t2,range.hi[dim]=thi;
    ans= (ans + divide_and_cal(range,0,pos+1))%MOD;

    range.low[dim]=tlow,range.hi[dim]=thi;
    return ans;
}

ll solve(){
    int i;
    ll ans=0;
    for(i=0;i<m;i++){
        ans+=divide_and_cal(cs[i],0,i+1);
        ans%=MOD;
    }
    return ans;
}

int main(){
    while(scanf("%d%d",&m,&n)!=EOF){
        int i,j,k;
        for(i=0;i<m;i++)cs[i].hi.clear(),cs[i].low.clear();
        for(i=0;i<m;i++){
            for(j=0;j<n;j++){
                scanf("%d",&k);
                cs[i].low.push_back(k);
            }
            for(j=0;j<n;j++){
                scanf("%d",&k);
                cs[i].hi.push_back(k);
            }
        }
        ll ans=solve();
        cout<<ans<<endl;
    }
    return 0;
}

