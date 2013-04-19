/**********************************
* Area of circles union or intersect
* author: cylixstar
* date: 2010-09-09
************************************/
const double EPS=1e-6;
const double PI=acos(-1.0);
struct Pt{
    double x,y;
    Pt(double x,double y):x(x),y(y){}
    Pt(){}
    Pt operator +(Pt r)const{
        return Pt(x+r.x,y+r.y);
    }
    Pt operator -(Pt r)const{
        return Pt(x-r.x,y-r.y);
    }
    Pt operator *(double k)const{
        return Pt(x*k,y*k);
    }
};

double dpr(Pt a,Pt b){
    return a.x*b.x+a.y*b.y;
}

//<0 when a at the ccw side of b
double ccw(Pt a,Pt b){
    return a.x*b.y-a.y*b.x;
}

struct Circle{
    Pt c;
    double r;
};

double inline sqr(double x){
    return x*x;
}


//Judge if circle a contains circle b
bool isContain(const Circle& a,const Circle& b){
    if(b.r>a.r+EPS)return false;
    Pt cd=a.c-b.c;    
    //<=
    return hypot(cd.x,cd.y)<a.r-b.r+EPS;
}

//Get the intersection of two circles
//Make sure they don't contain the other one
//return if they have common point;
//not allow single common point
//simple adjust to achieve it
bool cirInter(const Circle& a,const Circle& b,Pt& p1,Pt& p2){
    Pt cd=b.c-a.c;
    double d=hypot(cd.x,cd.y);
    if(hypot(cd.x,cd.y)>a.r+b.r-EPS)return false;
    double cs=(sqr(a.r)+sqr(d)-sqr(b.r))*0.5/(a.r*d);
    double ss=sqrt(1.0-cs*cs);
    p1=Pt(cd.x*cs-cd.y*ss,cd.x*ss+cd.y*cs)*(a.r/d)+a.c;
    p2=Pt(cd.x*cs+cd.y*ss,-cd.x*ss+cd.y*cs)*(a.r/d)+a.c;
    return true;
}


//Get the area of the union of n circles
//can be chang into intersection area
//by simple adjustment
double cirUnion(int n,Circle* cir){
    //remove the circle that contains by others
    vector<bool>remv(n,false);
    int i,j;
    for(i=0;i<n;i++)
        if(!remv[i]){
            for(int j=0;j<n;j++)
                //change into if(i!=j && !remv[j] && isContain(cir[j],cir[i]))
                //if you want to do intersection
                if(i!=j && !remv[j] && isContain(cir[i],cir[j]))
                    remv[j]=true;
        }
    for(i=0,j=0;i<n;i++){
        if(!remv[i])
            cir[j++]=cir[i];
    }
    n=j;
    double ans=0.0,A=0.0;
    //first : the angle
    //second : the flag;
    vector<pair<double,int> > inter;
    inter.reserve(3*n+4);
    Pt p1,p2,mid;
    double a1,a2,ma;
    for(i=0;i<n;i++){
        inter.clear();
        inter.push_back(make_pair(-PI,0));
        inter.push_back(make_pair(0.0,0));
        inter.push_back(make_pair(PI,0));
        for(j=0;j<n;j++)
            if(i!=j && cirInter(cir[i],cir[j],p1,p2)){
                p1=p1-cir[i].c;
                p2=p2-cir[i].c;
                a1=atan2(p1.y,p1.x);
                a2=atan2(p2.y,p2.x);
                if(a1>a2)swap(a1,a2);
                ma=(a1+a2)*0.5;
                mid=Pt(cos(ma),sin(ma))*cir[i].r+cir[i].c;
                if(hypot(mid.x-cir[j].c.x,mid.y-cir[j].c.y)<cir[j].r+EPS){
                    inter.push_back(make_pair(a1,-1));
                    inter.push_back(make_pair(a2,1));
                }else{
                    inter.push_back(make_pair(-PI,-1));
                    inter.push_back(make_pair(a1,1));
                    inter.push_back(make_pair(a2,-1));
                }
            }
        sort(inter.begin(),inter.end());
        int s=inter.size(),p=0;
        for(j=0;j<s-1;j++){
            p+=inter[j].second;
            //change into p==1-n if you want to do intersection
            if(p==0){
                a1=inter[j].first;
                a2=inter[j+1].first;
                ma=a2-a1;
                ans+=(ma-sin(ma))*0.5*cir[i].r*cir[i].r;
                A+=ccw(Pt(cos(a1),sin(a1))*cir[i].r+cir[i].c,
                    Pt(cos(a2),sin(a2))*cir[i].r+cir[i].c)*0.5;
            }
        }
    }
    return A+ans;
}


