#pragma once
#include <string>
#include <vector>
using namespace std;

extern string ClientsFile;
extern string UsersFile;

vector<string> SplitString(string S1, string delim);
void PrintSuccesOfTheOperationMessage(string Message);
void ReturnToMainMenue();
