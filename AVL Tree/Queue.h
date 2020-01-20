#pragma once
#include <string>
#include <iostream>
#include <cstddef>
#include <fstream>

using namespace std;

template<typename Q>
class Queue
{
public:
	struct Node {
		Q item;
		Node* next;
		Node* prev;
	};

	Node* head;
	Node* tail;
	int size; //Size of List

	Queue() {
		head = NULL;
		tail = NULL;
		size = 0;
	}

	Q front()
	{
		return head->item;
	}

	Q pop()
	{
		if (head == NULL)
			return Q();
		Q item;
			item = head->item;
			Node* temp = head;
			head = head->next;
			if (head == NULL)
				tail = NULL;
			else
				head->prev = NULL;
			delete temp; //Destroys object pointed to by temp
		
		size--;
		return item;
	}


	void insert(const Q& item)
	{
		Node* n = new Node();
		n->item = item;
		if (head == NULL) {
			head = n;
			tail = n;
		}
		else {
			tail->next = n;
			n->prev = tail;
			tail = n;
		}
		size++;
	}

	~Queue()
	{
		Node* temp = head;
		while (temp != NULL && size > 0) {
			Node* temp = head;
			head = head->next;
			delete temp;
			size--;
		}
		tail = NULL;
	}
};

