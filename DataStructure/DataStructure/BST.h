#pragma once
#include "BinTree.h"
#include "removeAt.h"

template <typename T>
class BST :public BinTree<T> {
public:
	BinNode<T>* hot;
	virtual BinNode<T>*& search(T& e) {
		if (!this->root || e == this->root->data) {
			hot = NULL;
			return this->root;
		}
		for (hot = this->root;;) {
			BinNode<T>*& v = (e < hot->data) ? hot->lc : hot->rc;
			if (!v || e == v->data) {
				return v;
			}
			hot = v;
		}
	}
	virtual BinNode<T>* insert(T& e) {
		BinNode<T>*& x = search(e);
		if (x) {
			return x;
		}
		x = new BinNode<T>(e, hot);
		this->size++;
		this->updateHeightAbove(x);
		return x;
	}
	virtual bool remove(T& e) {
		BinNode<T>*& x = search(e);
		if (!x) {
			return false;
		}
		removeAt(x, hot);
		this->size--;
		this->updateHeightAbove(hot);
		return true;
	}
	BinNode<T>* connect34(BinNode<T>* a, BinNode<T>* b, BinNode<T>* c, BinNode<T>* T0, BinNode<T>* T1, BinNode<T>* T2, BinNode<T>* T3) {
		a->lc = T0;
		if (T0) {
			T0->parent = a;
		}
		a->rc = T1;
		if (T1) {
			T1->parent = a;
		}
		this->updateHeight(a);
		c->lc = T2;
		if (T2) {
			T2->parent = c;
		}
		c->rc = T3;
		if (T3) {
			T3->parent = c;
		}
		this->updateHeight(c);
		b->lc = a;
		a->parent = b;
		b->rc = c;
		c->parent = b;
		this->updateHeight(b);
		return b;
	}
	BinNode<T>* rotateAt(BinNode<T>* v) {
		BinNode<T>* p = v->parent;
		BinNode<T>* g = p->parent;
		if (IsLChild(*p)) {
			if (IsLChild(*v)) {
				p->parent = g->parent;
				return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
			}
			else {
				v->parent = g->parent;
				return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
			}
		}
		else {
			if (IsRChild(*v)) {
				p->parent = g->parent;
				return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
			}
			else {
				v->parent = g->parent;
				return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
			}
		}
	}
};
