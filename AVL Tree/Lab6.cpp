#include "Tree.h"
#include <iostream>
#include <string>
#include <cstddef>
#include <fstream>
#include <sstream>


using namespace std;

int main(int argc, const char* argv[])
{
	Tree<string> AVL;
	AVL.root = NULL;
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
			AVL.add(word, AVL.root);
			out << text << endl;
		}
		else if (word == "clear")
		{
			AVL.clear(AVL.root);
			out << text << endl;
		}
		else if (word == "remove")
		{
			sentence >> word;
			AVL.remove(word, AVL.root, out);
			//AVL.root = AVL.RemSet(AVL.root, out);
			out << text << endl;
		}
		else if (word == "find")
		{
			sentence >> word;
			int index = AVL.find(word, AVL.root);
			string is_true = "false";
			if (index)
				is_true = "true";
			out << text << " " << is_true << endl;
		}
		else if (word == "print")
		{
			AVL.print(out);
		}
	}
	in.close();
	out.close();
	
    return 0;
}

