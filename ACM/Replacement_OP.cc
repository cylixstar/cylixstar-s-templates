/*******
* Operations on Group of replacement
* by cylixstar @ 2010-10-10
********/
//permutation are 0-indexed
typedef vector<int> VI;
int gcd(int a,int b){
    int r;
    while(b){
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

void printpg(int n,const int A[]){
    vector<bool> f(n,false);
    for(int i=0;i<n;i++){
        if(!f[i]){
            printf("(");
            int j = i;
            do{
                f[j] = true;
                printf(" %d ",j);
                j = A[j];
            }while(!f[j]);
            printf(")");
        }
    }
}

//Multiplication
//A * B -> C
void mul(int n,const int A[],const int B[],int C[]){
    static VI temp;
    temp.reserve(n);
    for(int i=0;i<n;i++)
        temp.push_back(B[A[i]]);
    copy(temp.begin(),temp.end(),C);
}

//Power
//A ^ k -> B
void pw(int n,const int A[],int k,int B[]){
    static VI t1,t2,ans;
    static vector<bool> f;
    t1.reserve(n),t2.reserve(n),ans.assign(n,0);
    f.assign(n,false);
    int i,j,l,m,c,p;
    for(i=0;i<n;i++)
        if(!f[i]){
            t1.clear();
            j =i;
            do{
                f[j] = true;
                t1.push_back(j);                
                j = A[j];
            }while(!f[j]);
            l = t1.size();
            m = gcd(l,k);
            for(j=0;j<m;j++){
                c = j,p = l / m;
                t2.clear();
                while(p--){
                    t2.push_back(t1[c]);
                    c += k;
                    c %= l;
                }
                p = l / m - 1;
                ans[t2[p]] = t2[0];
                while(p--){
                    ans[t2[p]] = t2[p + 1];
                }
            }
        }
    copy(ans.begin(),ans.end(),B);
}

//inverse Power;
//A ^ (1/k) -> B
//There may be multiple solution.
//But just return one of them
//returns false if there is no solution.
bool invPw(int n,const int A[],int k,int B[]){
    static VI cir,pos,ans,idx,cnt;
    static vector<bool> f;
    f.assign(n,false);
    cir.reserve(n),pos.reserve(n + 1);
    cir.clear();pos.clear();
    ans.assign(n,0);
    cnt.assign(n + 1,0);
    int i,j,m,l,p,c,nc,L,s;
    for(i=0;i<n;i++)
    if(!f[i]){
        j = i;
        pos.push_back(cir.size());
        do{
            f[j] =true;
            cir.push_back(j);
            idx.push_back(0);
            j = A[j];
        }while(!f[j]);
    }
    nc = pos.size();
    pos.push_back(n);
    for(i=0;i<nc;i++)
        cnt[pos[i + 1] - pos[i]]++;
    partial_sum(cnt.begin(),cnt.begin() + n + 1,cnt.begin());
    for(i=nc - 1;i>=0;i--){
        idx[--cnt[pos[i + 1] - pos[i]]] = i;
    }

    
    for(i=0;i<nc;){
        p = idx[i];
        l = pos[p + 1] - pos[p];
        m = gcd(k,l);
        L = m * l;
        if(m + i > nc || pos[idx[i + m - 1] + 1] - pos[idx[i + m - 1]]!=l)return false;
        cnt.assign(L,0);
        for(j=0;j<m;j++,i++){
            c = j;
            s = l;
            p = pos[p];
            while(s--){
                cnt[c] = cir[p];
                c = (c + k) % L;
                p++;
            }
        }
        for(j=0;j<L-1;j++)
            ans[cnt[j]] = cnt[j + 1];
        ans[cnt[L - 1]] = cnt[0];
    }
    copy(ans.begin(),ans.end(),B);
    return true;
}

