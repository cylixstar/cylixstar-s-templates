/*
 * Minimal Representation of String
 *
 * Remember to double the string first!
 * by cylixstar @ 2010-10-10
 */
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxlen=10000+10;
char s[maxlen+maxlen];

int minPresent(int len,char *str)
{
    int p1=0,p2=1,k;
    for(k=0;k<len;k++)
        str[k+len]=str[k];

    k=0;
    for(;k<len;)
    if(str[p1+k]==str[p2+k])k++;
    else
    {
        if(str[p1+k]>str[p2+k])
        {
            p1=p1+k+1;
            if(p1==p2)p1++;
        }
        else
        {
            p2=p2+k+1;
            if(p2==p1)p2++;
        }
        k=0;
        if(p1>=len)return p2;
        if(p2>=len)return p1;
    }
    return min(p1,p2);
}


