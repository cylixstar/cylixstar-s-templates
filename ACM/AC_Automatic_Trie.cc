/********************
* AC - Automatic with trie
* by cylixstar @ 2010-11-6
*
**********************/



//Attention that if char may be negative
//and you should turn it into unsigned char or int
const int maxnode = 10000;
const int alpha = 256;
struct triNode{
	int pf;
	int son[alpha];
};
struct trieTree{
	triNode node[maxnode];
	int que[maxnode];
	int cntNode;
	trieTree(){
		reset();
	}
	int newNode(){
		node[cntNode].pf = -1;
		fill(node[cntNode].son,node[cntNode].son + alpha,-1);
                //Put code here to initialize a new node
		return cntNode++;
	}
	void reset(){
		cntNode = 0;
		newNode();
	}
	void ins(const char* str,int len){
		int cur = 0,next;
		for(int i=0;i<len;i++){
			int key = str[i];
			if(node[cur].son[key]==-1){
				cur = node[cur].son[key] = newNode();
			}else cur = node[cur].son[key];
		}
                //Put some code here to handle the event of 
                //the ending of the string
                //For example: node[cur].fin=XXXX
	}

	void buildAC(){
		int head = 0,tail = 1;
		int next,last,pp;
		que[0] = 0;
		node[0].pf = 0;
		for(;head<tail;head++){
			int top = que[head];
			for(int i=0;i<alpha;i++){	
				if(node[top].son[i]==-1){
					if(top==0){
						node[top].son[i] = 0;
					}else{
						last = node[node[top].pf].son[i];
						node[top].son[i] = last;
					}
				}else{
					if(top==0)
						node[node[top].son[i]].pf = 0;
					else
						node[node[top].son[i]].pf = node[node[top].pf].son[i];
					que[tail++] = node[top].son[i];
				}
			}
		}
	}

	int nextState(int v,int key){
		return node[v].son[key];
	}

};

