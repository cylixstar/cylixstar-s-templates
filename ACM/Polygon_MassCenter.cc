/****
** Get the Mass Center of Polygon
* by cylixstar @ 2010-10-9
***/
//the points in pt should be clockwise or counter-clockwise
point massCenter(int n,const point* pt){
    int i,j;
    point ans;
    double A=0.0,T;
    ans.x=ans.y=0.0;
    for(i=0;i<n;i++){
        j=(i+1) % n;
        T=pt[i].x*pt[j].y-pt[j].x*pt[i].y;
        ans.x+=(pt[i].x+pt[j].x)*T;
        ans.y+=(pt[i].y+pt[j].y)*T;
        A += T;
    }
    if(fabs(A)>eps){
        ans.x/=3.0 * A;
        ans.y/=3.0 * A;
    }
    return ans;
}

