#pragma once
class Point {
public:
	int x;
	Point() {}
	Point(int x) :x(x) {}
	bool operator==(Point& p) {
		return x == p.x;
	}
	bool operator!=(Point& p) {
		return x != p.x;
	}
	bool operator<(Point& p) {
		return x < p.x;
	}
	bool operator>(Point& p) {
		return x > p.x;
	}
	bool operator<=(Point& p) {
		return x <= p.x;
	}
	bool operator>=(Point& p) {
		return x >= p.x;
	}
};
