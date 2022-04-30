#ifndef _UNION_FIND_H_
#define _UNION_FIND_H_
#include "general.h"


class Disjoint_Sets {
private:
	struct Element {
		int parent;
		int size;

		Element() : parent(-1), size(0) {};
	};

	Element* arr;

	bool isRep(int x) { return arr[x].parent == x; };
	bool isSet(int x) { return arr[x].parent != -1; };

public:
	Disjoint_Sets(size_t num) : arr(new Element[num + 1]) {};
	~Disjoint_Sets() { delete arr; };

	void Union(int repx, int repy);
	void makeSet(int x);
	int find(int x);
};
#endif