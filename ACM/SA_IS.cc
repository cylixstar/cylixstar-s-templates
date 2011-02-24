/**
 *	Suffix Array (IS)
 *	by cylixstar @ 2010-10-10
 * */
//S-type 0
//L-type 1

template<class T>
void getBkt(int bkt[],T seq[],int len,int alpha,bool end)
{
    fill(bkt,bkt + alpha,0);
    int i,sum = 0;
    for(i=0;i<len;i++)bkt[seq[i]]++;
    for(i=0;i<alpha;i++)
    {
        sum += bkt[i];
        bkt[i]=end ? sum : sum - bkt[i];
    }
}

template<class T>
void induceL(T seq[],int len,bool type[],int SA[],int alpha,int bkt[])
{
    getBkt(bkt,seq,len,alpha,false);
    int i,j;
    for(i=0;i<len;i++)
    if(SA[i]>0)
    {
        j = SA[i] - 1;
        if(type[j])
            SA[bkt[seq[j]]++] = j;
    }
}

template<class T>
void induceS(T seq[],int len,bool type[],int SA[],int alpha,int bkt[])
{

    getBkt(bkt,seq,len,alpha,true);
    int i,j;
    for(i=len-1;i>=0;i--)
    if(SA[i]>0)
    {
        j = SA[i] - 1;
        if(!type[j])
            SA[--bkt[seq[j]]] = j;
    }
    
}

//pos suppose to be positive
inline bool isLMS(bool type[],int pos)
{
    return !type[pos] && type[pos-1];
}

/**
* seq should be ended with 0 which is the smallest character.
* the length should be include the last 0
**/
template<class T>
void SA_IS(T seq[],int len,int SA[],int alpha)
{
    int i,n1,k,pos,name,prev;
    bool *t = new bool[len];
    t[len - 1] = 0;
    t[len - 2] = 1;
    for(i = len - 3;i>=0;i--)
        t[i] = seq[i]>seq[i+1]||(seq[i]==seq[i+1] && t[i+1]);
    
    int  *bkt = new int[alpha];

    fill(SA,SA + len,-1);
    getBkt(bkt,seq,len,alpha,true);

    for(i = 1;i<len;i++)
    if(isLMS(t,i))SA[--bkt[seq[i]]] = i;

    induceL(seq,len,t,SA,alpha,bkt);
    induceS(seq,len,t,SA,alpha,bkt);

    delete []bkt;
    
    for(i = n1 = 0;i<len;i++)
    if(SA[i]>0 && isLMS(t,SA[i]))
        SA[n1++] = SA[i];
    
    fill(SA + n1,SA + len,-1);
    prev = -1;
    name = 0;
    for(i=0;i<n1;i++)
    {
        pos = SA[i];
        if(i == 0)
            name++;
        else
        for(k=0;;k++)
            if(seq[pos + k]!=seq[prev + k]
                || t[pos + k]!=t[prev + k])
            {
                name++;
                break;
            }
            else
            if(k>0 && isLMS(t,pos + k))break;
        prev = pos;
        pos = pos / 2;
        SA[n1 + pos] = name - 1;
    }
    
    
    for(i = k = len - 1;k>=len-n1;i--)
    if(SA[i]>=0)
        SA[k--] = SA[i];
    
    int *s1 = SA + len - n1;
    if(name < n1)
        SA_IS(s1,n1,SA,name);
    else
        for(i=0;i<n1;i++)SA[s1[i]] = i;

    bkt = new int[alpha];
    for(i = 1,k = 0;i<len;i++)
    if(isLMS(t,i))s1[k++] = i;

    for(i=0;i<n1;i++)SA[i] = s1[SA[i]];

    getBkt(bkt,seq,len,alpha,true);
    fill(SA + n1,SA + len,-1);
    for(i = n1 - 1;i>=0;i--){
        k = SA[i];SA[i] = -1;
        SA[--bkt[seq[k]]] = k;
    }
    induceL(seq,len,t,SA,alpha,bkt);
    induceS(seq,len,t,SA,alpha,bkt);

    delete []bkt;
    delete []t;
}

//rank was calculated by this function
template<class T>
void getlcp(T seq[],int len,int sa[],int rank[],int lcp[])
{
    int i,j,p;
    for(i=0;i<len;i++)
        rank[sa[i]] = i;
    //Get LCP
    for(i = j = 0;i<totlen;lcp[rank[i++]] = j)
    if(rank[i]<totlen-1)
        for(j?j--:0,p = sa[rank[i]+1];seq[i + j] == seq[p + j];j++);
}

