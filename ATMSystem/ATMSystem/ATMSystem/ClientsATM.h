#pragma once
#include <string>
#include <vector>
using namespace std;

struct stClientData {
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	int AccountBalance = 0;
	bool MarkForDelete = false;
};

void ReadClientAccountNumberAndPinCode();
void PrintLoginScreen();
bool CheckIfClientIsFoundInFileAndLoadData();
bool IfTheAccountNumperFound(string AccountNumber);
stClientData ReadClientData();
void PrintClientData(stClientData CD);
void AppendClientRecordToFile(string Record);
string CreateClientRecord(stClientData CD, string Diameter);
stClientData ParseRecordToClient(string Record, string Diameter);
void WriteClientsToFile(vector <stClientData>& vClients);
void ReadClientsFromFile(vector<stClientData>& vClients);
void PrintClientTableHeader(int Count);
void PrintClientRow(stClientData& Client);
void PrintClientTable(vector <stClientData>& vClients);
void InteractiveAddSingleClient();
void DisplayAllClientsFromFile();
void InteractiveAddMultipleClients();
int FindClientIndexInVector(vector <stClientData>& vClients, string AccountNumber);
void RemoveDeletedClientsFromVector(vector <stClientData>& vClients);
void MarkClientForDeletionInVector(vector <stClientData>& vClients, string AccountNumber, bool& deleteSuccess);
void DeleteClientFromFileByAccountNumber(string AccountNumber, bool& deleteSuccess);
void InteractiveDeleteMultipleClients();
stClientData FindClientInFileByAccountNumber(string AccountNumber);
void FindClientByAccountNumber();
void UpdateClientInVector(vector <stClientData>& vClients, string AccountNumber);
void UpdateClientInformation();
string ReadAccountNumber();

