// This is the implementaton of the Bank Class "bank.h"
#include "bank.h"

Bank::Bank()
{
}

Bank::~Bank()
{
}

bool Bank::Open(int id, string first, string last)
{
	if (id < 1000 || id > 9999)
	{
		cerr << "Error: ID must be 4 digits from 1000 to 9999." << endl;
		return false;
	}
	Account* new_account = new Account(id, first, last);
	//If the given ID is already associated with another account
	if (accounts_.Retrieve(id, new_account))
	{
		cerr << "Error: Account failed to be opened. There already exists an account with ID: " << id << endl;
		return false;
	}
	else
	{
		accounts_.Insert(new_account);
		return true;
	}
}

bool Bank::Deposit(int id, int amount, int fund_type)
{
	Account* temp = new Account(id, "Temp first", "Temp last");
	if (accounts_.Retrieve(id, temp))
	{
		temp->Deposit(amount, fund_type);
		return true;
	}
	else
	{
		cout << "Error: Deposit to account failed. Account ID #" << id << " does not exist" << endl;
		return false;
	}
}

bool Bank::Withdraw(int id, int amount, int fund_type)
{
	Account* temp = new Account(id, "Temp first", "Temp last");
	if (accounts_.Retrieve(id, temp))
	{
		temp->Withdraw(amount, fund_type);
		return true;
	}
	else
	{
		cout << "Error: Withdraw to account failed. Account ID #" << id << " does not exist" << endl;
		return false;
	}
}

bool Bank::ViewFullHistory(int id)
{
	Account* temp;
	if (accounts_.Retrieve(id, temp))
	{
		temp->FullHistory();
		return true;
	}
	else
	{
		cerr << "ERROR: Show history failed. Account ID #" << id << " does not exist" << endl;
		return false;
	}
}

bool Bank::ViewFundHistory(int id, int fund_type)
{
	Account* temp;
	if (accounts_.Retrieve(id, temp))
	{
		temp->FundHistory(fund_type);
		return true;
	}
	else
	{
		cerr << "ERROR: Show history failed. Account ID #" << id << " does not exist" << endl;
		return false;
	}
}

bool Bank::Transfer(int source_id, int source_fund_type, int amount, int target_fund_type, int target_id)
{
	Account* temp = new Account(source_id, "Temp first", "Temp last");
	Account* second_temp = new Account(target_id, "Temp third" , "Temp fourth");

	Account* source;
	Account* goal;

	if (!accounts_.Retrieve(source_id, source))
	{
		cerr << "Error: Transfer failed. Account ID #" << source_id << " does not exist." << endl;
		return false;
	}
	if (!accounts_.Retrieve(target_id, goal))
	{
		cerr << "Error: Transfer failed. Account ID #" << target_id << " does not exist." << endl;
		return false;
	}

	if (source->TransferWithdraw(source_id, source_fund_type, amount, target_id, target_fund_type))
	{
		goal->TransferDeposit(source_id, source_fund_type, amount, target_id, target_fund_type);
		return true;
	}
	else
	{
		cout << "Error: Transfer to Account ID #" << target_id << " failed. Account ID #" << source_id << " does not have sufficient funds." << endl;
		return false;
	}
}

bool Bank::Enqueue(vector<string> transaction)
{
	transactions_queue_.push(transaction);
	return true;
}

bool Bank::ProcessQueue()
{
	vector<string> transactions;
	while (!transactions_queue_.empty())
	{
		transactions = transactions_queue_.front();

		if (transactions[0] == "O")
		{
			Open(stoi(transactions[3]), transactions[1], transactions[2]);
		}
		else if (transactions[0] == "D")
		{
			Deposit(stoi(transactions[1]), stoi(transactions[3]), stoi(transactions[2]));
		}
		else if (transactions[0] == "W")
		{
			Withdraw(stoi(transactions[1]), stoi(transactions[3]), stoi(transactions[2]));
		}
		else if (transactions[0] == "T")
		{
			Transfer(stoi(transactions[1]), stoi(transactions[2]), stoi(transactions[3]), stoi(transactions[5]), stoi(transactions[4]));
		}
		else if (transactions[0] == "H")
		{
			if (transactions[1].size() == 5)
			{
				int fund_type = stoi(transactions[1]) % 10;
				int account_id = stoi(transactions[1]) / 10;
				ViewFundHistory((account_id), (fund_type));
			}
			else
			{
				ViewFullHistory(stoi(transactions[1]));
			}
		}
		transactions_queue_.pop();
	}
	cout << endl;
	cout << "Processing Has Been Finished. Printing final balances...";
	cout << endl;
	return true;
}

void Bank::Display() const
{
	accounts_.Display();
}