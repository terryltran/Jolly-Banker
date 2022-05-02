/*
*   CSS 342B - Data Structures, Algorithms, and Discrete Mathematics I
*   Program 5: The Jolly Banker
*   Name: Terry Tran
*	The Account Class
*	Description:
*   The account class handles all the transactions and sends the records of transactions done (whether completed or failed) 
	to the Transaction class to hold the transactions (which can be printed). 
*/
#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <iostream>
#include <vector>
#include <string>
#include "fund.h"
#include "transaction.h"
using namespace std;

class Account
{
public:
	Account(int id, string first_name, string last_name);
	~Account();

	string getFirstName() const;
	string getLastName() const;
	int getID() const;
	bool Deposit(int amount, int fund_type);
	bool Withdraw(int amount, int fund_type);
	bool TransferDeposit(int source_id, int source_fund_type, int amount, int target_account_id, int target_fund_type);
	bool TransferWithdraw(int source_id, int source_fund_type, int amount, int target_account_id, int target_fund_type);
	void FullHistory() const;
	void FundHistory(int fund_type) const;

	friend ostream& operator<<(ostream& out_stream, const Account& account);
	bool operator==(const Account& account) const;
	bool operator<(const Account& account) const;

private:
	int id_ = 0;
	string first_name_ = " ";
	string last_name_ = " ";
	vector<string> full_history_;
	Fund* funds_[10];
	Transaction* fund_history_[10];
	// Helper Function for Joint withdraw cases
	bool JointWithdraw(int fund_type, int amount);
};
#endif