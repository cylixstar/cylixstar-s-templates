/***
 * Get the longest palindrome from the string 
 * by cylixstar @ 2011/1/19
***/

/**
 * P should be ended with 0 or some sort
 * there are n + 1 axis
 * so pal should be of size n + 1
 * the max length on axis i should be len 2 * pal[i]
 * axis i is before i-th character
 */
void getPalEven(const char* P,int pal[]){
	int L,R,PR,i;
	pal[0] = 0;
	R = 0,PR = 0;
	for(i = 1;P[i];i++){
		L = (PR<<1) - i;
		if(L<0)L = 0;
		else L = pal[L];
		if(PR + R<= i + L){
			for(L = max(PR + R  - i,0);i > L;L++)
				if(P[i + L]!=P[i - L - 1])break;
			PR = i;
			R = L;
		}
		pal[i] = L;
	}
	pal[i] = 0;

}

/**
 * P should be ended with 0 or some sort
 * there are n axis
 * pal should be of size n
 * axis i is at i-th character
 * the max length at axis i is 2 * pal[i] + 1
 */
void getPalOdd(const char* P,int pal[]){
	int L,R,PR,i;
	pal[0] = 0;
	R = 0,PR = 0;
	for(int i = 1;P[i];i++){
		L = (PR<<1) - i;
		if(L<0)L = 0;
		else L = pal[L];
		if(PR + R <= i + L){
			for(L = max(PR + R - i,0);i > L;L++)
				if(P[i - L - 1]!=P[i + L + 1])break;
			PR = i;
			R = L;
		}
		pal[i] = L;
	}
}

