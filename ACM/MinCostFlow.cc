/********
 *
 * ZKW Minimum Cost Flow
 * Notice the network should not
 * have a cost neg circle at the 
 * beginning
 * Edited by cylixstar
 */
namespace MinCostFlow {

	const int MAXN = 200;
	const int MAXM = 4000;
	typedef int flow_t;
	const flow_t INF = 0x7fffffff;

	struct Arc{
		flow_t remain;
		flow_t cost;
		int dest;
		Arc* next;
	};

	struct Network {
		int cntNode;
		int source,sink;
		Arc* hd[MAXN];
		Arc lnk[MAXM + MAXM];	
		Arc* ep;
		bool vis[MAXN];
		flow_t pi,totCost;
		flow_t dis[MAXN];

		void init(int cnt,int s,int t)
		{
			cntNode = cnt;
			source = s;
			sink = t;
			for(int i = 0;i<cntNode;i++) {
				hd[i] = NULL;
			}
			ep = lnk;
		}

		Arc* back(Arc* p) {
			return lnk + ((p - lnk) ^ 1);
		}

		void add_edge(int u,int v,flow_t cap,flow_t cost) {
			ep->dest = v;
			ep->remain = cap;
			ep->cost = cost;
			ep->next = hd[u];
			hd[u] = ep++;

			ep->dest = u;
			ep->remain = 0;
			ep->cost = -cost;
			ep->next = hd[v];
			hd[v] = ep++;
		}
		flow_t augment(int v,flow_t f) {
			if(v==sink)return totCost += pi * f,f;
			vis[v] = true;
			flow_t nextf,remain = f,d;
			for(Arc* e = hd[v];e;e = e->next) {
				if(!vis[e->dest] && !e->cost && e->remain) {
					d = augment(e->dest,remain < e->remain ?  remain : e->remain);
					e->remain -= d;back(e)->remain += d;
					remain -= d;
					if(!remain)return f;
				}
			}
			return f - remain;
		}

		bool modlab() {
			flow_t dt;
			int top;
			Arc *e,*b;
			deque<int> Q;
			Q.push_back(sink);
			for(int i = 0;i<cntNode;i++) {
				dis[i] = INF;
			}
			dis[sink] = 0;
			while(!Q.empty()) {
				top = Q.front();Q.pop_front();
				for(e = hd[top];e;e = e->next) {
					b = back(e);
					if(b->remain && 
						(dt = dis[top] - e->cost) < dis[e->dest]) {
						(dis[e->dest] = dt) < dis[Q.empty() ? 0 : Q.front()] 
							? Q.push_front(e->dest) : Q.push_back(e->dest);
					}
				}
			}

			for(int i = 0;i<cntNode;i++) {
				for(e = hd[i];e;e = e->next) {
					e->cost += dis[e->dest] - dis[i];
				}
			}
			pi += dis[source];
			return dis[source] < INF;
		}

		flow_t min_cost_flow() {
			pi = totCost = 0;
			while(modlab()) {
				do {
					memset(vis,0,sizeof(vis));
				}while(augment(source,INF));
			}
			return totCost;
		}

	};
	
};

