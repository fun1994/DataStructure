#pragma once
#include "BST.h"
#include "attach.h"

template <typename T>
class Splay :public BST<T> {
public:
	BinNode<T>* splay(BinNode<T>* v) {
		if (!v) {
			return NULL;
		}
		BinNode<T>* p;
		BinNode<T>* g;
		while ((p = v->parent) && (g = p->parent)) {
			BinNode<T>* gg = g->parent;
			if (IsLChild(*v)) {
				if (IsLChild(*p)) {
					attachAsLC(g, p->rc);
					attachAsLC(p, v->rc);
					attachAsRC(p, g);
					attachAsRC(v, p);
				}
				else {
					attachAsLC(p, v->rc);
					attachAsRC(g, v->lc);
					attachAsLC(v, g);
					attachAsRC(v, p);
				}
			}
			else {
				if (IsRChild(*p)) {
					attachAsRC(g, p->lc);
					attachAsRC(p, v->lc);
					attachAsLC(p, g);
					attachAsLC(v, p);
				}
				else {
					attachAsRC(p, v->lc);
					attachAsLC(g, v->rc);
					attachAsRC(v, g);
					attachAsLC(v, p);
				}
			}
			if (!gg) {
				v->parent = NULL;
			}
			else {
				(g == gg->lc) ? attachAsLC(gg, v) : attachAsRC(gg, v);
			}
			this->updateHeight(g);
			this->updateHeight(p);
			this->updateHeight(v);
		}
		if (p = v->parent) {
			if (IsLChild(*v)) {
				attachAsLC(p, v->rc);
				attachAsRC(v, p);
			}
			else {
				attachAsRC(p, v->lc);
				attachAsLC(v, p);
			}
			this->updateHeight(p);
			this->updateHeight(v);
		}
		v->parent = NULL;
		return v;
	}
	BinNode<T>*& search(T& e) {
		BinNode<T>* p = BST<T>::search(e);
		this->root = splay(p ? p : this->hot);
		return this->root;
	}
	BinNode<T>* insert(T& e) {
		if (!this->root) {
			this->size = 1;
			return this->root = new BinNode<T>(e);
		}
		BinNode<T>* t = search(e);
		if (e == t->data) {
			return t;
		}
		if (t->data < e) {
			t->parent = this->root = new BinNode<T>(e, NULL, t, t->rc);
			if (t->rc) {
				t->rc->parent = this->root;
				t->rc = NULL;
			}
		}
		else {
			t->parent = this->root = new BinNode<T>(e, NULL, t->lc, t);
			if (t->lc) {
				t->lc->parent = this->root;
				t->lc = NULL;
			}
		}
		this->size++;
		this->updateHeightAbove(t);
		return this->root;
	}
	bool remove(T& e) {
		if (!this->root || e != search(e)->data) {
			return false;
		}
		BinNode<T>* L = this->root->lc;
		BinNode<T>* R = this->root->rc;
		this->root->lc = NULL;
		this->root->rc = NULL;
		if (!R) {
			if (L) {
				L->parent = NULL;
			}
			this->root = L;
		}
		else {
			this->root = R;
			R->parent = NULL;
			search(e);
			if (L) {
				L->parent = this->root;
			}
			this->root->lc = L;
		}
		if (--this->size) {
			this->updateHeight(this->root);
		}
		return true;
	}
};
