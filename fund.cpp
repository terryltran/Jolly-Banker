// Implementation of the Fund Class "fund.h"
#include "fund.h"

Fund::Fund(string fund_type)
{
	fund_name_ = fund_type;
}

Fund::~Fund()
{
}

bool Fund::Deposit(int amount)
{
	balance_ += amount;
	return true;
}

bool Fund::Withdraw(int amount)
{
	balance_ -= amount;
	return true;
}

int Fund::getBalance() const
{
	return balance_;
}

string Fund::getFundType()
{
	return fund_name_;
}
