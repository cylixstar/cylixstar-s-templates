/**
 * Solve equations set
 * by Gaussian Elemination
 *
 * @author cylixstar
 * @date 2011-10-10
 *
 *
 **/

namespace GaussianElemination {
	//Number of equations
	const int maxEqu = 110;
	//Number of variables
	const int maxVar = 110;
	double mat[maxEqu][maxVar + 1];
	double res[maxVar];
	
	void init() {
		memset(mat,0,sizeof(mat));
	}

	//return -1 means no solution
	//otherwise return the rank
	int solve(int numEqu,int numVar) {
		int cur,next,rank,pos;
		double k;
		cur = 0;
		for(int i = 0;i < numVar && cur < numEqu;i++) {
			k = mat[cur][i],pos = cur;
			//find the row with max fabs(mat[next][i])
			for(next = cur;next < numEqu;next++) {
				if(sgn(fabs(mat[next][i]) - k) > 0) {
					k = fabs(mat[next][i]);
					pos = next;
				}
			}
			if(!sgn(k)) continue;

			if(pos > cur)
			for(int j = 0;j<=numVar;j++) {
				swap(mat[cur][j],mat[pos][j]);
			}
			for(int next = 0;next < numEqu;++next) {
				if(next==cur)continue;
				k = mat[next][i] / mat[cur][i];
				if(sgn(k)) {
					for(int j = 0;j<=numVar;j++) {
						mat[next][j] -= mat[cur][j] * k;
					}
				}
			}
			cur++;
		}

		rank = cur;
		for(next = cur;next < numEqu;++next) {
			//no solution
			if(sgn(mat[next][numVar]))return -1;
		}

		if(rank < numVar) {
			//multi solution
			return rank;
		}

		for(int i = 0;i<numVar;i++)res[i] = 0.0;
		
		for(next = cur - 1,pos = numVar - 1;next>=0;next--) {
			while(!sgn(mat[next][pos]))
				pos--;
			res[pos] = mat[next][numVar] / mat[next][pos];
		}
		return rank;
	}

}
