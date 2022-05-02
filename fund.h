/*
*   CSS 342B - Data Structures, Algorithms, and Discrete Mathematics I
*   Program 5: The Jolly Banker
*   Name: Terry Tran
*	The Fund Class
*	Description:
*   This is the fund class. The fund class takes care of all the fund functions and holds the balances for each of the fund types
*	for every account made in the bank. 
*/
#ifndef FUND_H
#define FUND_H
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Fund
{
public:
	Fund(string fund_type);
	~Fund();

	bool Deposit(int amount);
	bool Withdraw(int amount);
	int getBalance() const;
	string getFundType();
private:
	int balance_ = 0;
	string fund_name_ = " "; 
};
#endif
