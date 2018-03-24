#include <iostream>
#include <vector>
#include <iostream>  
#include <sstream>

using namespace std;

struct transaction {
	string transactionID;
	vector<string> products;
};

transaction stringToTransaction(string input) {
	istringstream iss (input);
	transaction newTransaction;
	iss >> newTransaction.transactionID;
	string product;
	while(iss >> product) 
		newTransaction.products.push_back(product);
	return newTransaction;
}

void inputTransactions(vector<transaction> &transactions) {
	string input;
	while(getline(cin, input)) 
		transactions.push_back(stringToTransaction(input));
}





int main(void) {

	vector<transaction> transactions;

	inputTransactions(transactions);
	cout << transactions.size() << endl;
	//cout << "completed" << endl;



	return 0;
}