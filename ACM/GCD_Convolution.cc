/**
 * GCD Convolution
 * C[i] = sum(A[x] * B[y],for (x,y) = i);
 **/
void mul(int n,int mod,const int A[],const int B[],int C[]){
    static int temp[maxn];
    int sa,sb,sum;
    for(int i = n;i>=1;i--) {
        sum=sa=sb=0;
        for (int j=i;j<=n;j+=i) {
            sa = (sa + A[j])%mod;
            sb = (sb + B[j])%mod;
            if(j > i) {
                sum = (sum + temp[j]) % mod;
            }
        }
        sum = ((long long)sa*sb - sum) % mod;
        if (sum < 0) sum += mod;
        temp[i] = sum;
    }
    for (int i = 1;i<=n;i++)C[i] = temp[i];
}

