#include <iostream>
#include <string>
#include "HashSet.h"
#include "List.h"
#include <cstddef>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, const char* argv[])
{
	/*cout << int('b') << endl;
	cout << int('o') << endl;
	string car = "bob";
	HashSet<string> hash;
	const int PRIME = 31; //CHANGED FROM DOUBLE
	int index = 0;
	for (auto &c : car) {
		index *= PRIME;
		index += int(c);
	}
	hash.table[index].size;
	cout << index << endl;
	cout << index % 3 << endl;*/
	
	HashSet<string> hash;
	string command_text = argv[1];
	string output_text = argv[2];

	string text;

	ifstream in;
	ofstream out;

	//READ
	in.open(command_text);
	out.open(output_text);
	while (in.good())
	{
		stringstream sentence;
		string word;
		getline(in, text);
		sentence << text;
		sentence >> word;
		if (word == "add")
		{
			sentence >> word;
			hash.add(word);
			out << text << endl;
		}
		else if (word == "clear")
		{
			hash.clear();
			out << text << endl;
		}
		else if (word == "remove")
		{
			sentence >> word;
			hash.remove(word);
			out << text << endl;
		}
		else if (word == "find")
		{
			sentence >> word;
			int index = hash.find(word);
			string is_true = "false";
			if (index)
				is_true = "true";
			out << text << " " << is_true << endl;
		}
		else if (word == "print")
		{
			hash.print(out);
		}
	}
	in.close();
	out.close();

    return 0;
}

