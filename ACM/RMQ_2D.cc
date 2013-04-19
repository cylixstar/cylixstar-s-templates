/******************
* author: cylixstar
* date:2010-10-20
* 2D-RMQ
*****************/
const int maxn=110;
int m,n;
int rmq[10][10][maxn][maxn];
int lg[maxn];
void getlg(){
    lg[0]=0;
    for(int i=0,j=2,k=1;k<maxn;i++,j<<=1)
        for(;k<j && k<maxn;k++)
            lg[k]=i;
}
void build_rmq(int a[maxn][maxn]){
    int i,j,k,l;
    int lx,ly;
    for(i=0,lx=1;lx<=m;i++,lx<<=1){
        for(j=0,ly=1;ly<=n;j++,ly<<=1){
            for(k=0;k<=m-lx;k++)
                for(l=0;l<=n-ly;l++){
                    if(i==0){
                        if(j==0)rmq[0][0][k][l]=a[k][l];
                        else rmq[0][j][k][l]=min(rmq[0][j-1][k][l],rmq[0][j-1][k][l+(ly>>1)]);
                    }else if(j==0){
                        rmq[i][0][k][l]=min(rmq[i-1][0][k][l],rmq[i-1][0][k+(lx>>1)][l]);
                    }else
                    rmq[i][j][k][l]=min(
                            min(rmq[i-1][j-1][k][l],
                                rmq[i-1][j-1][k+(lx>>1)][l+(ly>>1)]),
                            min(rmq[i-1][j-1][k+(lx>>1)][l],
                                rmq[i-1][j-1][k][l+(ly>>1)]));
                }
        }
    }
}

int RMQ(int x1,int y1,int x2,int y2){
    int lx=lg[x2-x1+1],ly=lg[y2-y1+1];
    int dx=1<<lx,dy=1<<ly;
    return min(
            min(rmq[lx][ly][x1][y1],
                rmq[lx][ly][x2-dx+1][y2-dy+1]),
            min(rmq[lx][ly][x2-dx+1][y1],
                rmq[lx][ly][x1][y2-dy+1]));
}

