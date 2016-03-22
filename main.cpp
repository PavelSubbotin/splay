#include "ialgo.h"
#include "splay.h"
#include "tester.h"



int main() {

	UnRandomTree hard;
	SimpleRealization simple;
	checker(generateFirstTest(10000, 100), &hard, &simple);
	hard = UnRandomTree();
	simple = SimpleRealization();
	checker(genLittleTest(10000, 100), &hard, &simple);


	return 0;
}
