/**
 * 快速求递推关系第n项:
 * F(n) = sum(F[n - i] * C[i])(1<=i<=L)
 * 可以推广到F[n]为矩阵的情况
 * 注意C数组的大小应该为最长L+1
 * O(L * L * lgL)
 * by cylxistar @ 2011-1-21
 *
 */
typedef long long ll;
const int mod = 100000007;
const int maxL = 750 + 1;

void convVec(int L,const int M[maxL][maxL],const int A[maxL],const int B[maxL],int C[maxL]){
	static int D[maxL + maxL];
	fill(D,D + L + L - 1,0);
	for(int i=0;i<L;i++)
		for(int j=0;j<L;j++)
			D[i + j] = (D[i + j] + (ll)A[i] * B[j]) % mod;
	for(int i=0;i<L;i++)
		C[i] = D[i];
	for(int i = 0;i<L - 1;i++)
		if(D[i + L])
		for(int j=0;j<L;j++)
			C[j] = (C[j] + (ll)D[i + L] * M[i][j]) % mod;
}

int fastRecursion(ll n,int L,int C[maxL]){
	static int high[maxL][maxL];
	static int X[maxL],Y[maxL];
	for(int i=1;i<=L;i++)
		high[0][L - i] = C[i];
	for(int i=1;i<L;i++){
		for(int j = L - 1;j>=1;j--)
			high[i][j] = high[i - 1][j - 1];
		high[i][0] = 0;
		if(high[i - 1][L - 1]){
			int tt = high[i - 1][L - 1];
			for(int j = 0;j<L;j++)
				high[i][j] = (high[i][j] + (ll)high[0][j] * tt)%mod;
		}
	}
	fill(X,X + L,0);
	fill(Y,Y + L,0);
	if(L==1)X[0] = C[1];
	else X[1] = 1;
	Y[0] = 1;
	
	for(;n;n>>=1LL,convVec(L,high,X,X,X))
		if(n&1LL)
			convVec(L,high,Y,X,Y);
	//如果需要自定义初值则把以下语句改为
	/*
	* int ans = 0;
	* for(int i=0;i<L;i++)
	* ans = (ans + (ll)A[i] * Y[i]))%mod
	* 其中A[i]为初值第i项
	*/
	X[0] = 1;
	int ans = Y[0];
	for(int i = 1;i<L;i++){
		X[i] = 0;
		for(int j = i;j>=1;j--)
			X[i] = (X[i] + (ll)X[i - j] * C[j]) % mod;
		ans = (ans + (ll)X[i] * Y[i]) % mod;
	}
	return ans;
}

