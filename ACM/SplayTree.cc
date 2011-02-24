/******
* SplayTree Templates by Cylixstar
* @2011-2-24
* Multiply SplayTree can use a common memory
* All SplayTree should be init with a SplayMem
* maxsz in Splaymem means the maximal number of nodes
********/
template<class T>
struct SplayNode{
	T dat;
	//0-left 1-right
	//s==son fa==father
	SplayNode<T> *s[2],*fa;
};

template<class T>
struct SplayMem{
	const static int maxsz=100000;
	//Zero is reserved for null
	SplayNode<T> nod[maxsz+1];
	SplayNode<T>* nil;
	
	int ava[maxsz+1];
	int top;
	SplayMem():nil(nod){
		clear();
	}
	void clear(){
		for(int i=1;i<=maxsz;i++)
			ava[i]=i;
		top=maxsz - 1;
	}
	SplayNode<T>* newNode(const T& dat){
		int x = ava[top--];
		nod[x].dat=dat;
		nod[x].s[0]=nod[x].s[1]=nil;
		return nod + x;
	}
	void delNode(SplayNode<T>* x){
		if(x==nil)return;
		ava[++top] = x - nod;
	}
};


template<class T,class Comp = less<T> >
class SplayTree{
public:
	typedef SplayNode<T>* SP;
	SP& nil;
private:
	SplayMem<T>& nod;
	SP root;


	SP newNode(const T& dat){
		return nod.newNode(dat);
	}

	void delNode(SP x){
		nod.delNode(x);
	}

	inline void con(SP& x,SP& y,int d){
		if(x==nil)return;
		x->s[d]=y;
		y->fa=x;
	}
	void rot(SP x,int d){
		if(x==root)return;
		SP y=x->fa,z=y->fa;
		con(z,x,z->s[0]==y?0:1);
		con(y,x->s[d^1],d);
		con(x,y,d^1);
		if(y==root){
			root=x;
			x->fa=nil;
		}
	}

public:

	SplayTree(SplayMem<T>& mem):nod(mem),nil(mem.nil){
		root = nil;
	}

	SP getRoot(){
		return root;
	}
	/*
	 * Rotate x up to root
	 */
	void splay(SP x){ splay(nil,x);}
	/*
	 * Rotate x up to below "below"
	 */
	void splay(SP below,SP x){
		if(root==nil)return;
		while(x->fa!=below){
			SP y = x->fa,z;
			if(y->s[0]==x){
				if(root==y)
					rot(x,0);
				else{
					z=y->fa;
					if(z->s[0]==y){
						rot(y,0);rot(x,0);
					}
					else {
						rot(x,0); rot(x,1);
					}
				}
			}else{
				if(root==y)
					rot(x,1);
				else{
					z=y->fa;
					if(z->s[1]==y){
						rot(y,1);rot(x,1);
					}
					else{
						rot(x,1);rot(x,0);
					}
				}
			}
		}
	}

	SP find(T dat){
		if(root==nil)return false;
		SP x = root;
		Comp lt;
		while(x!=nil){
			if(lt(dat,x->dat))
				x = x->s[0];
			else
			if(lt(x->dat,dat))
				x = x->s[1];
			else break;
		}
		if(x!=nil){
			splay(x);
			return x;
		}
		return nil;
	}

	SP insert(const T& dat){
		if(root==nil){
			root=newNode(dat);
			root->fa=nil;
			return root;
		}
		SP x = root,y = nil,z;
		Comp lt;
		while(x!=nil){
			y = x;
			if(lt(dat,x->dat))
				x = x->s[0];
			else
			if(lt(x->dat,dat))
				x = x->s[1];
			else break;
		}
		if(x!=nil){
			splay(x);
			return x;
		}
		z = newNode(dat);
		if(lt(dat,y->dat))
			con(y,z,0);
		else con(y,z,1);
		splay(z);
		return z;
	}
	
	//d=0 smaller
	//d=1 larger
	SP next(SP x,int d){
		x = x->s[d];
		if(x==nil)return nil;
		d^=1;
		while(x->s[d]!=nil)
			x = x->s[d];
		return x;
	}
	void del(SP x){
		SP y,f=x->fa,fy;

		if(x->s[0]==nil)
			y=x->s[1];
		else if(x->s[1]==nil)
			y=x->s[0];
		else {
			y=next(x,1);
			if(y!=nil){
				con(y,x->s[0],0);
				if(y!=x->s[1]){
					fy = y->fa;
					con(fy,y->s[1],fy->s[0]==y?0:1);
					con(y,x->s[1],1);
				}
			}
		}
		if(root==x){
			root=y;
			y->fa=nil;
		}
		else{
			con(f,y,f->s[0]==x?0:1);
			if(y!=nil)splay(y);
			else if(f!=nil)splay(f);
		}
		delNode(x);
	}

	void join(SplayTree<T>& S){
		if(root==nil){
			root=S.root;
			return;
		}
		SP x = root;
		while(x->s[1]!=0)
			x=x->s[1];
		splay(x);
		x->right=S.root;
	}
};

