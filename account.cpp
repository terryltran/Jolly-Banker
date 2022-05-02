// This is the implementation of the Account Class "account.h"
#include "account.h"

Account::Account(int id, string first_name, string last_name)
{
	id_ = id;
	first_name_ = first_name;
	last_name_ = last_name;

	// Account creates a new fund for each fund type and a history of transactions for each of those fund types for ONE SINGLE ACCOUNT.
	funds_[0] = new Fund("Money Market");
	funds_[1] = new Fund("Prime Money Market");
	funds_[2] = new Fund("Long-Term Bond");
	funds_[3] = new Fund("Short-Term Bond");
	funds_[4] = new Fund("500 Index Fund");
	funds_[5] = new Fund("Capital Value Fund");
	funds_[6] = new Fund("Growth Equity Fund");
	funds_[7] = new Fund("Growth Index Fund");
	funds_[8] = new Fund("Value Fund");
	funds_[9] = new Fund("Value Stock Index");

	fund_history_[0] = new Transaction("Money Market");
	fund_history_[1] = new Transaction("Prime Money Market");
	fund_history_[2] = new Transaction("Long-Term Bond");
	fund_history_[3] = new Transaction("Short-Term Bond");
	fund_history_[4] = new Transaction("500 Index Fund");
	fund_history_[5] = new Transaction("Capital Value Fund");
	fund_history_[6] = new Transaction("Growth Equity Fund");
	fund_history_[7] = new Transaction("Growth Index Fund");
	fund_history_[8] = new Transaction("Value Fund");
	fund_history_[9] = new Transaction("Value Stock Index");
}

Account::~Account()
{
}

string Account::getFirstName() const
{
	return first_name_;
}

string Account::getLastName() const
{
	return last_name_;
}

int Account::getID() const
{
	return id_;
}

bool Account::Deposit(int amount, int fund_type)
{
	// String transaction is added into the history recorder
	string transaction = "D " + to_string(id_) + to_string(fund_type) + " " + to_string(amount);
	if (fund_type < 0 || fund_type > 9)
	{
		cerr << "Error: Invalid Fund Type." << endl;
		return false;
	}
	else if (amount < 0)
	{
		cerr << "Error: Invalid deposit amount. Cannot deposit negative amount." << endl;
		fund_history_[fund_type]->Recorder(transaction + " (FAILED)");
		return false;
	}
	else
	{
		funds_[fund_type]->Deposit(amount);
		fund_history_[fund_type]->Recorder(transaction);
		fund_history_[fund_type]->getRecords();
		return true;
	}
}

bool Account::Withdraw(int amount, int fund_type)
{
	string transaction = "W " + to_string(id_) + to_string(fund_type) + " " + to_string(amount);
	if (fund_type < 0 || fund_type > 9)
	{
		cerr << "Error: Invalid Fund Type." << endl;
		return false;
	}
	else if (amount < 0)
	{
		cerr << "Error: Invalid withdrawal amount. Cannot withdraw negative amount." << endl;
		fund_history_[fund_type]->Recorder(transaction + " (FAILED)");
		return false;
	}
	// Case for when amount wanting to be withdrawn surpasses the balance
	if (amount > funds_[fund_type]->getBalance())
	{
		// Joint Functions
		if (fund_type == 0 || fund_type == 1 || fund_type == 2 || fund_type == 3)
		{
			// Helper for situations where you can withdraw from joint functions
			return JointWithdraw(fund_type, amount);
		}
		cerr << "Error: Insufficient Funds. Cannot withdraw $" << amount << " from " << first_name_ << " " << last_name_ << "'s " << funds_[fund_type]->getFundType() << endl;
		fund_history_[fund_type]->Recorder(transaction + " (FAILED)");
		return false; 
	}
	else
	{
		// Withdraw normal if sufficient funds and record transaction
		funds_[fund_type]->Withdraw(amount);
		fund_history_[fund_type]->Recorder(transaction);
		return true;
	}
}

bool Account::JointWithdraw(int fund_type, int amount)
{
	string transaction;
	int joint_fund_type;
	// Determines the joint fund type depending on the given fund type
	switch (fund_type)
	{
	case 0:
		joint_fund_type = 1;
		break;
	case 1:
		joint_fund_type = 0;
		break;
	case 2:
		joint_fund_type = 3;
		break;
	case 3:
		joint_fund_type = 2;
		break;
	default:
		return false;
	}

	int result = 0;
	int new_balance = 0;
	result = funds_[fund_type]->getBalance() - amount;
	// Case for when there is sufficient balance to do a withdraw from the joint fund type 
	if (funds_[joint_fund_type]->getBalance() >= abs(result))
	{
		new_balance = amount - abs(result);
		funds_[fund_type]->Withdraw(funds_[fund_type]->getBalance());
		funds_[joint_fund_type]->Withdraw(abs(result));
		transaction = "W " + to_string(id_) + to_string(fund_type) + " " + to_string(abs(new_balance));
		fund_history_[fund_type]->Recorder(transaction);
		transaction = "W " + to_string(id_) + to_string(joint_fund_type) + " " + to_string(abs(result));
		fund_history_[joint_fund_type]->Recorder(transaction);
		return true;
	}
	else
	{
		fund_history_[fund_type]->Recorder(transaction + " (FAILED)");
		fund_history_[joint_fund_type]->Recorder(transaction + " (FAILED)");
		return false;
	}
}

bool Account::TransferDeposit(int source_id, int source_fund_type, int amount, int target_account_id, int target_fund_type)
{
	string transaction = "T " + to_string(source_id) + to_string(source_fund_type) + " " + to_string(amount) + " " + to_string(target_account_id) + to_string(target_fund_type);
	// Case for if the amount given is negative
	if (amount < 0)
	{
		cerr << "Error: Invalid deposit amount. Cannot deposit negative amount." << endl;
		fund_history_[target_fund_type]->Recorder(transaction + " (FAILED)");
		return false;
	}
	// Deposits money that is withdrawn from TransferWithdraw function into the target account and a specific target fund type
	else
	{
		funds_[target_fund_type]->Deposit(amount);
		fund_history_[target_fund_type]->Recorder(transaction);
		return true;
	}
}

bool Account::TransferWithdraw(int source_id, int source_fund_type, int amount, int target_account_id, int target_fund_type)
{
	string transaction = "T " + to_string(source_id) + to_string(source_fund_type) + " " + to_string(amount) + " " + to_string(target_account_id) + to_string(target_fund_type);
	if (amount < 0)
	{
		cerr << "Error: Invalid withdrawal amount. Cannot withdraw negative amount." << endl;
		fund_history_[source_fund_type]->Recorder(transaction + " (FAILED)");
		return false;
	}
	else if (funds_[source_fund_type]->getBalance() >= amount)
	{
		funds_[source_fund_type]->Withdraw(amount);
		fund_history_[source_fund_type]->Recorder(transaction);
	}
	// Check funds in joint funds (if applicable) 
	else if (JointWithdraw(source_fund_type, amount))
	{
		return true;
	}
	//If the amount exceeds the balance
	else
	{
		cerr << "Error: Insufficient funds. Cannot withdraw $" << amount << " from " << getFirstName() << " "  << getLastName() << "'s "<< funds_[source_fund_type]->getFundType() << endl;
		fund_history_[source_fund_type]->Recorder(transaction + " (FAILED)");
		return false;
	}
	return true;
}

void Account::FullHistory() const
{
	vector<string> temp;
	cout << "Full History of Transactions for " << first_name_ << " " << last_name_ << " | Account #" << id_ << endl;
	for (int i = 0; i < 10; i++)
	{
		// If the fund history of the fund type is NOT empty, then it prints out the history out for the fund type.
		// Otherwise, the fund type history will not show up when the FullHistory function is called.
		if (!fund_history_[i]->getRecords().empty())
		{
			cout << "History of Transactions for " << funds_[i]->getFundType() << endl;
			temp = fund_history_[i]->getRecords();
			cout << funds_[i]->getFundType() << ": $";
			cout << funds_[i]->getBalance() << endl;
			for (auto it = temp.begin(); it < temp.end(); it++)
			{
				cout << " " + *it << endl;
			}
			cout << endl;
		}
	}
}

void Account::FundHistory(int fund_type) const
{
	vector<string> temp;
	if (fund_type < 0 || fund_type > 9)
	{
		cerr << "Error: Invalid fund type. Could not obtain history." << endl;
	}
	// Prints out history of specific fund type that is given
	cout << "History of Transactions for " << first_name_ << " " << last_name_ << "'s " << funds_[fund_type]->getFundType() << endl;
	temp = fund_history_[fund_type]->getRecords();
	cout << funds_[fund_type]->getFundType() << ": $";
	cout << funds_[fund_type]->getBalance() << endl;
	for (auto it = temp.begin(); it < temp.end(); it++)
	{
		cout << " " + *it << endl;
	}
	cout << endl;
}

bool Account::operator==(const Account& account) const
{
	if (this->getID() == account.getID())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Account::operator<(const Account& account) const
{
	if (this->getID() < account.getID())
	{
		return true;
	}
	else
	{
		return false;
	}
}

ostream& operator<<(ostream& out_stream, const Account& the_account)
{
	out_stream << the_account.first_name_ << " " << the_account.last_name_ << " | " << "Account #" << the_account.id_ << endl;
	for (int i = 0; i < 10; i++)
	{
		out_stream << the_account.funds_[i]->getFundType() << ": $" << the_account.funds_[i]->getBalance() << endl;
	}
	return out_stream;
}
