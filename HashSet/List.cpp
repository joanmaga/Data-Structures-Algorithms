#include "List.h"

using namespace std;

template<typename L>
class List
{
public:
	struct Node {
		L item;
		Node* next;
		Node* prev;
	};

	Node* head;
	Node* tail;
	int size; //Size of List

	List() {
		head = NULL;
		tail = NULL;
		size = 0;
	}

	L front()
	{
		return head->item;
	}

	L pop()
	{
		if (head == NULL)
			return L();
		L item;
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

	void remove(L item) //SHOULD WORK BUT WATCH OUT
	{
		if (head == NULL)
			return;
		
		if (item == head->item) {
			Node* temp = head;
			head = head->next;
			if (head == NULL)
				tail = NULL;
			else
				head->prev = NULL;
			delete temp;
		}
		else if (item == tail->item)
		{
			Node* temp = tail;
			tail = tail->prev;
			delete temp;
			if (tail != NULL) //DO I NEED AN ELSE? BOOK
				tail->next = NULL;
		}
		else
		{
			Node* temp = head->next;
			for (int i = 1; i < size; i++)
			{
				if (item == temp->item)
				{
					temp->prev->next = temp->next;
					temp->next->prev = temp->prev;
					delete temp;
					break;
				}
				else
					temp = temp->next;
			}
		}

		size--;
		/*if (head == NULL)
			tail = NULL;
		else
			head->prev = NULL;*/
	}


	void insert(const L& item)
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

	int find(const L& item)
	{
		int count = 0;
		Node* temp = head;
		if (head != NULL) {
			if (item == head->item)
				return count;
			count++;
			temp = temp->next;
			while (temp != NULL)
			{
				if (item == temp->item)
					return count;
				count++;
				temp = temp->next;
			}
		}

		return -1;
	}

	void print(ofstream& out, int i)
	{
		int const MAX = 8;
		Node* temp = head;
		int max = 0;
		while (temp != NULL) {
			if (max == MAX) { //IS IT RIGHT?
				out << endl;
				out << "hash " << i << ":";
				max = 0;
			}
			out << " " << temp->item;
			temp = temp->next;
			max++;
		}
	}

	void clear()
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

	~List()
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


