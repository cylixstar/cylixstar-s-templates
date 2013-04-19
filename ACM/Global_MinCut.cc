/***
* Global Minimum Cut
* 2010-12-19 by cylixstar
***/
const int maxn = 500 + 10;
int graph[maxn][maxn];
int ava[maxn];
const int inf = 1000000000;

/**
* find one s-t cut
* returns the weight
*/
int getMinCut(int n){
	static int d[maxn];
	static bitset<maxn> used;
	int best,bestj,last,cur;
	used.reset();
	fill(d,d + n,0);
	last = 0,cur = -1;
	used.set(0);
	for(int i=1;i<n;i++)
		d[i] = graph[ava[0]][ava[i]];

	for(int i=0;i<n-1;i++){
		best = -1,bestj = -1;
		for(int j=0;j<n;j++){
			if(used[j])continue;
			if(d[j]>best){
				best = d[j];
				bestj = j;
			}
		}
		used.set(bestj);
		last = cur,cur = bestj;
		for(int j=0;j<n;j++)
			if(!used[j]){
				d[j] += graph[ava[bestj]][ava[j]];
			}
	}
	int ans = 0;
	for(int i=0;i<n;i++){
		ans += graph[ava[i]][ava[cur]];
		if(i==last)continue;
		graph[ava[last]][ava[i]] += graph[ava[cur]][ava[i]];
		graph[ava[i]][ava[last]] += graph[ava[i]][ava[cur]];
	}
	swap(ava[n - 1],ava[cur]);
	return ans;
}
int globalMinCut(int n){
	for(int i=0;i<n;i++)ava[i] = i;
	int ans = inf;
	for(int i=0;i<n - 1;i++){
		ans = min(ans,getMinCut(n - i));
	}
	return ans;
}

