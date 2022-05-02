// Implementation of the Transaction Class "transaction.hh"
#include "transaction.h"

Transaction::Transaction(string name)
{
	fund_type_ = name;
}

Transaction::~Transaction()
{
}

bool Transaction::Recorder(string history)
{
	history_.push_back(history);
	return true;
}

vector<string> Transaction::getRecords()
{
	return history_;
}
