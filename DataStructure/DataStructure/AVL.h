#pragma once
#include "BST.h"

template <typename T>
class AVL :public BST<T> {
public:
	BinNode<T>* insert(T& e) {
		BinNode<T>*& x = this->search(e);
		if (x) {
			return x;
		}
		BinNode<T>* xx = x = new BinNode<T>(e, this->hot);
		this->size++;
		for (BinNode<T>* g = this->hot; g; g = g->parent) {
			if (!AvlBalanced(*g)) {
				FromParentTo(*g) = this->rotateAt(tallerChild(tallerChild(g)));
				break;
			}
			else {
				this->updateHeight(g);
			}
		}
		return xx;
	}
	bool remove(T& e) {
		BinNode<T>*& x = this->search(e);
		if (!x) {
			return false;
		}
		removeAt(x, this->hot);
		this->size--;
		for (BinNode<T>* g = this->hot; g; g = g->parent) {
			if (!AvlBalanced(*g)) {
				g = FromParentTo(*g) = this->rotateAt(tallerChild(tallerChild(g)));
			}
			this->updateHeight(g);
		}
		return true;
	}
};
