#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <cstring>
#include "hash.h"
using namespace std;

int main(){

hTable *fileHash = new hTable;

std::ifstream File("OnlineRetail.csv");

string input="";
string noneed;
string stockcode, description, amount;

if(File.is_open()){  //file opened
while(std::getline(File, input)){

getline(File, noneed, ';');
getline(File, stockcode, ';');
getline(File, description, ';');
getline(File, amount, ';');
getline(File, noneed, ';');
getline(File, noneed, ';');
getline(File, noneed, ';');
getline(File, noneed, '\n');

fileHash->hashTheInput(stockcode, description, amount);
}

}
fileHash->TheResult();
	cin >> description;

return 0;
}
