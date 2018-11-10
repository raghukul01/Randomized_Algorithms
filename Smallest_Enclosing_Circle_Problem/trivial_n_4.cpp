#include <bits/stdc++.h>
#include <LEDA/geo/circle.h>
#include <LEDA/geo/point.h>
using namespace std;
#define inf 1e18 
#define eps 1e-6

int n;
vector<leda::point> P;
long double min_rad = inf;
vector<int> two_points(2, 0), three_points(3, 0);

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

long double check_two_points() {
	long double r = inf;
	for(int i = 0;i < n;i++)
		for(int j = i+1;j < n;j++) {
			leda::point center((P[i].xcoord() + P[j].xcoord())/2.0,(P[i].ycoord() + P[j].ycoord())/2.0);
			leda::circle C(center, P[i]);
			if(is_valid_circle(C)) {
				long double rad = r;
				r = min(rad, (long double)C.radius());
				if(r<rad){
					two_points[0] = i;
					two_points[1] = j;
				}
			}
		}
	return r;
}

long double check_three_points() {
	long double r = inf;
	for(int i = 0;i < n;i++)
		for(int j = i+1;j < n;j++)
			for(int k = j+1;k < n;k++) {
				leda::circle C(P[i], P[j], P[k]);
				if(is_valid_circle(C)) {
					long double rad = r;
					r = min(rad, (long double)C.radius());
					if(r<rad){
						three_points[0] = i;
						three_points[1] = j;
						three_points[2] = k;
					}
				}
			}
	return r;
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

	if(n > 1)
		min_rad = min(min_rad, check_two_points());
	if(n > 2)
		min_rad = min(min_rad,check_three_points());
	if(min_rad == inf) {
		cout << "No circle possible\n";
	}
	else if(min_rad == check_two_points()) {
		leda::point center(
			(P[two_points[0]].xcoord() + P[two_points[1]].xcoord()) / 2.0,
			(P[two_points[0]].ycoord() + P[two_points[1]].ycoord()) / 2.0);
		leda::circle smallest_circle(center, P[two_points[0]]);
		cout << "Minimum radius enclosing circle is formed by 2 diametrical end, given by\n";
		cout << "Point A: " << P[two_points[0]] << endl;
		cout << "Point B: " << P[two_points[1]] << endl;
		cout << "Center of Circle: " << smallest_circle.center() << endl;
		cout << "Radius of Circle: " << smallest_circle.radius() << endl;
	}
	else {
		leda::circle smallest_circle(P[three_points[0]], P[three_points[1]], P[three_points[2]]);
		cout << "Minimum radius enclosing circle is formed by 3 points, given by\n";
		cout << "Point A: " << P[three_points[0]] << endl;
		cout << "Point B: " << P[three_points[1]] << endl;
		cout << "Point C: " << P[three_points[2]] << endl;
		cout << "Center of Circle: " << smallest_circle.center() << endl;
		cout << "Radius of Circle: " << smallest_circle.radius() << endl;
	}
	return 0;
}