#pragma once
#include "BTNode.h"
#include "search.h"

template <typename T>
class BTree {
public:
	int size;
	int m;
	BTNode<T>* root;
	BTNode<T>* hot;
	BTree(int m = 3) :size(0), m(m) {
		root = new BTNode<T>;
	}
	void solveOverflow(BTNode<T>* v) {
		while (m <= v->key.size()) {
			int s = m / 2;
			BTNode<T>* u = new BTNode<T>;
			for (int j = 0; j < m - s - 1; j++) {
				u->key.insert(u->key.begin() + j, v->key[s + 1]);
				v->key.erase(v->key.begin() + (s + 1));
				u->child.insert(u->child.begin() + j, v->child[s + 1]);
				v->child.erase(v->child.begin() + (s + 1));
			}
			u->child[m - s - 1] = v->child[s + 1];
			v->child.erase(v->child.begin() + (s + 1));
			if (u->child[0]) {
				for (int j = 0; j < m - s; j++) {
					u->child[j]->parent = u;
				}
			}
			BTNode<T>* p = v->parent;
			if (!p) {
				root = p = new BTNode<T>;
				p->child[0] = v;
				v->parent = p;
			}
			int r = 1 + ::search(p->key, v->key[0]);
			p->key.insert(p->key.begin() + r, v->key[s]);
			v->key.erase(v->key.begin() + s);
			p->child.insert(p->child.begin() + (r + 1), u);
			u->parent = p;
			v = p;
		}
	}
	void solveUnderflow(BTNode<T>* v) {
		while ((m + 1) / 2 > v->child.size()) {
			BTNode<T>* p = v->parent;
			if (!p) {
				if (!v->key.size() && v->child[0]) {
					root = v->child[0];
					root->parent = NULL;
				}
				return;
			}
			int r = 0;
			while (p->child[r] != v) {
				r++;
			}
			if (0 < r) {
				BTNode<T>* ls = p->child[r - 1];
				if ((m + 1) / 2 < ls->child.size()) {
					v->key.insert(v->key.begin(), p->key[r - 1]);
					p->key[r - 1] = ls->key[ls->key.size() - 1];
					ls->key.erase(ls->key.begin() + (ls->key.size() - 1));
					v->child.insert(v->child.begin(), ls->child[ls->child.size() - 1]);
					ls->child.erase(ls->child.begin() + (ls->child.size() - 1));
					if (v->child[0]) {
						v->child[0]->parent = v;
					}
					return;
				}
			}
			if (p->child.size() - 1 > r) {
				BTNode<T>* rs = p->child[r + 1];
				if ((m + 1) / 2 < rs->child.size()) {
					v->key.insert(v->key.begin() + v->key.size(), p->key[r]);
					p->key[r] = rs->key[0];
					rs->key.erase(rs->key.begin());
					v->child.insert(v->child.begin() + v->child.size(), rs->child[0]);
					rs->child.erase(rs->child.begin());
					if (v->child[v->child.size() - 1]) {
						v->child[v->child.size() - 1]->parent = v;
					}
					return;
				}
			}
			if (0 < r) {
				BTNode<T>* ls = p->child[r - 1];
				ls->key.insert(ls->key.begin() + ls->key.size(), p->key[r - 1]);
				p->key.erase(p->key.begin() + (r - 1));
				p->child.erase(p->child.begin() + r);
				ls->child.insert(ls->child.begin() + ls->child.size(), v->child[0]);
				v->child.erase(v->child.begin());
				if (ls->child[ls->child.size() - 1]) {
					ls->child[ls->child.size() - 1]->parent = ls;
				}
				while (!v->key.empty()) {
					ls->key.insert(ls->key.begin() + ls->key.size(), v->key[0]);
					v->key.erase(v->key.begin());
					ls->child.insert(ls->child.begin() + ls->child.size(), v->child[0]);
					v->child.erase(v->child.begin());
					if (ls->child[ls->child.size() - 1]) {
						ls->child[ls->child.size() - 1]->parent = ls;
					}
				}
			}
			else {
				BTNode<T>* rs = p->child[r + 1];
				rs->key.insert(rs->key.begin(), p->key[r]);
				p->key.erase(p->key.begin() + r);
				p->child.erase(p->child.begin() + r);
				rs->child.insert(rs->child.begin(), v->child[v->child.size() - 1]);
				v->child.erase(v->child.begin() + (v->child.size() - 1));
				if (rs->child[0]) {
					rs->child[0]->parent = rs;
				}
				while (!v->key.empty()) {
					rs->key.insert(rs->key.begin(), v->key[v->key.size() - 1]);
					v->key.erase(v->key.begin() + (v->key.size() - 1));
					rs->child.insert(rs->child.begin(), v->child[v->child.size() - 1]);
					v->child.erase(v->child.begin() + (v->child.size() - 1));
					if (rs->child[0]) {
						rs->child[0]->parent = rs;
					}
				}
			}
			v = p;
		}
	}
	BTNode<T>* search(T& e) {
		BTNode<T>* v = root;
		hot = NULL;
		while (v) {
			int r = ::search(v->key, e);
			if (0 <= r && e == v->key[r]) {
				return v;
			}
			hot = v;
			v = v->child[r + 1];
		}
		return NULL;
	}
	bool insert(T& e) {
		BTNode<T>* v = search(e);
		if (v) {
			return false;
		}
		int r = ::search(hot->key, e);
		hot->key.insert(hot->key.begin() + (r + 1), e);
		hot->child.insert(hot->child.begin() + (r + 2), NULL);
		size++;
		solveOverflow(hot);
		return true;
	}
	bool remove(T& e) {
		BTNode<T>* v = search(e);
		if (!v) {
			return false;
		}
		int r = ::search(v->key, e);
		if (v->child[0]) {
			BTNode<T>* u = v->child[r + 1];
			while (u->child[0]) {
				u = u->child[0];
			}
			v->key[r] = u->key[0];
			v = u;
			r = 0;
		}
		v->key.erase(v->key.begin() + r);
		v->child.erase(v->child.begin() + (r + 1));
		size--;
		solveUnderflow(v);
	}
};
