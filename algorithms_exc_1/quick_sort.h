#ifndef _QUICK_SORT_H_
#define _QUICK_SORT_H_
#include "general.h"

// a generic class for quick sort, a custom compare function for T must be provided
template<typename T>
class Quick_Sort {
private:
	std::function<bool(const T&, const T&)> compare;

	int partition(std::vector<T>& arr, int left, int right) {
		T& pivot = arr[right];
		int partitionInd = left;

		for (int i = left; i <= right; i++) {
			if (compare(arr[i], pivot)) {
				std::swap(arr[partitionInd], arr[i]);
				partitionInd++;
			}
		}

		std::swap(arr[partitionInd], arr[right]);
		return partitionInd;
	}

	void quickSort(std::vector<T>& arr, int left, int right) {
		int pivot;

		if (left < right) {
			pivot = partition(arr, left, right);
			quickSort(arr, left, pivot - 1);
			quickSort(arr, pivot + 1, right);
		}
	}

public:
	Quick_Sort<T>(std::function<bool(const T&, const T&)> compareFunc) : compare(compareFunc) {};

	void operator()(std::vector<T>& arr) {
		quickSort(arr, 0, arr.size() - 1);
	}
};

// specific instance of quick sort for sorting pointers of Edge
struct Edge_Quick_Sort : public Quick_Sort<Edge*> {
	Edge_Quick_Sort() : Quick_Sort(
		[](const Edge* edge1, const Edge* edge2) { return edge1->weight < edge2->weight; })
	{};
};
#endif