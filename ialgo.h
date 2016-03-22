#pragma once

#include <numeric>
#include <vector>
#include <algorithm>
#include "splay.h"

using std::vector;


class IAlgo {
public:
	virtual void insert(int, int) = 0;
	virtual void changeElement(int, int) = 0;
	virtual int sum(int, int) = 0;
	virtual void addingOnSegment(int, int, int) = 0;
	virtual void reverse(int, int) = 0;
	virtual void nextPermutation(int, int) = 0;
};

class UnRandomTree : public IAlgo {
private:
	SplayTree *root_;
public:
	UnRandomTree() :
		root_(NULL)
	{}

	UnRandomTree(SplayTree *root) :
		root_(root)
	{}

	void insert(int position, int element) {
		root_ = root_->insert(root_, position, element);
	}

	void changeElement(int position, int element) {
		root_ = root_->changeElement(root_, position, element);
	}

	int sum(int left, int right) {
		return root_->sum(root_, left, right);
	}

	void addingOnSegment(int left, int right, int element) {
		root_ = root_->addingOnSegment(root_, left, right, element);
	}

	void reverse(int left, int right) {
		root_ = root_->reverse(root_, left, right);
	}

	void nextPermutation(int left, int right) {
		root_ = root_->nextPermutation(root_, left, right);
	}

	void write() {
		root_->write(root_);
	}
};

class SimpleRealization : public IAlgo {
private:
	vector <int> tmp;
public:
	void insert(int position, int element) {
		tmp.insert(tmp.begin() + position, element);
	}

	void changeElement(int position, int element) {
		tmp[position] = element;
	}

	int sum(int left, int right) {
		return std::accumulate(tmp.begin() + left, tmp.begin() + right + 1, (int)0);
	}

	void addingOnSegment(int left, int right, int element) {
		std::transform(tmp.begin() + left, tmp.begin() + right + 1,
			tmp.begin() + left,
			[element](int elem) {
			return elem + element;
		});
	}

	void reverse(int left, int right) {
		std::reverse(tmp.begin() + left, tmp.begin() + right + 1);
	}

	void nextPermutation(int left, int right) {
		next_permutation(tmp.begin() + left, tmp.begin() + right + 1);
	}
};