/*
*   CSS 342B - Data Structures, Algorithms, and Discrete Mathematics I
*   Program 5: The Jolly Banker
*   Name: Terry Tran
*	The Transaction Class
*	Description:
*   This is the transaction class. It allows transactions to be recorder and saved into a history vector.
*	Then whenever a record of transactions is requested, the getRecords() function will be called to get
*	the recorders of a specific fund type or for the full history of an account. 
*/
#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Transaction
{
public:
	Transaction(string name);
	~Transaction();

	bool Recorder(string transaction);
	vector<string> getRecords();

private:
	vector<string> history_;
	string fund_type_ = "";
};
#endif
