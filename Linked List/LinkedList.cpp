#include "LinkedList.h"

using namespace std;

template<typename L>
class LinkedList
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

	LinkedList() {
		this->head = head;
		this->tail = tail;
		this->size = size;
	}

	L remove(int index)
	{
		if (head == NULL || index >= size)
			return "";
		L item;
		if (index == 0)
		{
			item = head->item;
			Node* temp = head;
			head = head->next;
			if (head == NULL)
				tail = NULL;
			else
				head->prev = NULL;
			delete temp; //Destroys object pointed to by temp
		}
		else if (index == (size - 1))
		{
			item = tail->item;
			Node* temp = tail;
			tail = tail->prev;
			delete temp;
			if (tail != NULL) //DO I NEED AN ELSE? BOOK
				tail->next = NULL;
		}
		else
		{
			RemMiddle(index, item);
		}

		size--;
		return item;
	}

	void AddMiddle(int index, Node* n, Node* temp)
	{
		if (index <= (size / 2))
		{
			Node* temp = head->next;
			//Or int i = 1; i < index
			for (int i = 2; i <= index; i++)
			{
				temp = temp->next;
			}

			temp->prev->next = n;
			n->prev = temp->prev;
			n->next = temp;
			temp->prev = n;
		}
		else
		{
			Node* temp = tail->prev;
			for (int i = (size - 2); i >= index; i--) //-3
			{
				temp = temp->prev;
			}
			temp->next->prev = n;
			n->prev = temp;
			n->next = temp->next;
			temp->next = n;
		}
	}
	void RemMiddle(int index, L& item)
	{
		if (index <= (size / 2))
		{
			Node* temp = head->next;
			//item = head->next->item;
			for (int i = 1; i < index; i++)
			{
				temp = temp->next;
			}
			item = temp->item;
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			delete temp;
		}
		else
		{
			Node* temp = tail->prev;
			for (int i = (size - 3); i >= index; i--)
			{
				temp = temp->prev;
			}
			item = temp->item;
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			delete temp;
		}
	}

	void insert(int index, const L& item)
	{
		if (index > size)
			return;

		Node* n = new Node();
		n->item = item;
		if (head == NULL) {
			head = n;
			tail = n;
		}
		else if (index == 0)
		{
			n->next = head;
			head->prev = n;
			head = n;
		}
		else if (index == size && size != 0) {
			tail->next = n;
			n->prev = tail;
			//n->next = NULL;
			tail = n;
		}
		else
		{
			Node* temp = NULL;
			AddMiddle(index, n, temp);
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

	void print(ofstream& out)
	{
		int i = 0;
		out << "print" << endl;
		Node* temp = head;
		while (temp != NULL) {
			out << "node " << i << ": " << temp->item << endl;
			i++;
			temp = temp->next;
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

	~LinkedList()
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

