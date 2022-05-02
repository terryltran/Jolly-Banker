// This is the implementation of the BSTree class "bstree.h'
#include "bstree.h"

BSTree::BSTree()
{
	root_ = new Node();
	root_->pAcct_ = new Account(-1234, "Temp First", "Temp Last");
}

BSTree::~BSTree()
{
	Empty();
}

bool BSTree::Insert(Account* the_account)
{
	RecursiveInserter(root_, the_account);
	return true;
}

bool BSTree::Retrieve(const int& id, Account*& the_account) const
{
	Account* temp = Searcher(root_, id);
	if (temp == NULL)
	{
		return false;
	}
	else
	{
		the_account = temp;
		return true;
	}
}

void BSTree::Display() const
{
	if (root_ == NULL || root_->pAcct_->getID() == -1234)
	{
		cerr << "Error: List of Accounts is empty." << endl;
	}
	else
	{
		Printer(root_);
	}
}

void BSTree::Empty()
{
	root_ = NULL;
}

bool BSTree::isEmpty() const
{
	if (root_ == nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}
// These are Private Functions Help Other Functions of the BSTree
Account* BSTree::Searcher(Node* node, const int& search_target) const
{
	if (node == NULL)
	{
		return NULL;
	}
	else if (search_target == (node->pAcct_->getID()))
	{
		return (node->pAcct_);
	}
	else if (search_target < (node->pAcct_->getID()))
	{
		return Searcher(node->left_, search_target);
	}
	else
	{
		return Searcher(node->right_, search_target);
	}
}

void BSTree::RecursiveInserter(Node*& node, Account* insert_goal)
{
	if (node == NULL || node->pAcct_->getID() == -1234)
	{
		node = new Node();
		node->pAcct_ = insert_goal;
		return;
	}
	else if (*insert_goal < *node->pAcct_)
	{
		RecursiveInserter(node->left_, insert_goal);
	}
	else
	{
		RecursiveInserter(node->right_, insert_goal);
	}
}

void BSTree::Printer(Node* current_node) const
{
	if (current_node->right_ != NULL && current_node->left_ != NULL)
	{
		Printer(current_node->right_);
		cout << *(current_node->pAcct_) << endl;
		Printer(current_node->left_);
	} 
	else if (current_node->left_ != NULL)
	{
		cout << *(current_node->pAcct_) << endl;
		Printer(current_node->left_);
	}
	else if (current_node->right_ != NULL)
	{
		cout << *(current_node->pAcct_) << endl;
		Printer(current_node->right_);
	}
	else
	{
		cout << *(current_node->pAcct_) << endl;
	}
}



