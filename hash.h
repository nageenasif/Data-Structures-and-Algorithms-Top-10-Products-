
#include <iostream>
#include <string>
#include <cstring>
#include <ctype.h>
#include <iostream>
using namespace std;

class hTable {
public:
	~hTable();
	hTable();
	unsigned int hKey(string key);
	void hashTheInput(string stockcode, string description, string amount);

	static const int tableSize = 9973;  //a random prime number

	struct product {
		string stockcode;
		string description;
		int amount;
		product* next;  };


	product *newHash[tableSize];
	bool fullFlag[tableSize];  //status 0-empty 1-filled
	product* finalList[10] = { NULL };
	void TheResult();

	void finalTable(product* tempptr);
private:
};



