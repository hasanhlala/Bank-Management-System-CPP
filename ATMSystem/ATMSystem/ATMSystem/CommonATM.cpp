#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include "CommonATM.h"
#include "ClientsATM.h"
#include "TransactionATM.h"

using namespace std;


string ClientsFile = "ClientsData";
string UsersFile = "UsersFile";

vector<string> SplitString(string S1, string delim) {

	vector <string> vString;

	size_t pos = 0;
	string sWord;

	while ((pos = S1.find(delim)) != string::npos) {

		sWord = S1.substr(0, pos);
		if (sWord != "") {
			vString.push_back(sWord);
		}

		S1.erase(0, pos + delim.length());

	}

	if (S1 != "") {
		vString.push_back(S1);
	}

	return vString;

}

void PrintSuccesOfTheOperationMessage(string Message) {
	int LineLength = 10 + Message.length() + 10;
	cout << "\n\n";
	cout << string(LineLength, '-') << endl;
	cout << string(10, ' ') << Message << endl;
	cout << string(LineLength, '-') << endl;
}

void ReturnToMainMenue() {
	cout << "\nPress any key to return to main menue...." << endl;
	system("pause>0");
}
