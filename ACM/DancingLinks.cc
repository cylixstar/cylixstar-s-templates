#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

struct DancingLinks
{
	int numRow,numCol;
	DancingLinks(int numRow,int numCol):
		numRow(numRow),numCol(numCol),
		colCnt(numCol,0)
		{}
	vector<pair<int,int> >nodes;
	vector<int>rowHead,colHead;
	vector<int>left,right,up,down;
	vector<int>colCnt;
	vector<int>solution;
	vector<bool> covered;
	int totNode,base,baseCol,baseRow;

	void addNode(int row,int col)
	{
		nodes.push_back(make_pair(row,col));
	}

	void makeLinks()
	{
		baseRow = nodes.size();
		baseCol = baseRow + numRow;
		totNode = baseCol + numCol;

		left.assign(totNode + 1,-1);
		right.assign(totNode + 1,-1);
		up.assign(totNode + 1,-1);
		down.assign(totNode + 1,-1);
		
		//For heuristic functino
		covered.assign(numCol,false);

		int row,col;
		int head,tail;

		sort(nodes.begin(),nodes.end());
		for(int i = 0;i < numRow;i++){
			if(i < numRow - 1) {
				down[baseRow + i] = baseRow + i + 1;
				up[baseRow + i + 1] = baseRow + i;
			}
			left[baseRow + i] = right[baseRow + i] = baseRow + i;
		}
		up[baseRow] = baseRow + numRow - 1;
		down[baseRow + numRow - 1] = baseRow;

		for(int i = 0;i < numCol;i++){
			if(i < numCol - 1) {
				right[baseCol + i] = baseCol + i + 1;
				left[baseCol + i + 1] = baseCol + i;
			}
			up[baseCol + i] = down[baseCol + i] = baseCol + i;
		}
		left[baseCol] = totNode;
		right[baseCol + numCol - 1] = totNode;

		left[totNode] = baseCol + numCol - 1;
		right[totNode] = baseCol;

		for(int i = 0 ; i < nodes.size();i++)
		{
			row = nodes[i].first;
			col = nodes[i].second;
			colCnt[col]++;

			head = baseRow + row;
			tail = left[head];

			right[tail] = i;
			left[i] = tail;
			right[i] = head;
			left[head] = i;

			head = baseCol + col;
			tail = up[head];

			down[tail]  = i;
			up[i] = tail;
			down[i] = head;
			up[head] = i;
		}
	}
	//Heuristic function
	//A lower bound of least remain rows
	//need to select
	int H() {
		int ret = 0;
		static int curNode,iterNode,enumNode,col;
		for(int i = 0;i<numCol;i++) {
			covered[i] = false;
		}
		for(curNode = right[totNode];curNode != totNode;curNode = right[curNode]) {
			col = curNode - baseCol;
			if(!covered[col]) {
				ret++;
				covered[col] = true;
				for(iterNode = down[curNode]; iterNode != curNode; iterNode = down[iterNode]) {
					for(enumNode = right[iterNode]; enumNode != iterNode; enumNode = right[enumNode]) {
						if(enumNode >= baseRow) continue;
						covered[nodes[enumNode].second] = true;
					}
				}
			}
		}
		return ret;
	}

	//if you want to remove a column  which x node is on
	//remember to invoke by removeColumn(nodes[x].second + baseCol)
	void removeColumn(int colNode)
	{
		static int iterNode,curNode;
		for(curNode = down[colNode];
				curNode!=colNode;
				curNode = down[curNode]) {
			if(curNode < baseCol) {
				for(iterNode = right[curNode];iterNode!=curNode;iterNode = right[iterNode]) {
					if(iterNode >= baseRow) continue;
					down[up[iterNode]] = down[iterNode];
					up[down[iterNode]] = up[iterNode];
					colCnt[nodes[iterNode].second]--;
				}
			} else {
				left[right[curNode]] = left[curNode];
				right[left[curNode]] = right[curNode];
			}
		}
	}
	
	void restoreColumn(int colNode)
	{
		static int iterNode,curNode;
		for(curNode = up[colNode];
				curNode!=colNode;
				curNode = up[curNode]) {
			if(curNode < baseCol) {
				for(iterNode = right[curNode];iterNode!=curNode;iterNode = right[iterNode]) {
					if(iterNode >= baseRow) continue;
					down[up[iterNode]] = iterNode;
					up[down[iterNode]] = iterNode;
					colCnt[nodes[iterNode].second]++;
				}
			} else {
				left[right[curNode]] = curNode;
				right[left[curNode]] = curNode;
			}
		}
	}

	void removeColumnRep(int colNode) {
        static int curNode;
        for(curNode = down[colNode];curNode!=colNode;curNode = down[curNode]) {
            right[left[curNode]] = right[curNode];
            left[right[curNode]] = left[curNode];
        }
	}

    void restoreColumnRep(int colNode)
    {
        static int curNode;
        for(curNode = up[colNode];curNode!=colNode;curNode = up[curNode]) {
            right[left[curNode]] = curNode;
            left[right[curNode]] = curNode;
        }
    }

	void search()
	{
		if(right[totNode]==totNode)
		{
			//handle solution
			/*for(int i = 0;i<solution.size();i++)
				printf("%d ",solution[i]);
			puts("");*/
			return;
		}
		int minNode = -1,minCnt = 0,curNode;
		int iterNode;
		for(curNode = right[totNode];
				curNode!=totNode;
				curNode = right[curNode])
		{
			if(minNode < 0 || (minCnt > colCnt[curNode - baseCol]))
			{
				minNode = curNode;
				minCnt = colCnt[curNode - baseCol];
			}
		}
		if(minCnt==0)return;

		
		for(curNode = down[minNode];
				curNode!=minNode;
				curNode = down[curNode])
		{
			removeColumn(curNode);
			//removeColumnRep(curNode);
			for(iterNode = right[curNode];iterNode != curNode;iterNode = right[iterNode]) {
				if(iterNode < baseRow) {
					removeColumn(iterNode);
				}
				//Replace code in this block if you want to 
				//solve rep cover problem
				/* 
				if(iterNode >= baseRow)continue;
				removeColumnRep(iterNode);
                up[down[iterNode]] = up[iterNode];
                down[up[iterNode]] = down[iterNode];
                colCnt[nodes[iterNode].second]--;*/
			}
			solution.push_back(nodes[curNode].first);
			//Put some branches-cut code here
			search();
			solution.pop_back();
			for(iterNode = left[curNode];iterNode != curNode;iterNode = left[iterNode]) {
				if(iterNode < baseRow) {
					restoreColumn(iterNode);
				}	
				//Replace code in this block if you want to 
				//solve rep cover problem
				/*if(iterNode >= baseRow)continue;
                up[down[iterNode]] = iterNode;
                down[up[iterNode]] = iterNode;
                restoreColumnRep(iterNode);
                colCnt[nodes[iterNode].second]++;*/
			}
			restoreColumn(curNode);
			//restoreColumnRep(curNode);
		}
	}
};


void printrow(const DancingLinks& dlx,int start)
{
	int curNode = dlx.right[start];
	printf("Row %d ",start);
	for(;curNode!=start;curNode = dlx.right[curNode])
	{
		printf("%d ",curNode);
	}
	puts("");
}

void printcol(const DancingLinks& dlx,int start)
{
	int curNode = dlx.down[start];
	printf("Col %d ",start);
	for(;curNode!=start;curNode = dlx.down[curNode])
	{
		printf("%d ",curNode);
	}
	puts("");
}

int main()
{
	int numNode,x,y;
	int numRow,numCol;
	scanf("%d%d%d",&numRow,&numCol,&numNode);
	printf("%d %d\n",numRow,numCol);
	DancingLinks dlx(numRow,numCol);
	for(int i = 0;i<numNode;i++)
	{
		scanf("%d%d",&x,&y);
		dlx.addNode(x,y);
	}
	dlx.makeLinks();
	printrow(dlx,dlx.totNode);
	for(int i = 0;i<numRow;i++)
	{
		printrow(dlx,dlx.baseRow + i);
	}
	for(int i = 0;i<numCol;i++)
	{
		printcol(dlx,dlx.baseCol + i);
	}
	dlx.search();
	return 0;
}
