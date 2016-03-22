#pragma once
#include <cstdio>
#include <iostream>
#include "ialgo.h"

using std::swap;
using std::cout;

class SplayTree {
private:
	int key_;
	int sum_;
	int size_;
	int psh_;
	bool flag_;
	int leftist_;
	int rightist_;
	int sizeLeft_;
	int sizeRight_;
	SplayTree *parent_;
	SplayTree *left_;
	SplayTree *right_;

	void changeParent(SplayTree *t, SplayTree *p) {
		if (t == NULL) {
			return;
		}

		t->parent_ = p;
	}

	void changeLeft(SplayTree *t, SplayTree *left) {
		t->left_ = left;
	}

	void changeRight(SplayTree *t, SplayTree *right) {
		t->right_ = right;
	}

	bool isLeft(SplayTree *t) {
		return t->parent_->left_ == t;
	}

	int getSize(SplayTree *t) {
		if (t == NULL) {
			return 0;
		}

		return t->size_;
	}

	int sum(SplayTree *t) {
		if (t == NULL) {
			return 0;
		}

		return t->sum_;
	}

	int sizeLeft(SplayTree *t) {
		if (t == NULL) {
			return 0;
		}

		return t->sizeLeft_;
	}

	int sizeRight(SplayTree *t) {
		if (t == NULL) {
			return 0;
		}

		return t->sizeRight_;
	}

	void recalc(SplayTree *t) {
		if (t->left_ != NULL) {
			t->leftist_ = t->left_->leftist_;
		}
		else {
			t->leftist_ = t->key_;
		}

		if (t->right_ != NULL) {
			t->rightist_ = t->right_->rightist_;
		}
		else {
			t->rightist_ = t->key_;
		}

		if (sizeRight(t->right_) != getSize(t->right_)) {
			t->sizeRight_ = sizeRight(t->right_);
		}
		else if (t->right_ != NULL && t->key_ < t->right_->leftist_) {
			t->sizeRight_ = sizeRight(t->right_);
		}
		else if (t->left_ == NULL || t->left_->rightist_ < t->key_) {
			t->sizeRight_ = sizeRight(t->right_) + 1;
		}
		else {
			t->sizeRight_ = sizeRight(t->right_) + 1 + sizeRight(t->left_);
		}

		if (sizeLeft(t->left_) != getSize(t->left_)) {
			t->sizeLeft_ = sizeLeft(t->left_);
		}
		else if (t->left_ != NULL && t->left_->rightist_ > t->key_) {
			t->sizeLeft_ = sizeLeft(t->left_);
		}
		else if (t->right_ == NULL || t->key_ > t->right_->leftist_) {
			t->sizeLeft_ = sizeLeft(t->left_) + 1;
		}
		else {
			t->sizeLeft_ = sizeLeft(t->left_) + 1 + sizeLeft(t->right_);
		}

		t->size_ = 1 + getSize(t->left_) + getSize(t->right_);
		t->sum_ = t->key_ + sum(t->left_) + sum(t->right_);
	}

	void sets(SplayTree *t, int psh) {
		if (t == NULL) {
			return;
		}

		t->sum_ += psh * getSize(t);
		t->key_ += psh;
		t->leftist_ += psh;
		t->rightist_ += psh;
		t->psh_ += psh;
	}

	void setsFlag(SplayTree *t) {
		if (t == NULL) {
			return;
		}
		swap(t->left_, t->right_);
		swap(t->leftist_, t->rightist_);
		swap(t->sizeLeft_, t->sizeRight_);
		t->flag_ = !t->flag_;
	}

	void push(SplayTree *t) {
		if (t == NULL) {
			return;
		}

		if (t->psh_ != 0) {
			sets(t->left_, t->psh_);
			sets(t->right_, t->psh_);
			t->psh_ = 0;
		}

		if (t->flag_) {
			setsFlag(t->left_);
			setsFlag(t->right_);
			t->flag_ = false;
		}
	}

	void zig(SplayTree *t) {
		if (t->parent_->parent_ != NULL) {
			if (isLeft(t->parent_)) {
				changeLeft(t->parent_->parent_, t);
			}
			else {
				changeRight(t->parent_->parent_, t);
			}
		}

		changeLeft(t->parent_, t->right_);
		changeParent(t->right_, t->parent_);
		changeRight(t, t->parent_);
		SplayTree *buf = t->parent_->parent_;
		changeParent(t->parent_, t);
		changeParent(t, buf);
		recalc(t->right_);
		recalc(t);
	}

	void zag(SplayTree *t) {
		if (t->parent_->parent_ != NULL) {
			if (isLeft(t->parent_)) {
				changeLeft(t->parent_->parent_, t);
			}
			else {
				changeRight(t->parent_->parent_, t);
			}
		}

		changeRight(t->parent_, t->left_);
		changeParent(t->left_, t->parent_);
		changeLeft(t, t->parent_);
		SplayTree *buf = t->parent_->parent_;
		changeParent(t->parent_, t);
		changeParent(t, buf);
		recalc(t->left_);
		recalc(t);
	}

	void splay(SplayTree *t) {
		if (t->parent_ == NULL) {
			return;
		}

		if (t->parent_->parent_ == NULL) {
			if (isLeft(t)) {
				zig(t);
			}
			else {
				zag(t);
			}

			return;
		}

		if (isLeft(t) == isLeft(t->parent_)) {
			if (isLeft(t)) {
				zig(t->parent_);
				zig(t);
			}
			else {
				zag(t->parent_);
				zag(t);
			}
		}
		else {
			if (isLeft(t)) {
				zig(t);
				zag(t);
			}
			else {
				zag(t);
				zig(t);
			}
		}

		splay(t);
	}

	SplayTree* getLeft(SplayTree *t) {
		push(t);
		if (t->left_ == NULL) {
			return t;
		}

		return getLeft(t->left_);
	}

	SplayTree* getRight(SplayTree *t) {
		push(t);
		if (t->right_ == NULL) {
			return t;
		}

		return getRight(t->right_);
	}

	SplayTree* merge(SplayTree *left, SplayTree *right) {
		if (left == NULL) {
			return right;
		}

		if (right == NULL) {
			return left;
		}

		left = getRight(left);
		right = getLeft(right);

		splay(left);
		splay(right);

		left->right_ = right;

		changeParent(right, left);

		recalc(left);

		return left;
	}

	SplayTree* getElement(SplayTree *t, int pos) {
		push(t);
		if (getSize(t->left_) > pos) {
			return getElement(t->left_, pos);
		}
		else if (pos == getSize(t->left_)) {
			return t;
		}
		else {
			return getElement(t->right_, pos - getSize(t->left_) - 1);
		}
	}

	void split(SplayTree *t, int count, SplayTree *&l, SplayTree *&r) {
		push(t);
		if (getSize(t) == count) {
			l = t;
			r = NULL;
			return;
		}

		t = getElement(t, count);

		splay(t);

		if (t->psh_ != 0) {
			throw 1;
		}

		l = t->left_;
		changeParent(l, NULL);
		t->left_ = NULL;
		r = t;
		recalc(r);
	}
public:
	SplayTree()
	{}

	SplayTree(int key, int sum, int size, SplayTree *p, SplayTree *l, SplayTree *r) :
		key_(key),
		sum_(sum),
		size_(size),
		psh_(0),
		flag_(false),
		leftist_(key),
		rightist_(key),
		sizeLeft_(1),
		sizeRight_(1),
		parent_(p),
		left_(l),
		right_(r)
	{}

	SplayTree* insert(SplayTree *t, int position, int element) {
		SplayTree *l = NULL, *r = NULL;
		split(t, position, l, r);

		return merge(merge(l, new SplayTree(element, element, 1, NULL, NULL, NULL)), r);
	}

	SplayTree* changeElement(SplayTree *t, int position, int element) {
		t = getElement(t, position);
		splay(t);
		t->key_ = element;
		t->leftist_ = element;
		t->rightist_ = element;

		if (t->psh_ != 0) {
			throw 1;
		}

		recalc(t);
		return t;
	}

	int sum(SplayTree *&t, int left, int right) {
		SplayTree *l = NULL, *m = NULL, *r = NULL;
		split(t, right + 1, l, r);
		split(l, left, l, m);

		int answer = sum(m);

		t = merge(merge(l, m), r);

		return answer;
	}

	SplayTree* addingOnSegment(SplayTree *t, int left, int right, int element) {
		SplayTree *l = NULL, *m = NULL, *r = NULL;
		split(t, right + 1, l, r);
		split(l, left, l, m);

		sets(m, element);

		return merge(merge(l, m), r);
	}

	SplayTree* reverse(SplayTree *t, int left, int right) {
		SplayTree *l = NULL, *m = NULL, *r = NULL;
		split(t, right + 1, l, r);
		split(l, left, l, m);

		setsFlag(m);

		return merge(merge(l, m), r);
	}

	SplayTree* upperBound(SplayTree *t, int elem) {
		push(t);
		if (t->right_ == NULL) {
			if (t->key_ > elem) {
				return t;
			}
			else {
				return upperBound(t->left_, elem);
			}
		}
		else if (t->right_->leftist_ > elem) {
			return upperBound(t->right_, elem);
		}
		else if (t->key_ > elem) {
			return t;
		}
		else {
			return upperBound(t->left_, elem);
		}
	}

	SplayTree* nextPermutation(SplayTree *t) {
		if (getSize(t) == sizeRight(t)) {
			setsFlag(t);
			return t;
		}

		SplayTree *l = NULL, *m = NULL, *r = NULL;

		split(t, getSize(t) - sizeRight(t) - 1, l, r);
		split(r, 1, m, r);

		if (sizeRight(r) != getSize(r)) {
			throw 1;
		}

		if (getSize(m) != 1) {
			throw 1;
		}

		r = upperBound(r, m->key_);
		splay(r);

		swap(m->key_, r->key_);
		recalc(m);
		recalc(r);
		setsFlag(r);

		return merge(merge(l, m), r);
	}

	SplayTree* nextPermutation(SplayTree *t, int left, int right) {
		SplayTree *l = NULL, *m = NULL, *r = NULL;
		split(t, right + 1, l, r);
		split(l, left, l, m);

		m = nextPermutation(m);

		return merge(merge(l, m), r);
	}

	int leftist(SplayTree *&t, int left, int right) {
		SplayTree *l = NULL, *m = NULL, *r = NULL;
		split(t, right + 1, l, r);
		split(l, left, l, m);

		int answer = m->leftist_;

		t = merge(merge(l, m), r);

		return answer;
	}

	int rightist(SplayTree *&t, int left, int right) {
		SplayTree *l = NULL, *m = NULL, *r = NULL;
		split(t, right + 1, l, r);
		split(l, left, l, m);

		int answer = m->rightist_;

		t = merge(merge(l, m), r);

		return answer;
	}

	void write(SplayTree *t) {
		if (t == NULL) {
			return;
		}
		push(t);

		write(t->left_);
		cout << t->key_ << "\n";
		write(t->right_);
	}
};
