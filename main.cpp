#include "tester.h"


int main() {
	
	SimpleRealization vect;
	GoodRealization tree;
	
	checker(generateFirstTest(30, 10), &vect, &tree);
	//generateFirstTest(30, 10);

	return 0;
}
