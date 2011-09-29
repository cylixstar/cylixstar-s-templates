/**
 *
 * Caculate how many 
 * integer points under triangle
 * 0<= y <= a * x / b and 0<=x<=n
 * inclusive means is the integer
 * points on the line y = a * x / b included
 *
 **/
ll gridp_under_tri(bool inclusive,ll n,int a,int b){
	int q = a / b;
	ll base = (((ll)q*n*(n + 1))>>1);
	if (a % b==0){
		return base + (inclusive ? n + 1 : 0);
	}
	
	ll nn = ((ll)a%b*n/b);
	return base + (1 + nn) * (1 + n) - gridp_under_tri(!inclusive,nn,b,a % b);
}

