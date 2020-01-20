#include "HashSet.h"

using namespace std;



template <typename H>
class HashSet
{
public:
	int tableSize; //Current Size of Array
	int size; //COUNT
	List<H>* table;
	HashSet()
	{
		table = NULL;
		tableSize = 0;
		size = 0;
	}

	int RehashLarge()
	{
		int new_size = tableSize * 2 + 1;
		//REMOVE, MAYBE CALL LIST.CLEAR AFTER REHASHING?
		//NEW TABLE
		List<H>* new_table = new List<H>[new_size];
		
		for (auto i = 0; i < tableSize; i++) //STILL O(n) // ONLY GOING THROUGH WHAT'S NECESSARY
		{
			//if (table[i] != NULL) //THAT MIGHT BE WRONG
			{
				int perm_size = table[i].size;
				for (auto j = 0; j < perm_size; j++)
				{
					H item = table[i].pop();
					unsigned int index = hashCode(item, new_size);
					new_table[index].insert(item);
				}
				table[i].clear(); //MIGHT BE UNNECESSARY
			}
		}
		//DELETE OLD TABLE
		delete[] table;
		table = new_table;

		return new_size;
	}

	int RehashSmall()
	{
		int new_size = tableSize/2;
		if (new_size == 0) //TABLE IS EMPTY
		{
			delete[] table;
			table = NULL;
			table = 0;
			return 0;
		}
		List<H>* new_table = new List<H>[new_size];
		for (auto i = 0; i < tableSize; i++) //STILL O(n) // ONLY GOING THROUGH WHAT'S NECESSARY
		{
			//if (table[i] != NULL) //THAT MIGHT BE WRONG
			{
				int perm_size = table[i].size;
				for (auto j = 0; j < perm_size; j++)
				{
					H item = table[i].pop();
					unsigned int index = hashCode(item, new_size);
					new_table[index].insert(item);
				}
				table[i].clear(); //MIGHT BE UNNECESSARY
			}
		}
		//DELETE OLD TABLE
		delete[] table;
		tableSize = new_size;
		table = new_table;

		return new_size;
	}
	
	void add(const H& item) { //0 thru table.size() - 1
		//if //table is NULL
		if (table == NULL) {
			tableSize++;
			table = new List<H>[tableSize];
		}
		else if (size == tableSize)
		{
			unsigned int index = hashCode(item, tableSize);
			if (table[index].find(item) == -1)
				tableSize = RehashLarge(); //DO I NEED ANYTHING ELSE?
		}

		unsigned int index = hashCode(item, tableSize);
		if (table[index].find(item) == -1) //WE GOOD
		{
			table[index].insert(item);
			size++;
		}
		//delete[] table;
		//tableSize = new_size;
		//table = new_table;
	}

	void remove(const H& item)
	{
		if (table == NULL)
			return;

		int index = hashCode(item, tableSize);
		if (tableSize == 0 || size == 0) //There's nothing there, BUT EVALUATE CODE LATER
			//IF STATEMENT: MIGHT WANT TO REDUCE CONDITIONS FOR COMPLEXITY
			return;
		else if (table[index].find(item) != -1)
		{
			table[index].remove(item);
			size--;
		}

		//IS IT RIGHT?
		if (size == tableSize / 2)  //IT SHOULD BE THE LAST STATEMENT
			tableSize = RehashSmall();
	}

	unsigned int hashCode(const string& str, int tableSize)
	{
		const int PRIME = 31; //IT WAS DOUBLE
		unsigned int index = 0;
		for (auto &c : str) {
			index *= PRIME;
			index += int(c);
		}
		return index % tableSize;
	}

	bool find(const H& item)
	{
		if (table == NULL)
			return false;
		unsigned int index = hashCode(item, tableSize);
		int found = table[index].find(item);
		if (found != -1)
			return true;
		return false;
	}

	void print(ofstream& out)
	{
		out << "print" << endl;
		if (table == NULL)
			return;
		for (auto i = 0; i < tableSize; i++) //STILL O(n) // ONLY GOING THROUGH WHAT'S NECESSARY
		{
			out << "hash " << i << ":";
			//if (table[i] != NULL) //THAT MIGHT BE WRONG
			{
				table[i].print(out, i);
			}
			out << endl;
		}
	}

	void clear()
	{
		if (table == NULL)
			return;
		for (auto i = 0; i < tableSize; i++) //STILL O(n) // ONLY GOING THROUGH WHAT'S NECESSARY
		{
			//if (table[i] != NULL) //THAT MIGHT BE WRONG
			{
				table[i].clear(); //MIGHT BE UNNECESSARY
			}
		}
		delete[] table;
		table = NULL;
		size = 0;
		tableSize = 0;
	}

	~HashSet()
	{
		clear();
	}

};

