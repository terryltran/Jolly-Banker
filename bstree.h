/*
*   CSS 342B - Data Structures, Algorithms, and Discrete Mathematics I
*   Program 5: The Jolly Banker
*   Name: Terry Tran
*	The BSTree Class
*	Description:
*   This is the BSTree class. The accounts that are made are sent to a binary search tree of accounts and inserted into the tree
*	where they belong. The Insert function takes advantage of a RecursiveInserter function. The Retrieve function that checks that
*	the account exists or if the account id trying to be used to create a new account is already in use, uses a recursive searcher. 
	Finally, the display function uses a recursive printer function. 
*/
#ifndef BSTREE_H
#define BSTREE_H
#include <iostream>
#include <vector>
#include <string>
#include "account.h"
using namespace std;

class BSTree
{
public:
	BSTree();
	~BSTree();

	bool Insert(Account* the_account);
	// retrieve object, first parameter is the ID of the account
	// second parameter holds pointer to found object, NULL if not found
	bool Retrieve(const int& id, Account*& the_account) const;
	// displays the contents of a tree to cout
	void Display() const;
	void Empty();
	bool isEmpty() const;

private:
	struct Node
	{
		Account* pAcct_;
		Node* right_ = nullptr;
		Node* left_ = nullptr;
	};
	Node* root_ = nullptr;
	Account* Searcher(Node* node, const int& target) const;
	void RecursiveInserter(Node*& node, Account* insert_goal);
	void Printer(Node* node) const;
};
#endif
