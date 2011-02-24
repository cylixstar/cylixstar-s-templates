/******
* Fast Algor to get the intersection point between a convex hull and a ray
* by cylixstar @ 2010-11-1
*
******/
const double eps = 1e-6;

#define sgn(x) ((x)>eps ? 1:(x)<-eps ? -1 : 0)

struct point{
    double x,y;
    point(){}
    point(double x,double y):x(x),y(y){}
    point operator -(const point& r)const{
        return point(x - r.x,y - r.y);
    }
};

double ccw(const point& p1,const point& p2){
    return p1.x*p2.y - p1.y*p2.x;
}
double dpr(const point& p1,const point& p2){
    return p1.x*p2.x + p1.y * p2.y;
}
bool polarCmp(const point& p1,const point& p2){
    char t1 = p1.y < -eps,t2 = p2.y < -eps;
    if(t1!=t2)return t1<t2;
    return ccw(p1,p2)>eps;
}

//sort points in a convex hull
//so that the edge between adjacent points
//are in ascending order in polar angle
//points must be in counter-clockwise
void sortCH(int n,point* pt){
    int i,j,bi = 0,bj = 1 % n;
    for(i=0;i<n;i++){
        j = i + 1;
        if(j==n)j = 0;
        if(polarCmp(pt[j] - pt[i],pt[bj] - pt[bi])){
            bi = i,bj = j;
            break;
        }
    }
    rotate(pt,pt + i,pt + n);
}


//find the first point in a convex hull which
//the directed edge begin with 
//and the polar angle of the edge is greater
//and equals to dir
//the convex must be sorted by sortCH
int findSlope(int n,point* pt,point dir){
    int l,r,m;
    if(n<=1 || polarCmp(pt[0] - pt[n - 1],dir))return 0;
    l = 0,r = n - 1;
    while(l<r){
        m = (l + r) >> 1;
        
        if(polarCmp(pt[m + 1] - pt[m],dir))
            l = m + 1;
        else
            r = m;

    }
    return l;
}


//find the intersection between [from,to] in a convex hull
//"from" may be greater than "to"
//returns if there is an intersection
bool findIntersect(int n,point* pt,point org,point dir,int from ,int to,double& res){
    int len,m,;
    if(to<from)to += n;
    int l = from,r = to,sl = sgn(ccw(pt[from] - org,dir));
    while(l<r){
        m = (l + r + 1)>>1;
        if(sgn(ccw(pt[m % n] - org,dir)) * sl>=0)
            l = m;
        else r = m - 1;
    }
    r = l + 1;
    if(l>=n)l %= n;
    if(r>=n)r %= n;
    res = ccw(pt[l] - org,pt[r] - pt[l]) / ccw(dir,pt[r] - pt[l]);
    if(sgn(res)<0)return false;

    return true;
}

//cacluate the intersections bewteen a ray and
//a convex hull
//the convev hull must be sorted with sortCH
//returns the number of intersections
//and org + p1 * dir and org + p2 * dir would be the intersection 
//if there's only one p1 will equals to p2
//if the ray tagent with the convex hull
//there's no intersection
int fastIntersect(int n,point* pt,point org,point dir,double& p1,double& p2){
    point rdir = point(-dir.x,-dir.y);
    int pi,pj;
    pi = findSlope(n,pt,dir);
    pj = findSlope(n,pt,rdir);
    if(sgn(ccw(pt[pi] - org,dir)) * sgn(ccw(pt[pj] - org,dir))>0)return 0;
    //////The ray go through one of the edge of 
    //the convex hull
    //change the code to handle this special case
    if(sgn(ccw(pt[pi] - org,dir))==0){
        if(sgn(dpr(pt[pi] - org,dir))>=0){
            p1 = p2 = (pt[pi].x - org.x)/dir.x;
            return 1;
        }
        return 0;
    }
    if(sgn(ccw(pt[pj] - org,dir))==0){
        if(sgn(dpr(pt[pj] - org,dir))>=0){
            p1 = p2 = (pt[pj].x - org.x)/dir.x;
            return 1;
        }
        return 0;
    }
    //////////////
    int cnt=0;
    cnt += findIntersect(n,pt,org,dir,pi,pj,p1);
    if(findIntersect(n,pt,org,dir,pj,pi,p2)){
        if(cnt==0)p1 = p2;
        cnt++;
    }
    return cnt;

}

