/*************************
* The intersection point bewteen a ray and a segment
* by cylixstar @ 2010-11-13
************************/
/*
    the ray does not colinear with the segment

    org: the original point of the ray
    dir: the direction of the ray
    p1,p2: two end points of the segment
    res : returns the result
    returns if the intersection exists
*/
bool intersect_ray_seg(point org,point dir,point p1,point p2,point& res){
	if(fabs(ccw(dir,p2 - p1))<eps)return false;
	double k = ccw(p1 - org,p2 - p1) / ccw(dir,p2 - p1);
        //inverse the eps to allow the intersection being at the original point
	if(k < eps)return false;
	res = point(org.x + dir.x * k,org.y + dir.y * k);
	double L = dpr(res - p1,p2 - p1);
        //inverse the eps and -eps to allow the intersection being at the two end points
	if(L<eps || L - dpr(p2 - p1,p2 - p1) > -eps)return false;
	return true;
}

