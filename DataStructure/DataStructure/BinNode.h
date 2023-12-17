#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include "macro.h"

template <typename T>
class BinNode {
public:
	T data;
	BinNode<T>* parent;
	BinNode<T>* lc;
	BinNode<T>* rc;
	int height;
	RBColor color;
	BinNode() :parent(NULL), lc(NULL), rc(NULL), height(0), color(RB_RED) {}
	BinNode(T e, BinNode<T>* p = NULL, BinNode<T>* lc = NULL, BinNode<T>* rc = NULL, int h = 0, RBColor c = RB_RED) :data(e), parent(p), lc(lc), rc(rc), height(h), color(c) {}
	int size() {
		int s = 1;
		if (lc) {
			s += lc->size();
		}
		if (rc) {
			s += rc->size();
		}
		return s;
	}
	BinNode<T>* insertAsLC(T& e) {
		return lc = new BinNode<T>(e, this);
	}
	BinNode<T>* insertAsRC(T& e) {
		return rc = new BinNode<T>(e, this);
	}
	BinNode<T>* prec() {
		BinNode<T>* p = this;
		if (lc) {
			p = lc;
			while (HasRChild(*p)) {
				p = p->rc;
			}
		}
		else {
			while (IsLChild(*p)) {
				p = p->parent;
			}
			p = p->parent;
		}
		return p;
	}
	BinNode<T>* succ() {
		BinNode<T>* s = this;
		if (rc) {
			s = rc;
			while (HasLChild(*s)) {
				s = s->lc;
			}
		}
		else {
			while (IsRChild(*s)) {
				s = s->parent;
			}
			s = s->parent;
		}
		return s;
	}
	std::vector<T> travPre() {
		std::vector<T> visit;
		BinNode<T>* x = this;
		std::stack<BinNode<T>*> S;
		while (true) {
			while (x) {
				visit.push_back(x->data);
				S.push(x->rc);
				x = x->lc;
			}
			if (S.empty()) {
				break;
			}
			x = S.top();
			S.pop();
		}
		return visit;
	}
	std::vector<T> travIn() {
		std::vector<T> visit;
		BinNode<T>* x = this;
		std::stack<BinNode<T>*> S;
		while (true) {
			while (x) {
				S.push(x);
				x = x->lc;
			}
			if (S.empty()) {
				break;
			}
			x = S.top();
			S.pop();
			visit.push_back(x->data);
			x = x->rc;
		}
		return visit;
	}
	std::vector<T> travPost() {
		std::vector<T> visit;
		BinNode<T>* x = this;
		std::stack<BinNode<T>*> S;
		if (x) {
			S.push(x);
		}
		while (!S.empty()) {
			if (S.top() != x->parent) {
				while (x = S.top()) {
					if (HasLChild(*x)) {
						if (HasRChild(*x)) {
							S.push(x->rc);
						}
						S.push(x->lc);
					}
					else {
						S.push(x->rc);
					}
				}
				S.pop();
			}
			x = S.top();
			S.pop();
			visit.push_back(x->data);
		}
		return visit;
	}
	std::vector<T> travLevel() {
		std::vector<T> visit;
		BinNode<T>* x = this;
		std::queue<BinNode<T>*> Q;
		if (x) {
			Q.push(x);
		}
		while (!Q.empty()) {
			x = Q.front();
			Q.pop();
			visit.push_back(x->data);
			if (HasLChild(*x)) {
				Q.push(x->lc);
			}
			if (HasRChild(*x)) {
				Q.push(x->rc);
			}
		}
		return visit;
	}
};
