/**
 * Shirnk the graph by cut vertex in directed graph
 *
 * by lch
 */

/*F means dfn
P means the id of connected components
reset F and P to -1

reset cnt0 and cnt1 into 0
reset top and p into 0 before each component
*/
void dfs(int u){
	F[u] = cnt0++;
	s[top++] = u;
	path[p++] = u;
	for(int j = h[u];j!=-1;j = es[j][1]){
		int v = es[j][0];
		if(F[v]==-1)dfs(v);
		else if(P[v]==-1)while(F[path[p - 1]]>F[v])--p;
	}
	if(path[p - 1]!=u)return;
	--p;
	do P[s[--top]] = cnt1;while(s[top]!=u);
	++cnt1;
}

