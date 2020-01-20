#include <iostream>
#include <string>
#include "LinkedList.h"
#include <cstddef>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, const char* argv[])
{
	LinkedList<string> List;
	List.head = NULL;
	List.tail = NULL;
	List.size = 0;

	string command_text = argv[1];
	string output_text = argv[2];

	//string command_text = "command.txt";
	//string output_text = "output.txt";
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
		if (word == "insert")
		{
			sentence >> word;
			int index = stoi(word);
			sentence >> word;
			List.insert(index, word);
			out << text << endl;
		}
		else if (word == "clear")
		{
			List.clear();
			out << text << endl;
		}
		else if (word == "remove")
		{
			sentence >> word;
			int index = stoi(word);
			string off = List.remove(index);
			out << text << " " << off << endl;
		}
		else if (word == "find")
		{
			sentence >> word;
			int index = List.find(word);
			out << text << " " << index << endl;
		}
		else if (word == "print")
		{
			List.print(out);
		}
	}
	in.close();
	out.close();


	

	return 0;
}
