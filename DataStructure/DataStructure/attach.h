#pragma once
#include "BinNode.h"

template <typename T>
void attachAsLC(BinNode<T>* p, BinNode<T>* lc) {
	p->lc = lc;
	if (lc) {
		lc->parent = p;
	}
}

template <typename T>
void attachAsRC(BinNode<T>* p, BinNode<T>* rc) {
	p->rc = rc;
	if (rc) {
		rc->parent = p;
	}
}
