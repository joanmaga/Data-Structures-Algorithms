#pragma once
#include <cstddef>
#include "Queue.h"
#include <iostream>

using namespace std;

template<typename A>
class Tree
{
public:
	
	struct Node {
		A item;
		int height;
		Node* left;
		Node* right;
	};

	Node* root;
	int count = 0;
	

	Tree() {
		this->root = root;
	}

	void SetHeight(Node* root, int& h_left, int& h_right)
	{
		//IsNull
		
		if (root->left == NULL)
			h_left = 0;
		else
			h_left = root->left->height;
		if (root->right == NULL)
			h_right = 0;
		else
			h_right = root->right->height;
	}

	/*void RemSetHeight(Node* root, int& h_left, int& h_right)
	{
		//IsNull
		//RETURN MAYBE?
		if (root == NULL) { //THIS WAS ADDED
			h_left = 0;
			h_right = 0;
			return;
		}
		
		if (root->left == NULL)
			h_left = 0;
		else
			h_left = root->left->height;
		if (root->right == NULL)
			h_right = 0;
		else
			h_right = root->right->height;
		//NEW
		if (root->left == NULL && root->right == NULL && root->height > 1) //ADDED
			root->height--;
		else if (root->left != NULL && (h_left >= h_right) && (root->height - root->left->height) > 1)
			root->height--;
		else if (root->right != NULL && (h_right >= h_left) && (root->height - root->right->height) > 1)
			root->height--;
		//TILL THIS POINT
	}*/

	void Balance(Node*& root)
	{
		int h_left = 0;
		int h_right = 0;

		SetHeight(root, h_left, h_right);
		if ((h_left - h_right) > 1) {
			int h_left_left = 0, h_left_right = 0;
			SetHeight(root->left, h_left_left, h_left_right);
			//LL
			if (h_left_left > h_left_right)
			{
				Node* temp = root->left; //SAME
				root->left = temp->right; //SAME
				temp->right = root;
				root = temp;
				root->right->height -= 2;
			}
			//LR
			else if (h_left_left < h_left_right)
			{
				Node* temp = root->left;
				root->left = temp->right;
				//FIGURE OUT OR *ITEM DISAPPEARS
				temp->right = temp->right->left; //NOT RIGHT FOR SOME REASON
				root->left->left = temp;
				//temp->right->left = temp;
				//temp->right = NULL;
				temp = root->left;
				root->left = temp->right;
				temp->right = root;
				root = temp;
				root->right->height -= 2;
				root->height++;
				root->left->height--;
			}
		}
		else if ((h_right - h_left) > 1) {
			int h_right_left = 0, h_right_right = 0;
			SetHeight(root->right, h_right_left, h_right_right);
			//RR
			if (h_right_right > h_right_left)
			{
				Node* temp = root->right; //SAME
				root->right = temp->left; //SAME
				temp->left = root;
				root = temp;
				root->left->height -= 2;
			}
			//RL
			else if (h_right_right < h_right_left)
			{
				Node* temp = root->right;
				root->right = temp->left;
				//FIGURE OUT OR *ITEM DISAPPEARS
				temp->left = temp->left->right; //NOT RIGHT FOR SOME REASON
				root->right->right = temp;
				temp = root->right;
				root->right = temp->left;
				temp->left = root;
				root = temp;
				root->left->height -= 2;
				root->height++;
				root->right->height--;
			}
		}
	}

	/*void RemBalance(Node*& root)
	{
		int h_left = 0;
		int h_right = 0;
		
		RemSetHeight(root, h_left, h_right);
		if ((h_left - h_right) > 1) {
			int h_left_left = 0, h_left_right = 0;
			RemSetHeight(root->left, h_left_left, h_left_right);
			//LL
			if (h_left_left > h_left_right)
			{
				Node* temp = root->left; //SAME
				root->left = temp->right; //SAME
				temp->right = root;
				root = temp;
				root->right->height -= 2;
			}
			//LR
			else if (h_left_left < h_left_right)
			{
				Node* temp = root->left;
				root->left = temp->right;
				//FIGURE OUT OR *ITEM DISAPPEARS
				temp->right = temp->right->left; //NOT RIGHT FOR SOME REASON
				root->left->left = temp;
				//temp->right->left = temp;
				//temp->right = NULL;
				temp = root->left;
				root->left = temp->right;
				temp->right = root;
				root = temp;
				root->right->height -= 2;
				root->height++;
				root->left->height--;
			}
		}
		else if ((h_right - h_left) > 1) {
			int h_right_left = 0, h_right_right = 0;
			RemSetHeight(root->right, h_right_left, h_right_right);
			//RR
			if (h_right_right > h_right_left)
			{
				Node* temp = root->right; //SAME
				root->right = temp->left; //SAME
				temp->left = root;
				root = temp;
				root->left->height -= 2;
			}
			//RL
			else if (h_right_right < h_right_left)
			{
				Node* temp = root->right;
				root->right = temp->left;
				//FIGURE OUT OR *ITEM DISAPPEARS
				temp->left = temp->left->right; //NOT RIGHT FOR SOME REASON
				root->right->right = temp;
				temp = root->right;
				root->right = temp->left;
				temp->left = root;
				root = temp;
				root->left->height -= 2;
				root->height++;
				root->right->height--;
			}
		}
	}*/

	void add(const A& item, Node*& root) //Root is LOCAL Root
	{
		if (root == NULL)
		{
			//Is it Necessary
			Node* n = new Node();
			root = n;
			root->height = 0;
			n->item = item;
			//root = n;
			root->left = NULL;
			root->right = NULL;
			root->height++; //MAKE SURE TO INITIALIZE
			count++;
			//return; //DO I NEED THIS? We might bc of the Balance Function, 
					//we don't wanna run it in this node;
		}
		else {
			if (item == root->item)
				return; //Item already exists in Tree
			if (item < root->item)
			{
				add(item, root->left);
				if (root->left->height == root->height) //Shouldn't have access violation, bc there will be a value for height
					root->height++;
			}
			else if (item > root->item)
			{
				add(item, root->right);
				if (root->right->height == root->height)
					root->height++;
			}
			
			//BALANCE
			Balance(root);
			
		}
		
	}



	Node* remove(const A& item, Node*& root, ofstream& out)
	{
		if (root == NULL)
			return root;
		else if (item < root->item)
			root->left = remove(item, root->left, out);
		else if (item > root->item)
			root->right = remove(item, root->right, out);
		else {
			if (root->left == NULL || root->right == NULL)
			{
				Node* old_root = root->left ? root->left : root->right;
				if (old_root == NULL) {
					old_root = root;
					root = NULL;
					delete old_root;
				}
				else {
					delete root;
					root = old_root;
				}
			}
			else {
				Node* old_root = getSmall(root->right);
				root->item = old_root->item;
				root->height = maxHeight(height(root->left) + 1, height(old_root));
				root->right = remove(old_root->item, root->right, out);
			}
		}

		if (root != NULL) {
			root->height = maxHeight(height(root->left), height(root->right)) + 1;
			root = RemSet(root, out);
		}

		return root;
	}

	Node* RemSet(Node*& root, ofstream& out)
	{
		if (root == NULL)
			return root;
		int bal = RemBalance(root);
		if (bal > 1 && RemBalance(root->left) >= 0) {
			//out << "OPTION 1" << endl;
			return rightRot(root);
		}
		if (bal > 1 && RemBalance(root->left) < 0) {
			//out << "OPTION 2" << endl;
			root->left = leftRot(root->left);
			return rightRot(root);
		}
		if (bal < -1 && RemBalance(root->right) <= 0) {
			//out << "OPTION 3" << endl;
			return leftRot(root);
		}
		if (bal < -1 && RemBalance(root->right) > 0) {
			//out << "OPTION 4" << endl;
			root->right = rightRot(root->right);
			return leftRot(root);
		}
		root->height = maxHeight(height(root->left), height(root->right)) + 1;
		return root;
	}

	Node* leftRot(Node*& n) {
		Node* temp1 = n->right;
		Node* temp2 = temp1->left;
		temp1->left = n;
		n->right = temp2;
		n->height = 1 + maxHeight(height(n->left), height(n->right));
		temp1->height = 1 + maxHeight(height(temp1->left), height(temp1->right));
		return temp1;
	}
	Node* rightRot(Node*& n) {
		Node* temp1 = n->left;
		Node* temp2 = temp1->right;
		temp1->right = n;
		n->left = temp2;
		n->height = 1 + maxHeight(height(n->left), height(n->right));
		temp1->height = 1 + maxHeight(height(temp1->left), height(temp1->right));
		return temp1;
	}

	int RemBalance(Node* root)
	{
		if (root == NULL)
			return 0;
		else
			return (height(root->left) - height(root->right));
	}

	int height(Node* temp)
	{
		if (temp == NULL)
			return 0;
		else {
			return temp->height;
			/*int r = height(temp->right);
			int l = height(temp->left);
			if (r > l) {
				return r + 1;
			}
			else {
				return l + 1;
			}*/
		}
	}
	
	Node* getSmall(Node* n)
	{
		Node* temp = n;
		while (temp->left != NULL)
			temp = temp->left;
		return temp;
	}
	int maxHeight(int left, int right)
	{
		if (left > right)
			return left;
		else
			return right;
	}

	void getParent(Node*& old_root, Node*& local_root)
	{
		if (local_root->left != NULL)
			getParent(old_root, local_root->left);
		else {
			old_root->item = local_root->item;
			old_root = local_root;
			local_root = local_root->right;
		}
		if(local_root != NULL)
			local_root->height--;
	}
	
	bool find(const A& item, Node*& root)
	{
		if (root == NULL)
			return false;
		if (item == root->item)
			return true;
		else if (item < root->item)
			return find(item, root->left); //ADDED RETURN
		else if (item > root->item)
			return find(item, root->right); //ADDED RETURN
		return false;
	}

	void clear(Node* root)
	{
		if (root == NULL)
			return;
		if (root->left != NULL && root->right != NULL)
		{
			clear(root->left);
			clear(root->right);
		}
		delete root;
		root = NULL;
	}

	void print(ofstream& out)
	{
		out << "print" << endl;
		if (root == NULL) {
			return;
		}
		Queue<Node*> Q;
		Q.insert(root);
		int lvl = 0;
		int const MAX = 8;
		while (true)
		{
			int max = 0;
			int count = Q.size;
			if (count == 0)
				break;

			out << "level " << lvl << ":";
			while (count > 0)
			{
				if (max == MAX) { //IS IT RIGHT?
					out << endl;
					out << "level " << lvl << ": ";
					max = 0;
				}
				Node* n = Q.front();
				out << " " << n->item << "(" << n->height << ")";
				Q.pop();
				if (n->left != NULL)
					Q.insert(n->left);
				if (n->right != NULL)
					Q.insert(n->right);
				count--;
				max++;
			}
			lvl++;
			out << endl;
		}

	}

	~Tree() {
		clear(root);
	}
};

