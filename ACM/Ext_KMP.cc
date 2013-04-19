/*************************
* author: cylixstar
* date 2010-10-20
* Extended KMP
*************************/

/*
 * A[i] = longest common prefix between s[0..n - 1] and s[i..n - 1]
 */
template<class T>
void calA(int n,const T s[],int A[]){
    A[0] = n;
    int i,j,k;
    for(j=1;s[j]==s[j - 1];j++);
    A[1] = j - 1,k = 1;
    for(i=2;i<n;i++){
        if(k + A[k] -i > A[i - k])
            A[i] = A[i - k];
        else{
            j = max(0,k + A[k] - i);
            while(s[j] == s[i + j])j++;
            A[i] = j,k = i;
        }
    }
}

/*
 * B[i] = longest common prefix between x[0..n - 1] and y[i..m - 1]
 * calculate A of x use calA first
 */
template<class T>
void calB(int n,const T x[],const int A[],
        int m,const T y[],int B[]){
    int i,j,k;
    for(j=0;j<n && j<m && x[j]==y[j];j++);
    B[0] = j,k = 0;
    for(i=1;i<m;i++){
        if(k + B[k] - i > A[i - k])
            B[i] = A[i - k];
        else{
            j = max(0, k + B[k] - i);
            while(x[j] == y[i + j])j++;
            B[i] = j,k = i;
        }
    }
    
}

