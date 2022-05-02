/*
*   CSS 342B - Data Structures, Algorithms, and Discrete Mathematics I
*   Program 5: The Jolly Banker
*   Name: Terry Tran
*	The Jolly Banker Driver
*	Description:
*   This is the driver that takes in the BankTransIn.txt file, reads through it and puts all the transactions into a vector that 
	is into a enqueued. Once the all the transactions have been enqueued. The transaction vector is cleared out. The queue is then 
	run in the Bank. Uses the bank funcions to process the queue and display the accounts in the bank and their total balances for
	each fund type. 
*/
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "bank.h"
int main()
{
	Bank* bank = new Bank();
	vector<string> transactions_list;
	ifstream in("BankTransIn.txt");
	string read_line;
	if (!in)
	{
		cerr << "Error: File cannot be opened." << endl;
	}

	while (!in.eof())
	{
		getline(in, read_line);
		if (read_line.empty())
		{
			break;
		}
		istringstream parse_line(read_line);
		string transaction_type;
		parse_line >> transaction_type;

		if (transaction_type == "O")
		{
			string last_name, first_name, account_id;
			parse_line >> first_name >> last_name >> account_id;
			transactions_list.push_back(transaction_type);
			transactions_list.push_back(last_name);
			transactions_list.push_back(first_name);
			transactions_list.push_back(account_id);
		}
		else if (transaction_type == "W" || transaction_type == "D")
		{
			transactions_list.push_back(transaction_type);
			int account_id, fund_type, amount;
			parse_line >> account_id >> amount;
			fund_type = account_id % 10;
			account_id = account_id / 10;
			transactions_list.push_back(to_string(account_id));
			transactions_list.push_back(to_string(fund_type));
			transactions_list.push_back(to_string(amount));
		}
		else if (transaction_type == "T")
		{
			transactions_list.push_back(transaction_type);
			int source_account_id, source_fund_type, amount, target_account_id, target_fund_type;
			parse_line >> source_account_id >> amount >> target_account_id;
			source_fund_type = source_account_id % 10;
			source_account_id = source_account_id / 10;
			target_fund_type = target_account_id % 10;
			target_account_id = target_account_id / 10;
			transactions_list.push_back(to_string(source_account_id));
			transactions_list.push_back(to_string(source_fund_type));
			transactions_list.push_back(to_string(amount));
			transactions_list.push_back(to_string(target_account_id));
			transactions_list.push_back(to_string(target_fund_type));
		}
		else if (transaction_type == "H")
		{
			transactions_list.push_back(transaction_type);
			string account_id;
			parse_line >> account_id;
			transactions_list.push_back(account_id);
		}
		else
		{
			cerr << "Error: Invalid transaction type." << endl;
		}
		// Push the vector into the queue
		bank->Enqueue(transactions_list);

		// Clears the transaction vector
		transactions_list.clear();
	}
	bank->ProcessQueue();
	bank->Display();
}


