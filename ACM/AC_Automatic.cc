/********************
* AC - Automatic
* by cylixstar @ 2010-11-6
*
**********************/
const int maxnode = 10000;
struct acNode{
	int key;
	int pf,son,bro;
};

struct acTree{
	acNode node[maxnode];
	int que[maxnode];
	int cntNode;
	acTree(){
		reset();
	}
	int newNode(){
		node[cntNode].pf = node[cntNode].son = node[cntNode].bro = -1;
                   //Put code here to initialize a new node
		return cntNode++;
	}
	void reset(){
		cntNode = 0;
		newNode();
	}
	int findson(int v,int key){
		if(node[v].son==-1)return -1;
		int next = node[v].son;
		while(node[next].key!=key){
			if(node[next].bro==-1)return -1;
			next = node[next].bro;
		}
		return next;
	}
	void ins(const char* str,int len){
		int cur = 0,next;
		for(int i=0;i<len;i++){
			int key = str[i];
			if(node[cur].son==-1){
				cur = node[cur].son = newNode();
				node[cur].key = key;
			}else{
				cur = node[cur].son;
				while(node[cur].key!=key){
					if(node[cur].bro==-1){
						next = newNode();
						node[next].key = key;
						node[cur].bro = next;
						cur = next;
						break;
					}else cur = node[cur].bro;
				}
			}
		}
                //Put some code here to handle the event of 
                //the ending of the string
                //For example: node[cur].fin=XXXX
                
	}

	void buildAC(){
		int head=0,tail = 1;
		int next,key,last,pp;
		que[0] = 0;
		node[0].pf = 0;
		for(;head<tail;head++){
			int top = que[head];
			if(node[top].son==-1)continue;
			next = node[top].son;
			while(true){
				key = node[next].key;
				last = node[top].pf;
				while(last!=0 && (pp=findson(last,key))==-1){
					last = node[last].pf;
				}
				if(last==0){
					pp = findson(0,key);
					if(pp==-1 || pp==next)pp=0;
				}
				node[next].pf = pp;
				que[tail++] = next;
				if(node[next].bro==-1)break;
				next = node[next].bro;
			}
		}
	}

	int nextState(int v,int key){
		int pp=-1;
		while(true){
			pp = findson(v,key);
			if(pp!=-1)break;
			if(v==0)break;
			v = node[v].pf;
		}
		if(pp<0)return 0;
		return pp;
	}
};

