#include "disjoint_sets.h"


void Disjoint_Sets::makeSet(int x) {
	if (isSet(x))
		throw std::invalid_argument("element already in a set");

	arr[x].parent = x;
	arr[x].size = 1;
}

int Disjoint_Sets::find(int x) {
	if (!isSet(x))
		throw std::invalid_argument("element is not part of a set");

	if (arr[x].parent == x)
		return x;
	else
		return arr[x].parent = find(arr[x].parent);
}

void Disjoint_Sets::Union(int repx, int repy) {
	if (!isRep(repx) || !isRep(repy))
		throw std::invalid_argument("one of the elements to union is not a rep of its set");

	if (arr[repx].size >= arr[repy].size) {
		arr[repy].parent = repx;
		arr[repx].size += arr[repy].size;
	}
	else {
		arr[repx].parent = repy;
		arr[repy].size += arr[repx].size;
	}
}