/***************
* Light Reflection
* by cylixstar @ 2010-11-13
***************/ 

/*
    assuming that the ray has touch the plane
    through p1 and p2
    and no total reflection
    get a new direction after the ray goes through
    the plane

    K means the reflection index of the incident part
    divides the reflection index of the outgoing part
*/
void reflect(point& dir,point p1,point p2,double K){
	double c1,s1,c2,s2,cd,sd;
	double L = sqrt(dpr(dir,dir)) * sqrt(dpr(p2 - p1,p2 - p1));
	c1 = dpr(p2 - p1, dir) / L;
	s1 = ccw(p2 - p1, dir) / L;
	c2 = K * c1;
	s2 = sqrt(1.0 - c2 * c2);
	if(s1 < -eps)s2 = -s2;
	cd = c1 * c2 + s1 * s2;
	sd = c1 * s2 - c2 * s1;
	dir = point(dir.x * cd - dir.y * sd,dir.x * sd + dir.y * cd);	
}

