/**
 * @author cylixstar
 * 
 * Dancing Links
 *
 * Special thanks to kelvinlau
 *
 * @date 2011-10-07
 *
 **/

namespace DancingLinks {
	const int maxNode = 80000;
	const int maxRow = 9 * 9 * 9;
	const int maxCol = 9 * 9 * 9;
	struct DanceNode{
		int x,y;
		DanceNode *l,*r,*u,*d;
	};

	DanceNode nodes[maxNode];
	DanceNode *row[maxRow],*col[maxCol];
	DanceNode *root,*curAva;
	int cnt[maxCol];
	//Just for heuristic function
	//for repetition cover
	bool covered[maxCol];

	void init(int numRow,int numCol) {
		memset(row,0,sizeof(row));

		curAva = nodes;
		root = curAva++;
		root->l = root->r = root;
		DanceNode* p;
		for(int i = 0;i<numCol;i++) {
			cnt[i] = 0;
			col[i] = p = curAva++;
			p->x = -1,p->y = i;
			p->u = p->d = p;
			p->r = root;
			p->l = root->l;
			p->l->r = p->r->l = p;

			//Just for heuristic function
			//for repetition cover
			covered[i] = false;
		}
	}

	//Heuristic function
	//A lower bound of least remain rows
	//need to select
	int H() {
		int ret = 0;
		static DanceNode *cur,*p,*q;
		for(cur = root->r;cur!=root;cur=cur->r) {
			if(!covered[cur->y]) {
				ret++;
				covered[cur->y];
				for(p = cur->d;p!=cur;p=p->d) {
					for(q = p->r;q!=p;q=q->r) {
						covered[q->y] = true;
					}
				}
			}
		}
		for(cur = root->r;cur!=root;cur=cur->r) {
			covered[cur->y] = false;
		}
		return ret;
	}
	
	void add(int x,int y) {
		DanceNode *p = curAva++;
		p->x = x,p->y = y;
		cnt[y]++;

		if(!row[x]) {
			row[x] = p->l = p->r = p;
		} else {
			p->l = row[x]->l;
			p->r = row[x];
			p->l->r = p->r->l = p;
		}

		p->u = col[y]->u;
		p->d = col[y];
		p->u->d = p->d->u = p;
	}
	
	void del_col_rep(DanceNode* p) {
		for(DanceNode* q = p->d;q!=p;q=q->d) {
			q->l->r = q->r;
			q->r->l = q->l;
		}
	}
	void undel_col_rep(DanceNode* p) {
		for(DanceNode* q = p->u;q!=p;q = q->u) {
			q->l->r = q->r->l = q;
		}
	}

	void del_col(int y) {
		DanceNode *p = col[y];
		p->l->r = p->r;
		p->r->l = p->l;
		for(DanceNode* a = p->d;a!=p;a = a->d) {
			for(DanceNode* b = a->r;b!=a;b = b->r) {
				b->u->d = b->d;
				b->d->u = b->u;
				cnt[b->y]--;
			}
		}
	}

	void undel_col(int y) {
		DanceNode *p = col[y];
		p->l->r = p->r->l = p;

		for(DanceNode* a = p->u;a!=p;a = a->u) {
			for(DanceNode* b = a->l;b!=a;b = b->l) {
				b->u->d = b->d->u = b;
				cnt[b->y]++;
			}
		}
	}
	
	//When dealing with repetition cover
	//remove *_col function 
	//then put on *_col_rep function
	void search() {
		if(root->r==root) {
			//handle a solution;
			return;
		}

		//Add a branch cut such as
		//if(H() + dep > maxstep) then return

		DanceNode *p,*q,*y = root->r;
		for(p = y->r;p!=root;p = p->r)
			if(cnt[p->y] < cnt[y->y]) y = p;
		
		if(!cnt[y->y])return;
		

		del_col(y->y);
		for(p = y->d;p!=y;p = p->d) {
			//del_col_rep(p);
			for(q = p->r;q!=p;q = q->r) {
				del_col(q->y);
				//del_col_rep(q);
			}
			
			//put p->x in solution
			search();
			//pop p->x out of solution

			for(q = p->l;q!=p;q = q->l) {
				undel_col(q->y);
				//undel_col_rep(q);
			}
			//undel_col_rep(p);
		}
		undel_col(y->y);
	}
};

