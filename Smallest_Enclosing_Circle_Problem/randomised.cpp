#include <bits/stdc++.h>
#include <LEDA/geo/circle.h>
#include <LEDA/geo/point.h>
using namespace std;
#define inf 1e18 

int n;
vector<leda::point> P;
long double min_rad = inf;
vector<int> defining_points(3, 0);

bool is_valid_circle(leda::circle C,int n) {
	bool v = true;
	for(int i = 0;i < n;i++)
		if(C.outside(P[i]))
			v = false;
	return v;
}

int just_less_than(int x, int y) {
	long double mx = 0.0, curr_angle;
	int res = -1;
	for(int i = 0;i < y;i++) {
		if(i != x && i != y) {
			curr_angle = abs(P[i].angle(P[x], P[y]));
			if(curr_angle > mx && curr_angle <= right_angle) {
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
	for(int i = 0;i < y;i++) {
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
	if(is_valid_circle(C1,y)) {
		min_rad = min(min_rad, (long double)C1.radius());
		defining_points[0] = x, defining_points[1] = y;
		defining_points[2] = -1;
	}
	// get circle with just greater than 90, and just less than 90;
	int z1 = just_greater_than(x, y);
	if(z1 > 0) {
		leda::circle C2(P[x], P[y], P[z1]);
		if(is_valid_circle(C2,y)) {
			min_rad = min(min_rad, (long double)C2.radius());
			defining_points[0] = x, defining_points[1] = y;
			defining_points[2] = z1;
		}
	}
	int z2 = just_less_than(x, y);
	if(z2 > 0) {
		leda::circle C3(P[x], P[y], P[z2]);
		if(is_valid_circle(C3,y)) {
			min_rad = min(min_rad, (long double)C3.radius());
			defining_points[0] = x, defining_points[1] = y;
			defining_points[2] = z2;
		}
	}
	return;
}

leda::circle build_circle(int index,int p_i){
	if(build_circle(index-1,p_i).outside(P[index])){
		get_valid_circle(index,p_i);
		if(defining_points[2] == -1) {
			leda::point center(
				(P[defining_points[0]].xcoord() + P[defining_points[1]].xcoord()) / 2.0,
				(P[defining_points[0]].ycoord() + P[defining_points[1]].ycoord()) / 2.0);
			leda::circle smallest_circle(center, P[defining_points[0]]);
			return smallest_circle;
		}
		else {
			leda::circle smallest_circle(P[defining_points[0]], 
										 P[defining_points[1]], 
										 P[defining_points[2]]);
			return smallest_circle;
		}
	}
	return build_circle(index-1,p_i);
}

void print(){
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

int main() {
	cin >> n;
	int x, y;
	for(int i = 0;i < n;i++) {
		cin >> x >> y;
		leda::point p(x, y);
		P.push_back(p);
	}
	two_points[0] = P[0];
	two_points[1] = P[1];
	leda::point center(
		(P[two_points[0]].xcoord() + P[two_points[1]].xcoord()) / 2.0,
		(P[two_points[0]].ycoord() + P[two_points[1]].ycoord()) / 2.0);
	leda::circle C(center, P[two_points[0]]);
	for(int i=2;i<n;i++){
		if(C.outside(P[i])){
			C = build_circle(i-1,i);
		}
	}
	print();
	return 0;
}