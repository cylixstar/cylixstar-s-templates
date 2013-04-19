#include <cstring>
#include <cstdio>
#include <iostream>
using namespace std;

/**
 *
 * @author cylixstar
 * @date 2011-10-04
 *
 * Input is the edge list.
 *
 * Just call make path
 * to construct the
 * tree and then decomposition
 * the tree in paths.
 *
 *
 **/

typedef long long ll;
const int maxnode = 50000 + 10;

bool heavy[maxnode];
int sz[maxnode],fa[maxnode];
//The paths all put in a line
int line[maxnode],idxLine;
//pathTail[i] the vertex most near to root of the
//path contains node i
//pathPos[i] the pos of node i in the line
int pathTail[maxnode],pathPos[maxnode];
//Edge list,remember to set hd to -1
int lnk[maxnode + maxnode][2],nlnk,hd[maxnode];
int dep[maxnode];
int totNode;


void add_edge(int a,int b) {
    lnk[nlnk][0] = b;
    lnk[nlnk][1] = hd[a];
    hd[a] = nlnk++;
}

void updatePath(int v,int lca,int delta) {
    while(true) {
        if(pathTail[v]!=pathTail[lca]){
			//update v-->tail[v]
			v = fa[pathTail[v]];
        } else {
			//update v-->lca;
            break;
        }
    }
}


int getlca(int v1,int v2) {
	int n1,n2;
	while(pathTail[v1]!=pathTail[v2]) {
		if(v1==0 | v2==0)return 0;
		n1 = heavy[v1] ? pathTail[v1] : fa[v1];
		n2 = heavy[v2] ? pathTail[v2] : fa[v2];
		if(dep[n1] >= dep[n2]) {
			v1 = n1;
		} else {
			v2 = n2;
		}
	}
	return dep[v1] < dep[v2] ? v1 : v2;
}

/*void modify(int v1,int v2,int delta) {
	int lca = getlca(v1,v2);
    updatePath(v1,lca,delta);
    updatePath(v2,lca,delta);
	//attention!!
    updatePath(lca,lca,-delta);
}*/

int que[maxnode];
bool used[maxnode];
void makePath() {
    memset(fa,-1,sizeof(fa));
    fa[0] = 0;
    que[0] = 0;
    int head,tail;
    head = 0,tail = 1;
    dep[0] = 0;
    for(;head<tail;head++) {
        int top = que[head],next;
        for(int j = hd[top];j!=-1;j = lnk[j][1]) {
            next = lnk[j][0];
            if(next==0 || fa[next]>=0)continue;
            fa[next] = top;
            dep[next] = dep[top] + 1;
			que[tail++] = next;
        }
    }
    for(int i =0 ;i<totNode;i++) {
        heavy[i] = used[i] = false;
    }

    for(int i = totNode - 1;i>=0;i--) {
        int v = que[i];
        sz[v] = 1;
        int next;
        int maxidx = -1,maxsz = 0;
        for(int j = hd[v];j!=-1;j = lnk[j][1]) {
            next = lnk[j][0];
            if(fa[next]!=v)continue;
            sz[v] += sz[next];
            if(sz[next] > maxsz) {
                maxidx = next;
                maxsz = sz[next];
            }
        }
        if(maxidx>=0) {
            heavy[maxidx] = true;
        }
    }

	int start;
	idxLine = 0;
    for(int i = totNode - 1;i>=0;i--) {
        int v = que[i];
        if(!used[v]) {
            tail = v;
			start = idxLine;
			while(true) {
				used[tail] = true;
				pathPos[tail] = idxLine;
				line[idxLine++] = tail;
				if(!heavy[tail])break;
				tail = fa[tail];
			}
			for(int j = start;j < idxLine; j++) {
				pathTail[line[j]] = tail;
			}
        }
    }
}



