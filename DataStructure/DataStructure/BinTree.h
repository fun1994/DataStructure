#pragma once
#include "BinNode.h"

template <typename T>
class BinTree {
public:
	int size;
	BinNode<T>* root;
	BinTree() :size(0), root(NULL) {}
	bool empty() {
		return !root;
	}
	virtual int updateHeight(BinNode<T>* x) {
		return x->height = 1 + std::max(stature(x->lc), stature(x->rc));
	}
	void updateHeightAbove(BinNode<T>* x) {
		while (x) {
			updateHeight(x);
			x = x->parent;
		}
	}
	BinNode<T>* insertAsRoot(T& e) {
		size = 1;
		return root = new BinNode<T>(e);
	}
	BinNode<T>* insertAsLC(BinNode<T>* x, T& e) {
		size++;
		x->insertAsLC(e);
		updateHeightAbove(x);
		return x->lc;
	}
	BinNode<T>* insertAsRC(BinNode<T>* x, T& e) {
		size++;
		x->insertAsRC(e);
		updateHeightAbove(x);
		return x->rc;
	}
	BinNode<T>* attachAsLC(BinNode<T>* x, BinTree<T>* S) {
		if (x->lc = S->root) {
			x->lc->parent = x;
		}
		size += S->size;
		updateHeightAbove(x);
		return x;
	}
	BinNode<T>* attachAsRC(BinNode<T>* x, BinTree<T>* S) {
		if (x->rc = S->root) {
			x->rc->parent = x;
		}
		size += S->size;
		updateHeightAbove(x);
		return x;
	}
	int remove(BinNode<T>* x) {
		FromParentTo(*x) = NULL;
		updateHeightAbove(x->parent);
		int n = x->size();
		size -= n;
		return n;
	}
	BinTree<T>* secede(BinNode<T>* x) {
		FromParentTo(*x) = NULL;
		updateHeightAbove(x->parent);
		BinTree<T>* S = new BinTree<T>;
		S->root = x;
		x->parent = NULL;
		S->size = x->size();
		size -= S->size;
		return S;
	}
	std::vector<T> travPre() {
		return root->travPre();
	}
	std::vector<T> travIn() {
		return root->travIn();
	}
	std::vector<T> travPost() {
		return root->travPost();
	}
	std::vector<T> travLevel() {
		return root->travLevel();
	}
};
