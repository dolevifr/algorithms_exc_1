#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_
#include "general.h"

// generic priority queue ADT, implemented with binary heap 
// a function for comparing nodes and updating key can be specified when initializing an instance
// otherwise default functions will be used
template <typename T>
class Priority_Queue {
	typedef std::function<bool(const T&, const T&)>	Comparator;
	typedef std::function<void(T&, int)>			UpdateKey;
	typedef std::function<void(T&, T&)>				Upkeep;

private:
	std::vector<T>	arr;
	UpdateKey		updateKey;
	Comparator		compare;
	Upkeep			upkeep;
	size_t			arrSize;

	static size_t parent(size_t ind) { return (ind - 1) / 2; };
	static size_t left(size_t ind) { return (2 * ind + 1); };
	static size_t right(size_t ind) { return (2 * ind + 2); };

	void fixHeap(size_t node);
	T remove(size_t node);
	
public:
	Priority_Queue(
		const Comparator& compareFunction = [](const T& left, const T& right) { return left < right; },
		const UpdateKey& updateKeyFunction = [](T& item, int newKey) { item = newKey; },
		const Upkeep& upkeepFunction = [](T& item1, T& item2) {}
		) : arrSize(0), compare(compareFunction), updateKey(updateKeyFunction), upkeep(upkeepFunction) {};

	~Priority_Queue() {};

	void fixUpwards(size_t index, int newKey);
	void build(std::vector<T> toBuild);
	bool isEmpty() const;
	T deleteRoot();
};

// bubbles node at index given upwards
template <typename T>
void Priority_Queue<T>::fixUpwards(size_t index, int newKey) {
	size_t i = index;

	T item = arr[i];
	updateKey(arr[i], newKey);

	while (i > 0 && compare(arr[i], arr[parent(i)])) {
		upkeep(arr[i], arr[parent(i)]);
		std::swap(arr[i], arr[parent(i)]);
		i = parent(i);
	};
}


template <typename T>
void Priority_Queue<T>::fixHeap(size_t node) {
	size_t max;
	size_t lft = left(node);
	size_t rght = right(node);

	if ((lft < arrSize) && compare(arr[lft], arr[node])) 
		max = lft;
	else 
		max = node;
	
	if ((rght < arrSize) && compare(arr[rght], arr[max])) 
		max = rght;

	if (max != node) {
		std::swap(arr[node], arr[max]);
		upkeep(arr[node], arr[max]);
		fixHeap(max);
	}
}

// deletes node at specified index
template <typename T>
T Priority_Queue<T>::remove(size_t node) {
	if (isEmpty())
		throw std::runtime_error("heap is empty, no items to remove");

	T root = arr[node];

	arrSize--;
	upkeep(arr[node], arr[arrSize]);
	arr[node] = arr[arrSize];
	arr.pop_back();
	fixHeap(node);

	return root;
}


template <typename T>
T Priority_Queue<T>::deleteRoot() {
	return remove(0);
}


template <typename T>
bool Priority_Queue<T>::isEmpty() const {
	return arrSize == 0;
};

// creates a priority queue for a vector 
template <typename T>
void Priority_Queue<T>::build(std::vector<T> toBuild) {
	if (!isEmpty())
		throw std::runtime_error("build can only be used on an empty queue");

	arr = toBuild;
	arrSize = toBuild.size();

	for (int i = arrSize / 2; i >= 0; i--)
		fixHeap(i);
}
#endif