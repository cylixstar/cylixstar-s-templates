/**
 * Toolkits to constuct regexpr
 * into NFA and then into DFA
 *
 * The nodes of NFA should be less than 64
 *
 * Use functions as
 * addstar,addor,concat,singlechr
 * to handle symbols like *,|,concat and 
 * single char
 *
 * cntDFA should be init outside
 * use cntDFA without reset can make 
 * multiply DFA exist in the same array
 * by cylixstar @ 2011-1-25
 */

typedef long long ll;
const int maxch = 2;
struct NFANode{
    int son[maxch];
    vector<int> ep;
};
struct NFA{
    int S,E;
};
struct DFANode{
    int son[maxch];
    bool end;
};


const int maxnode = 200;
NFANode nfa_node[maxnode];
DFANode dfa_node[maxnode];

map<ll,int> nodeMap;

int cntNFA,cntDFA;
int newNode(){
    nfa_node[cntNFA].son[0] = nfa_node[cntNFA].son[1] = -1;
    nfa_node[cntNFA].ep.clear();        
    return cntNFA++;
}


inline void addep(int S,int T){
    nfa_node[S].ep.push_back(T);
}

NFA addstar(NFA A){
    NFA ans;
    ans.S = newNode();
    ans.E = newNode();    
    addep(ans.S,A.S);
    addep(ans.S,ans.E);
    addep(ans.E,ans.S);
    addep(A.E,ans.E);
    return ans;
}

NFA concat(NFA A,NFA B){
    NFA ans;
    ans.S = A.S;
    ans.E = B.E;
    addep(A.E,B.S);
    return ans;
}

NFA addor(NFA A,NFA B){
    NFA ans;
    ans.S = newNode();
    ans.E = newNode();
    addep(ans.S,A.S);
    addep(ans.S,B.S);
    addep(B.E,ans.E);
    addep(A.E,ans.E);
    return ans;
}

NFA singlechr(int ch){
    NFA ans;
    ans.S = newNode();
    ans.E = newNode();
    nfa_node[ans.S].son[ch] = ans.E;
    return ans;
}


int newDFANode(ll s,int E){
    for(int i=0;i<maxch;i++)
        dfa_node[cntDFA].son[i] = -1;
    dfa_node[cntDFA].end = (s & (1LL<<E))>0;
    return cntDFA++;
}

ll next(ll v){
    ll ans = 0;
    static int que[maxnode];
    static bool vis[maxnode];
    fill(vis,vis + cntNFA,false);
    int head = 0 ,tail = 0;
    for(int i=0;v;i++,v>>=1)if(v&1){
        que[tail++] = i;
        vis[i] = true;
    }
    for(;head<tail;head++){
        int top = que[head];
        for(int i=0;i<nfa_node[top].ep.size();i++){
            int T = nfa_node[top].ep[i];
            if(!vis[T]){
                que[tail++] = T;
                vis[T] = true;
            }
        }
    }
    while(tail--)
        ans |= 1LL<<que[tail];

    return ans;
}

void make_dfa(NFA nfa){
    nodeMap.clear();
    static ll que[maxnode];
    int head,tail;
    head = 0,tail = 1;
    que[0] = next(1LL<<nfa.S);
    nodeMap.insert(make_pair(que[0],cntDFA));
    newDFANode(que[0],nfa.E);

    for(;head<tail;head++){
        ll top = que[head],ns;
        int S = nodeMap[top];
        for(int i=0;i<maxch;i++){
            ns = 0;
            dfa_node[S].son[i] = -1;
            top = que[head];
            for(int j=0;j<cntNFA && top;j++,top>>=1)
                if(top&1LL)
                    if(nfa_node[j].son[i]!=-1)
                        ns |= (1LL<<nfa_node[j].son[i]);
            ns = next(ns);
            if(ns>0){
                map<ll,int>::iterator it = nodeMap.find(ns);
                if(it!=nodeMap.end()){
                    dfa_node[S].son[i] = it->second;
                }else{
                    int nT = newDFANode(ns,nfa.E);
                    dfa_node[S].son[i] = nT;
                    nodeMap.insert(make_pair(ns,nT));
                    que[tail++] = ns;
                }
            }
        }
    }
}

