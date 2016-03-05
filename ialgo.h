#pragma once

#include <vector>
#include <numeric>
#include "splaytree.h"

using std::vector;

class IAlgo {
public:
	virtual void insert(int, int) = 0;
	virtual void changeElement(int, int) = 0;
	virtual int sum(int, int) = 0;
	virtual void addingOnSegment(int, int, int) = 0;
	virtual void reverse(int, int) = 0;
	virtual void nextPermutation(int, int) = 0;
	virtual size_t size() = 0;
};

class GoodRealization : public IAlgo {
private:
	SplayTree *root_;
public:
	GoodRealization() :
		root_(NULL)
	{}

	GoodRealization(SplayTree *root) :
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
		root_ = root_->changeSegment(root_, left, right, element);
	}

	void reverse(int left, int right) {
		root_ = root_->reverse(root_, left, right);
	}

	void nextPermutation(int left, int right) {
		root_ = root_->nextPermutation(root_, left, right);
	}

	size_t size()
	{
		return root_->getSize(root_);
	}
};

class SimpleRealization : public IAlgo {
private:
	vector <int> tmp;
public:
	void insert(int element ,int position) {
		tmp.insert(tmp.begin() + position, element);
	}

	void changeElement(int element, int position) {
		tmp[position] = element;
	}

	int sum(int left, int right) {
		return std::accumulate(tmp.begin() + left, tmp.begin() + right + 1, (int)0);
	}

	void addingOnSegment(int element, int left, int right) {
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
	size_t size()
	{
		return tmp.size();
	}
};
