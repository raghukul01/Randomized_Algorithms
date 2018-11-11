#include "matplotlibcpp.h"
#include <bits/stdc++.h>
#include <LEDA/geo/circle.h>
#include <LEDA/geo/point.h>
using namespace std;
namespace plt = matplotlibcpp;
#define inf 1e18 
#define right_angle acos(0)
#define eps 1e-8
long double factor = 180.0/(2*right_angle);

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

bool is_valid_circle(leda::circle C,int q) {
	bool v = true;
	for(int i = 0;i <= q;i++)
		if(outside(C,P[i]))
			v = false;
	return v;
}

int just_less_than(int x, int y) {
	long double mx = right_angle*factor;
	long double curr_angle = 0.0;
	int res = -1;
	for(int i = 0;i < x;i++) {
		if(i != x && i != y) {
			curr_angle = abs(P[i].angle(P[y], P[x]));
			curr_angle = curr_angle*factor;
			long double temp = abs(P[i].angle(P[x], P[y]));
			temp = temp*factor;
			curr_angle = min(curr_angle,temp);
			if(curr_angle < mx && curr_angle <= right_angle*factor) {
				mx = curr_angle;
				res = i;
			}
		}
	}
	return res;
}

void get_valid_circle(int x, int y) {
	min_rad = inf;
	leda::point a = P[x], b = P[y];
	// check for circle with a, b being diameteric ends
	leda::point center((a.xcoord() + b.xcoord()) / 2.0, (a.ycoord() + b.ycoord()) / 2.0);
	leda::circle C1(center, a);
	if(is_valid_circle(C1,x-1)) {
		long double rad = min_rad;
		min_rad = min(min_rad, (long double)C1.radius());
		if(min_rad < rad){
			defining_points[0] = x, defining_points[1] = y;
			defining_points[2] = -1;
		}
	}
	int z2 = just_less_than(x, y);
	if(z2 >= 0) {
		leda::circle C3(P[x], P[y], P[z2]);
		if(is_valid_circle(C3,x-1)) {
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

leda::circle build_circle(int index,int p_i){
	if(index == 0) {
		leda::point c((P[index].xcoord() + P[p_i].xcoord()) / 2.0, (P[index].ycoord() + P[p_i].ycoord()) / 2.0);
		leda::circle C(c, P[index]);
		defining_points[0] = index; 
		defining_points[1] = p_i;
		defining_points[2] = -1;
		return C;
	}
	leda::circle C = build_circle(index-1,p_i);
	if(outside(C,P[index])){
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
	return C;
}

void print(){
	if(defining_points[2] == -1) {
		leda::point center(
			(P[defining_points[0]].xcoord() + P[defining_points[1]].xcoord()) / 2.0,
			(P[defining_points[0]].ycoord() + P[defining_points[1]].ycoord()) / 2.0);
		leda::circle smallest_circle(center, P[defining_points[0]]);
		// cout << "Minimum radius enclosing circle is formed by 2 diametrical end, given by\n";
		// cout << "Point A: " << P[defining_points[0]] << endl;
		// cout << "Point B: " << P[defining_points[1]] << endl;
		cout << smallest_circle.center() << endl;
		cout << smallest_circle.radius() << endl;
	}
	else {
		leda::circle smallest_circle(P[defining_points[0]], 
									 P[defining_points[1]], 
									 P[defining_points[2]]);
		// cout << "Minimum radius enclosing circle is formed by 3 points, given by\n";
		// cout << "Point A: " << P[defining_points[0]] << endl;
		// cout << "Point B: " << P[defining_points[1]] << endl;
		// cout << "Point C: " << P[defining_points[2]] << endl;
		cout << smallest_circle.center() << endl;
		cout << smallest_circle.radius() << endl;
	}
}

int main() {
	clock_t begin = clock();
	cout.precision(7);
	cin >> n;
	int x, y;
	for(int i = 0;i < n;i++) {
		cin >> x >> y;
		leda::point p(x, y);
		P.push_back(p);
	}
	random_shuffle(P.begin(),P.end());
	leda::point center(
		(P[0].xcoord() + P[1].xcoord()) / 2.0,
		(P[0].ycoord() + P[1].ycoord()) / 2.0);
	leda::circle C(center, P[1]);
	for(int i = 0;i < 2;i++)
		defining_points[i] = i;
	defining_points[2] = -1;
	for(int i=2;i<n;i++){
		if(outside(C,P[i])){
			C = build_circle(i-1,i);
		}
	}
	// // print();
	// clock_t end = clock();
	// double elapsed_secs = (long double)(end - begin) / CLOCKS_PER_SEC;
	// cout << elapsed_secs*1000 << endl;
	return 0;
}
