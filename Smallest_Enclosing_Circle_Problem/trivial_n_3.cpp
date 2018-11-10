#include <bits/stdc++.h>
#include <LEDA/geo/circle.h>
#include <LEDA/geo/point.h>
#include <LEDA/geo/segment.h>
using namespace std;
#define inf 1e18 
#define right_angle acos(0)
#define eps 1e-6

// correct the angle thing
int n;
vector<leda::point> P;
long double min_rad = inf;
vector<int> defining_points(3, 0);

bool outside(leda::circle C, leda::point P) {
	leda::point Q = C.center();
	long double r = C.radius(), d = (long double)(Q.distance(P));
	if((r + eps - d) > 0.0)
		return false;
	return true;
}

bool is_valid_circle(leda::circle C) {
	bool v = true;
	for(int i = 0;i < n;i++)
		if(outside(C, P[i])){
			v = false;
		}
	return v;
}

int just_less_than(int x, int y) {
	long double mx = right_angle, curr_angle;
	int res = -1;
	for(int i = 0;i < n;i++) {
		if(i != x && i != y) {
			curr_angle = abs(P[i].angle(P[x], P[y]));
			if(curr_angle < mx && curr_angle <= right_angle) {
				mx = curr_angle;
				res = i;
			}
		}
	}
	return res;
}

int just_greater_than(int x, int y) {
	long double mn = 2*right_angle, curr_angle;
	int res = -1;
	for(int i = 0;i < n;i++) {
		if(i != x && i != y) {
			curr_angle = abs(P[i].angle(P[x], P[y]));
			if(curr_angle < mn && curr_angle >= right_angle) {
				mn = curr_angle;
				res = i;
			}
		}
	}
	return res;
}

void get_valid_circle(int x, int y) {
	leda::point a = P[x], b = P[y];
	// check for circle with a, b being diameteric ends
	leda::point center((a.xcoord() + b.xcoord()) / 2.0, (a.ycoord() + b.ycoord()) / 2.0);
	leda::circle C1(center, P[x]);
	if(is_valid_circle(C1)) {
		long double rad = min_rad;
		min_rad = min(min_rad, (long double)C1.radius());
		if(min_rad < rad){
			defining_points[0] = x, defining_points[1] = y;
			defining_points[2] = -1;
		}
	}
	int z1 = just_greater_than(x, y);
	if(z1 > 0) {
		leda::circle C2(P[x], P[y], P[z1]);
		if(is_valid_circle(C2)) {
			long double rad = min_rad;
			min_rad = min(min_rad, (long double)C2.radius());
			if(min_rad < rad){
				defining_points[0] = x, defining_points[1] = y;
				defining_points[2] = z1;
			}
		}
	}
	int z2 = just_less_than(x, y);
	if(z2 > 0) {
		leda::circle C3(P[x], P[y], P[z2]);
		if(is_valid_circle(C3)) {
			long double rad = min_rad;
			min_rad = min(min_rad, (long double)C3.radius());
			if(min_rad < rad){
				defining_points[0] = x, defining_points[1] = y;
				defining_points[2] = z2;
			}
		}
	}
	return;
}

int main() {
	cout.precision(17);
	cin >> n;
	int x, y;
	for(int i = 0;i < n;i++) {
		cin >> x >> y;
		leda::point p(x, y);
		P.push_back(p);
	}
	for(int i = 0;i < n;i++)
		for(int j = i+1;j < n;j++) {
			get_valid_circle(i, j);
		}
	if(n < 2)
		cout << "Trivial Circle, with radius 0 centered at " << P[0] << endl;
	else {
		if(defining_points[2] == -1) {
			leda::point center(
				(P[defining_points[0]].xcoord() + P[defining_points[1]].xcoord()) / 2.0,
				(P[defining_points[0]].ycoord() + P[defining_points[1]].ycoord()) / 2.0);
			leda::circle smallest_circle(center, P[defining_points[0]]);
			cout << "Minimum radius enclosing circle is formed by 2 diametrical end, given by\n";
			cout << "Point A: " << P[defining_points[0]] << endl;
			cout << "Point B: " << P[defining_points[1]] << endl;
			cout << "Center of Cirlce: " << smallest_circle.center() << endl;
			cout << "Radius of Circle: " << smallest_circle.radius() << endl;
		}
		else {
			leda::circle smallest_circle(P[defining_points[0]], 
										 P[defining_points[1]], 
										 P[defining_points[2]]);
			cout << "Minimum radius enclosing circle is formed by 3 points, given by\n";
			cout << "Point A: " << P[defining_points[0]] << endl;
			cout << "Point B: " << P[defining_points[1]] << endl;
			cout << "Point C: " << P[defining_points[2]] << endl;
			cout << "Center of Cirlce: " << smallest_circle.center() << endl;
			cout << "Radius of Circle: " << smallest_circle.radius() << endl;
		}
	}
	return 0;
}