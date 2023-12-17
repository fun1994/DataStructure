#pragma once
#include <vector>

template <typename T>
int search(std::vector<T>& v, T& e) {
	int r = -1;
	for (int i = 0; i < v.size(); i++) {
		if (v[i] <= e) {
			r++;
		}
	}
	return r;
}
