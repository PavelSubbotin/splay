#define _CRT_SECURE_NO_WARNINGS

#pragma once



#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <assert.h>
#include "ialgo.h"


using namespace std;

int rand(int a)
{
	return rand() % a;
}

void myException(bool a, string s)
{
	assert(a);
}

string generateFirstTest(size_t numberOfOperation, size_t range)
{
	FILE *stream;
	freopen_s(&stream, "FirstTest.txt", "w", stdout);
	size_t supportSize = 0;
	for (int i = 0; i < numberOfOperation; ++i)
	{
		int randomValue = rand() % 5;
		switch (randomValue)
		{
		case 0:
			if (supportSize) {
				int r = rand(supportSize) + 1;
				printf("sum %d %d\n", rand(r), r);
			}
			break;
		case 1:
			printf("insert %d %d\n", rand(range), rand(supportSize + 1));
			++supportSize;
			break;
		case 2:
			if (supportSize) {
				printf("changeElement %d %d\n", rand(range), rand(supportSize));
			}
			break;
		case 3:
			if (supportSize)
			{
				int r = rand(supportSize) + 1;
				printf("addingOnSegment %d %d %d\n", rand(range), rand(r), r);
			}
			break;
		case 4:
			if (supportSize)
			{
				int r = rand(supportSize) + 1;
				printf("nextPermutation %d %d\n", rand(r), r);
			}
			break;
		case 5:
			printf("size %d\n", supportSize);
			break;
		}
	}
	return "FirstTest.txt";
}

string genLittleTest(size_t numberOfOperation, size_t range) {
	FILE *stream;
	freopen_s(&stream, "testLittle.txt", "w", stdout); 
	size_t supportSize = 0;
	int starterSize = sqrt(numberOfOperation);
	for (int i = 0; i < starterSize; ++i)
	{
		printf("insert %d %d\n", i, i);
		++supportSize;
	}

	for (int i = 0; i < supportSize; ++i)
	{
		printf("sum %d %d\n", i, supportSize);
	}
	for (int i = 0; i < supportSize; ++i)
	{
		printf("changeElement %d %d\n", i * i, supportSize - i - 1);
	}
	for (int i = 0; i < supportSize; ++i)
	{
		printf("addingOnSegment %d %d %d\n", i * i, i, supportSize);
	}
	return "testLittle.txt";
}



void checker(string fileFrom, IAlgo* simple, IAlgo* hard)
{
	FILE *stream;
	freopen_s(&stream, fileFrom.c_str(), "r", stdin);

	string s;
	while (cin >> s)
	{
		if (s == "sum")
		{
			int a, b;
			cin >> a >> b;
			myException(simple->sum(a, b) == hard->sum(a, b), s);
		}
		else if (s == "insert")
		{
			int a, b;
			cin >> a >> b;
			simple->insert(a, b);
			hard->insert(a, b);
		}
		else if (s == "changeElement")
		{
			int a, b;
			cin >> a >> b;
			simple->changeElement(a, b);
			hard->changeElement(a, b);
		}
		else if (s == "addingOnSegment")
		{
			int a, b, c;
			cin >> a >> b >> c;
			simple->addingOnSegment(a, b, c);
			hard->addingOnSegment(a, b, c);
		}
		else if (s == "nextPermutation")
		{
			int a, b;
			cin >> a >> b;
			simple->nextPermutation(a, b);
			hard->nextPermutation(a, b);
		}
		else if (s == "size")
		{
			int a;
			cin >> a;
			//myException(simple->size() == a, s);
		}
		//myException(simple->size() == hard->size(), s);
	}



}