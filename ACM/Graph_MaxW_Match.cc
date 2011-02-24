/**************
* Weighted Graph Maximal Match
* author: cylixstar
* date: 2010-10-20
*
***************/

//Notice that the N may be changed by the algorithm
//Adjust the MAXTRY to be more accurate
const int MAXN = 101;
const int MAXTRY = 10;
int graph[MAXN][MAXN];
int N;
int M[MAXN];

bool vis[MAXN];
int dist[MAXN],ord[MAXN],pred[MAXN];

int spfa(int u){
    vis[u]=true;
    int i;
    for(i=0;i<N;i++){
        int v = ord[i];
        if(dist[M[v]]>dist[u] + graph[v][M[v]] - graph[u][v]){
            if(vis[v])continue;
            dist[M[v]] = dist[u] + graph[v][M[v]] - graph[u][v];
            pred[M[v]]=u;
            if(vis[M[v]])return M[v];
            int ret = spfa(M[v]);
            if(ret!=-1)return ret;
        }
    }
    vis[u] =  false;
    return -1;
}

int negcir(){
    for(int i=0;i<N;i++){
        fill(vis, vis+N,false);
        fill(dist,dist+N,0);
        int ret = spfa(ord[i]);
        if(ret!=-1){
            return ret;
        }
    }
    return -1;
}

int augment(int x){
    if(M[M[x]]!=x)return 0;
    int m=M[x];
    int ans = graph[pred[x]][m] - graph[m][x];
    M[m] = pred[x];
    ans += augment(pred[x]);
    M[pred[x]] = m;
    return ans;
}

void shuffle(){
    int i,j;
    for(i=2;i<N;i++)
        swap(ord[i],ord[rand()%i]);
}

int weightedMatch(){
    int i,j,ans=0;
    if(N&1){
        for(i=0;i<N;i++){
            graph[i][N]=graph[N][i]=0;
        }
        N++;
    }
    fill(vis,vis+N,false);
    for(i=0;i<N;i++){
        M[i]=i^1;
        if(i&1) ans += graph[i][i^1];
        ord[i] = i;
    }
    while(true){
        int tt = MAXTRY;
        while(tt--){
            shuffle();
            int ret = negcir();
            if(ret!=-1){
                ans += augment(ret);
                break;
            }
        }
        if(tt<0)break;
    }
    return ans;
}

