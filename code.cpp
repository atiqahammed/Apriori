#include <iostream>
#include <vector>
#include <map>
#include <iostream>  
#include <sstream>

using namespace std;

#define min_sup 2

struct transaction {
	string transactionID;
	vector<string> products;
};


struct productSet {
	vector<string> productList;
	int count;
};
int depth = 1;

vector<productSet> allProductSetWithMinSup;

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

void findUniqueProduct(vector<string> &uniqueProduct, vector<transaction> transactions) {
	map<string, bool> productFound;
	for(int i = 0; i < transactions.size(); i++) {
		for(int j = 0; j < transactions[i].products.size(); j++) {
			if(! productFound[transactions[i].products[j]]) {
				uniqueProduct.push_back(transactions[i].products[j]);
				productFound[transactions[i].products[j]] = true;
			}
		} 
	}
}

void makeSetOfProductList(vector<productSet> &setofProductList, vector<string> uniqueProduct) {
	for(int i = 0; i < uniqueProduct.size(); i++) {
		productSet newSetofProductList;
		newSetofProductList.productList.push_back(uniqueProduct[i]);
		setofProductList.push_back(newSetofProductList);
	}
}


bool isOccuerIn(transaction currentTransaction, productSet currentProductList) {
	int count = 0;
	for(int i = 0; i < currentProductList.productList.size(); i++) {
		for(int j = 0; j < currentTransaction.products.size(); j++) {
			if(currentProductList.productList[i] == currentTransaction.products[j]) {
				count++;
				break;
			}
		}
	}

	if(count >= currentProductList.productList.size())
		return true;
	return false;
}


int testOccurance(productSet currentProductList, vector<transaction> transactions) {
	int count = 0;
	for(int i = 0; i < transactions.size(); i++)
		if(isOccuerIn(transactions[i], currentProductList))
			count++;
	return count;
}

void selectProductList(vector<productSet> &setOfProductList, vector<transaction> transactions, vector<productSet> &selectedSetOfProductList){
	for(int i = 0; i < setOfProductList.size(); i++) {
		int occurance = testOccurance(setOfProductList[i], transactions);
		setOfProductList[i].count = occurance;
		if(setOfProductList[i].count >= min_sup) {
			allProductSetWithMinSup.push_back(setOfProductList[i]);
			selectedSetOfProductList.push_back(setOfProductList[i]);
		}
	}
}

void printTable(string tableType, vector<productSet> setOfProductList) {
	cout << "Table " << tableType << depth << endl;
	for(int i = 0; i < setOfProductList.size(); i++) {
		for(int j = 0; j < setOfProductList[i].productList.size(); j++) {
			cout << setOfProductList[i].productList[j] << " ";
		}
		cout << "  --  " << setOfProductList[i].count << endl; 
	}

}

productSet getNewCombination(productSet set1, productSet set2) {
	productSet newSet;
	map<string, bool> taken;
	for(int i = 0; i < set1.productList.size(); i++) {
		if(!taken[set1.productList[i]]) {
			newSet.productList.push_back(set1.productList[i]);
			taken[set1.productList[i]] = true;
		}
	}

	for(int i = 0; i < set2.productList.size(); i++) {
		if(!taken[set2.productList[i]]) {
			newSet.productList.push_back(set2.productList[i]);
			taken[set2.productList[i]] = true;
		}
	}

	return newSet;
}

void operate(vector<productSet> setOfProductList, vector<transaction> transactions) {
	vector<productSet> selectedSetOfProductList;
	selectProductList(setOfProductList, transactions, selectedSetOfProductList);
	printTable("C", setOfProductList);
	cout << endl;
	if(selectedSetOfProductList.size() < 1) return;
	printTable("L", selectedSetOfProductList);
	cout << endl;
	
	vector<productSet> newSetofProductList;
	
	if(selectedSetOfProductList[0].productList.size() == 1) {
		for(int i = 0; i < selectedSetOfProductList.size() - 1; i++) {
			for(int j = i + 1; j < selectedSetOfProductList.size(); j++) {
				productSet newSet;
				newSet.productList.push_back(selectedSetOfProductList[i].productList[0]);
				newSet.productList.push_back(selectedSetOfProductList[j].productList[0]);
				newSetofProductList.push_back(newSet);
			}
		}

	} else 
		for(int i = 0; i < selectedSetOfProductList.size() - 1; i++)
			for(int j = i + 1; j < selectedSetOfProductList.size(); j++)
				if(selectedSetOfProductList[i].productList[0] == selectedSetOfProductList[j].productList[0])
					newSetofProductList.push_back( getNewCombination(selectedSetOfProductList[i], selectedSetOfProductList[j]));

	depth++;
	operate(newSetofProductList, transactions);
}



int main(void) {

	vector<transaction> transactions;
	vector<string> uniqueProduct;
	//map<productSet, int> countOfProductSet;


	

	inputTransactions(transactions);
	findUniqueProduct(uniqueProduct, transactions);

	vector<productSet> setofProductList;

	makeSetOfProductList(setofProductList, uniqueProduct);
	operate(setofProductList, transactions);



	//cout << setofProductList[0].productList[0] << endl;

	//countOfProductSet[setofProductList[0]] = 9;

	//cout << countOfProductSet[setofProductList[0]] << endl;




	//cout << setofProductList.size() << endl;

	//cout << uniqueProduct.size() << endl;

	//cout << transactions.size() << endl;
	//cout << "completed" << endl;



	return 0;
}