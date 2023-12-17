#pragma once
#include "BST.h"

template <typename T>
class RedBlack :public BST<T> {
public:
	int updateHeight(BinNode<T>* x) {
		return x->height = IsBlack(x) + std::max(stature(x->lc), stature(x->rc));
	}
	void solveDoubleRed(BinNode<T>* x) {
		if (IsRoot(*x)) {
			this->root->color = RB_BLACK;
			this->root->height++;
			return;
		}
		BinNode<T>* p = x->parent;
		if (IsBlack(p)) {
			return;
		}
		BinNode<T>* g = p->parent;
		BinNode<T>* u = uncle(x);
		if (IsBlack(u)) {
			if (IsLChild(*x) == IsLChild(*p)) {
				p->color = RB_BLACK;
			}
			else {
				x->color = RB_BLACK;
			}
			g->color = RB_RED;
			BinNode<T>* gg = g->parent;
			BinNode<T>* r = FromParentTo(*g) = this->rotateAt(x);
			r->parent = gg;
		}
		else {
			p->color = RB_BLACK;
			p->height++;
			u->color = RB_BLACK;
			u->height++;
			g->color = RB_RED;
			solveDoubleRed(g);
		}
	}
	void solveDoubleBlack(BinNode<T>* r) {
		BinNode<T>* p = r ? r->parent : this->hot;
		if (!p) {
			return;
		}
		BinNode<T>* s = (r == p->lc) ? p->rc : p->lc;
		if (IsBlack(s)) {
			BinNode<T>* t = NULL;
			if (IsRed(s->rc)) {
				t = s->rc;
			}
			if (IsRed(s->lc)) {
				t = s->lc;
			}
			if (t) {
				RBColor oldColor = p->color;
				BinNode<T>* b = FromParentTo(*p) = this->rotateAt(t);
				if (HasLChild(*b)) {
					b->lc->color = RB_BLACK;
					updateHeight(b->lc);
				}
				if (HasRChild(*b)) {
					b->rc->color = RB_BLACK;
					updateHeight(b->rc);
				}
				b->color = oldColor;
				updateHeight(b);
			}
			else {
				s->color = RB_RED;
				s->height--;
				if (IsRed(p)) {
					p->color = RB_BLACK;
				}
				else {
					p->height--;
					solveDoubleBlack(p);
				}
			}
		}
		else {
			s->color = RB_BLACK;
			p->color = RB_RED;
			BinNode<T>* t = IsLChild(*s) ? s->lc : s->rc;
			this->hot = p;
			FromParentTo(*p) = this->rotateAt(t);
			solveDoubleBlack(r);
		}
	}
	BinNode<T>* insert(T& e) {
		BinNode<T>*& x = this->search(e);
		if (x) {
			return x;
		}
		x = new BinNode<T>(e, this->hot, NULL, NULL, -1);
		this->size++;
		BinNode<T>* xOld = x;
		solveDoubleRed(x);
		return xOld;
	}
	bool remove(T& e) {
		BinNode<T>*& x = this->search(e);
		if (!x) {
			return false;
		}
		BinNode<T>* r = removeAt(x, this->hot);
		if (!(--this->size)) {
			return true;
		}
		if (!this->hot) {
			this->root->color = RB_BLACK;
			updateHeight(this->root);
			return true;
		}
		if (BlackHeightUpdated(*this->hot)) {
			return true;
		}
		if (IsRed(r)) {
			r->color = RB_BLACK;
			r->height++;
			return true;
		}
		solveDoubleBlack(r);
		return true;
	}
};
