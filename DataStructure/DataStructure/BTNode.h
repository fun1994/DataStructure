#pragma once
#include <iostream>
#include <vector>

template <typename T>
class BTNode {
public:
	std::vector<T> key;
	BTNode<T>* parent;
	std::vector<BTNode<T>*> child;
	BTNode() {
		parent = NULL;
		child.insert(child.begin(), NULL);
	}
	BTNode(T e, BTNode<T>* lc = NULL, BTNode<T>* rc = NULL) {
		key.insert(key.begin(), e);
		parent = NULL;
		child.insert(child.begin(), lc);
		if (lc) {
			lc->parent = this;
		}
		child.insert(child.begin() + 1, rc);
		if (rc) {
			rc->parent = this;
		}
	}
};
