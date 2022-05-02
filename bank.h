/*
*   CSS 342B - Data Structures, Algorithms, and Discrete Mathematics I
*   Program 5: The Jolly Banker
*   Name: Terry Tran
*	The Bank Class
*	Description:
*   This is the bank class. The bank class takes care of processing the queue, and then running the given transactions given once
*	the account is opened, and checked if it the account is valid in the BSTree. 
*/
#ifndef BANK_H
#define BANK_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include "bstree.h"
#include "account.h"
using namespace std;

class Bank
{
public: 
	Bank();
	~Bank();

	bool Open(int id, string first, string last);
	bool Deposit(int id, int amount, int fund_type);
	bool Withdraw(int id, int amount, int fund_type);
	bool ViewFullHistory(int id);
	bool ViewFundHistory(int id, int fund_type);
	bool Transfer(int source_id, int source_fund_type, int amount, int target_fund_type, int target_id);
	bool Enqueue(vector<string> transaction);
	bool ProcessQueue();
	void Display() const;

private:
	BSTree accounts_;
	queue<vector<string>> transactions_queue_;
};
#endif
