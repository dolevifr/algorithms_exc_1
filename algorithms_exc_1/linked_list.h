#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_
#include "general.h"

// linked list class, with iterator
template<typename T>
class Linked_List {
private:
	struct Node {
		Node*	next;
		Node*	prev;
		T		data;

		Node(const T& data) : data(data), next(nullptr), prev(nullptr) {};
		~Node() { delete next; };
	};

	Node* head;
	Node* tail;

	bool isEmpty() { return !head; }

public:
	Linked_List() : head(nullptr), tail(nullptr) {}
	~Linked_List() { delete head; };

	class Iterator {
	private:
		friend class Linked_List<T>;
		Node* node;

	public:
		Iterator(Node* node = nullptr) : node(node) {};
		Node* getItem() const { return node;};

		Iterator operator++() {
			node = node->next;
			return *this;
		}
		Iterator operator--() {
			node = node->prev;
			return *this;
		}
		int operator!=(Iterator iter) {
			return node != iter.node;
		}

		T& operator*() {
			return node->data;
		}
	};
	Iterator begin() { return head; }
	Iterator end() { return tail->next; }

	T& getTail() { return tail->data; };
	T& getHead() { return head->data; };
	void append(const T& data);
	void remove(Node* node);
};

// a vertex is a linked list of edges, in an adjacency list implementation of graph
typedef Linked_List<Edge> Vertex;


template<typename T>
void Linked_List<T>::append(const T& data) {
	Node* node = new Node(data);

	if (isEmpty())
		head = tail = node;

	else {
		tail->next = node;
		node->prev = tail;
		tail = tail->next;
	}
}


template<typename T>
void Linked_List<T>::remove(Node* node) {
	Node* next = node->next;
	Node* prev = node->prev;

	if (prev)
		prev->next = next;
	else
		head = next;

	if (next)
		next->prev = prev;
	else
		tail = prev;

	delete node;
}
#endif