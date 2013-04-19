/******************
* Closest Pair of Points
* author: cylixstar
* date:2010-10-20
*****************/
const double EPS=1e-6;
const double inf=1e18;
const int maxn=100000+10;

struct Pt{
    double x,y;
};

inline bool xcmp(const Pt& p1,const Pt& p2){
    return p1.x<p2.x;
}

inline bool ycmp(const Pt& p1,const Pt& p2){
    return p1.y<p2.y;
}

Pt mp[maxn];

//Make sure pts are sorted by x
double closestPair(int n,Pt* pts){
    if(n<2)return inf;
    int mid = n/2;
    double mx = pts[mid].x;
    double d = min(closestPair(mid,pts),closestPair(n-mid,pts+mid));
    if(d<EPS)return d;
    inplace_merge(pts,pts+mid,pts+n,ycmp);
    int i,j,ln=0,p1=0;
    for(i=0;i<n;i++)
        if(fabs(pts[i].x-mx)<d){
            while(p1<ln && pts[i].y-mp[p1].y>d)p1++;
            if(p1<ln)
                for(j=p1;j<ln;j++)
                    d = min(d, hypot(mp[j].x-pts[i].x,mp[j].y-pts[i].y));
            mp[ln++]=pts[i];
        }
    return d;
}

double solve(int n,Pt *pts){
    sort(pts,pts+n,xcmp);
    return closestPair(n,pts);
}

