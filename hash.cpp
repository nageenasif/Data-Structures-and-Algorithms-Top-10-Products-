#include "hash.h"

hTable::~hTable() {	//deconstructer
	delete[] fullFlag;
	delete[] newHash;
}


hTable::hTable() {		//creating an empty table and initializing order table
	for (int i = 0; i<9973; i++) {
		newHash[i] = new product;
		newHash[i]->stockcode = "";
		newHash[i]->description = "";
		newHash[i]->amount = 0;
		newHash[i]->next = NULL;
		fullFlag[i] = 0;
	}

	for (int i = 0; i<10; i++) {
		finalList[i] = newHash[0];
	}
}

unsigned int hTable::hKey(string stockcode) { //stockcode is taken as Key
	unsigned int key = 0;
	for (int i = 0; i<stockcode.size(); i++) {
		key = key * 23 + stockcode[i];
	}

	key = key % 9973;		//building a circular table
	return key;
}



void hTable::finalTable(product* tempptr) {
	int repit=0;
	int tableIndex = -1;
	int productIndex = -1;
	bool matches = 0;   //does the Key match the stockcode?

	for (int i = 0; i<10; i++) {  //traverse most ordered products table
		if (finalList[i]->stockcode == tempptr->stockcode) { //find the stockcode index in the most ordered products table
			matches = 1;
			productIndex = i;
		}
		if (finalList[i]->amount <= tempptr->amount) {  //find the position the product shall be due to its total quantity number (position is the sorting)
			tableIndex++;
		}    //increase the table spot 'till we find the correct position for the product
	}
	if(repit>1) {
		for (int i = productIndex; i > repit; i--) {
			finalList[i-1] = finalList[i-repit-1];
		}
	}


	if (tableIndex>-1) {   	//if the product position in the table is increased
		if (matches == 1) {	//for a matching product
			for (int i = productIndex; i<tableIndex; i++) {
				finalList[i] = finalList[i + 1];
			}  //shift every product coming after our currently checked product in the list, to correct the sorting
		}

		else {						//for an unmatched product
			for (int i = 0; i<tableIndex; i++) { 		//shift every product in the list from the first index and save the new one at the end
				finalList[i] = finalList[i + 1];
			}
		}

		finalList[tableIndex] = tempptr;  //insert our checked product to its correct table position.
	}


}

void hTable::TheResult() {

	cout << "Stockcode: \t\t" << "Descripton \t\t\t\t" << "Order" << endl;

	for (int i = 0; i<10; i++) {
		cout << finalList[i]->stockcode << "\t --- \t" << finalList[i]->description << "\t --- \t" << finalList[i]->amount << endl;
	}
}


void hTable::hashTheInput(string scode, string descript, string amountno) {
    int quantity = stoi(amountno);

	int key = hKey(scode);
	product* temp = newHash[key];

	if (temp->stockcode == scode) {     //Product is found in list
		temp->amount = temp->amount + quantity;    //updating its total quantity
	}

	else if (fullFlag[key] == 0) {	//The spot of the key is yet empty
		temp->stockcode = scode;
		temp->description = descript;
		temp->amount = quantity;
		temp->next = NULL;
		fullFlag[key] = 1;
	}  
		finalTable(temp);
}


