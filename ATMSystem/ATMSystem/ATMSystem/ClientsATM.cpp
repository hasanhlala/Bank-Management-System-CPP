#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include "ClientsATM.h"
#include "CommonATM.h"

stClientData CurrentClient;
using namespace std;

void ReadClientAccountNumberAndPinCode() {
	cout << "Enter the account number: ";
	cin >> CurrentClient.AccountNumber;
	cout << "Enter PIN code: ";
	cin >> CurrentClient.PinCode;
}

bool CheckIfClientIsFoundInFileAndLoadData() {

	fstream MyFile;
	MyFile.open(ClientsFile, ios::in);

	if (MyFile.is_open()) {
		string line;
		stClientData CD;
		while (getline(MyFile, line)) {
			CD = ParseRecordToClient(line, "/#/");
			if (CD.AccountNumber == CurrentClient.AccountNumber && CD.PinCode == CurrentClient.PinCode) {
				CurrentClient = CD;
				return true;
			}
		}
		MyFile.close();
	}

	return false;
}

bool IfTheAccountNumperFound(string AccountNumber) {

	fstream MyFile;
	MyFile.open(ClientsFile, ios::in);

	if (MyFile.is_open()) {
		string line;
		stClientData CD = {};

		while (getline(MyFile, line)) {
			CD = ParseRecordToClient(line, "/#/");
			if (CD.AccountNumber == AccountNumber)
				return true;
		}
		MyFile.close();
	}

	return false;
}

stClientData ReadClientData() {
	stClientData CD;
	cout << "Enter Account Number? ";
	getline(cin >> ws, CD.AccountNumber);
	while (IfTheAccountNumperFound(CD.AccountNumber)) {
		cout << "\nThe Account Numper " << CD.AccountNumber << " found in the file...\n";
		cout << "Enter another one : ";
		getline(cin >> ws, CD.AccountNumber);
	}
	cout << "Enter PinCode? ";
	getline(cin, CD.PinCode);
	cout << "Enter Name? ";
	getline(cin, CD.Name);
	cout << "Enter Phone? ";
	getline(cin, CD.Phone);
	cout << "Enter Account Balance? ";
	cin >> CD.AccountBalance;

	return CD;
}

void PrintClientData(stClientData CD) {

	cout << "\n\n";

	cout << "Account Number : " << CD.AccountNumber << endl;
	cout << "Pin Code       : " << CD.PinCode << endl;
	cout << "Name           : " << CD.Name << endl;
	cout << "Phone          : " << CD.Phone << endl;
	cout << "Account Balance: " << CD.AccountBalance << endl;

}

void AppendClientRecordToFile(string Record) {

	fstream MyFile;

	MyFile.open(ClientsFile, ios::out | ios::app);

	if (MyFile.is_open()) {

		MyFile << Record << endl;
		MyFile.close();
	}


}

string CreateClientRecord(stClientData CD, string Diameter) {

	string Record = "";

	Record += (CD.AccountNumber + Diameter);
	Record += (CD.PinCode + Diameter);
	Record += (CD.Name + Diameter);
	Record += (CD.Phone + Diameter);
	Record += (to_string(CD.AccountBalance));

	return Record;

}

stClientData ParseRecordToClient(string Record, string Diameter) {

	vector<string> vRecordData = SplitString(Record, Diameter);

	stClientData ClientData;

	if (vRecordData.empty()) {
		return ClientData;
	}

	ClientData.AccountNumber = vRecordData[0];

	if (vRecordData.size() >= 2) {
		ClientData.PinCode = vRecordData[1];
	}
	if (vRecordData.size() >= 3) {
		ClientData.Name = vRecordData[2];
	}
	if (vRecordData.size() >= 4) {
		ClientData.Phone = vRecordData[3];
	}
	if (vRecordData.size() >= 5) {
		ClientData.AccountBalance = stoi(vRecordData[4]);
	}

	return ClientData;
}

void WriteClientsToFile(vector <stClientData>& vClients) {

	fstream MyFile;

	MyFile.open(ClientsFile, ios::out);

	if (MyFile.is_open()) {
		for (int i = 0; i < vClients.size(); i++) {
			if (!vClients[i].MarkForDelete)
				MyFile << CreateClientRecord(vClients[i], "/#/") << endl;
		}
	}

}

void ReadClientsFromFile(vector<stClientData>& vClients) {

	fstream MyFile;

	MyFile.open(ClientsFile, ios::in);

	if (MyFile.is_open()) {
		string line = "";
		stClientData client;

		while (getline(MyFile, line)) {
			client = ParseRecordToClient(line, "/#/");
			if (!line.empty())
				vClients.push_back(client);

		}

		MyFile.close();
	}

}

void PrintClientTableHeader(int Count) {
	const int totalWidth = 2 + 14 + 2 + 12 + 2 + 40 + 2 + 14 + 2 + 14 + 2; // compute rough width including separators
	cout << "\n\t\t\t\tClient List (" << Count << ") Client(s)." << endl;
	cout << string(totalWidth, '_') << "\n\n";
	cout << "| " << setw(14) << left << "Account Number"
		<< "| " << setw(12) << left << "Pin Code"
		<< "| " << setw(40) << left << "Client Name"
		<< "| " << setw(14) << left << "Phone"
		<< "| " << setw(14) << left << "Balance"
		<< " |" << endl;
	cout << string(totalWidth, '_') << "\n";
}

void PrintClientRow(stClientData& Client) {
	cout << "| " << setw(14) << left << Client.AccountNumber;
	cout << "| " << setw(12) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(14) << left << Client.Phone;
	cout << "| " << setw(14) << left << Client.AccountBalance << " |";
}

void PrintClientTable(vector <stClientData>& vClients) {
	PrintClientTableHeader(vClients.size());
	if (vClients.size() != 0) {
		for (size_t i = 0; i < vClients.size(); i++) {
			PrintClientRow(vClients[i]);
			cout << "\n";
		}
	}

}

void InteractiveAddSingleClient() {
	stClientData CD;
	CD = ReadClientData();
	AppendClientRecordToFile(CreateClientRecord(CD, "/#/"));
}

void DisplayAllClientsFromFile() {

	vector <stClientData> vClients;
	ReadClientsFromFile(vClients);
	PrintClientTable(vClients);
}

void InteractiveAddMultipleClients() {
	char MoreClients = 'y';
	do {
		system("cls");
		cout << "Add new client : " << endl;
		InteractiveAddSingleClient();
		cout << "\nWant to add more client ? ";
		cin >> MoreClients;
	} while (toupper(MoreClients) == 'Y');
	cout << endl;
}

int FindClientIndexInVector(vector <stClientData>& vClients, string AccountNumber) {

	for (int i = 0; i < vClients.size(); i++) {
		if (vClients[i].AccountNumber == AccountNumber) return i;
	}

	return -1;
}

void RemoveDeletedClientsFromVector(vector <stClientData>& vClients) {
	vector <stClientData> vClients2;
	int count = 0;

	for (int i = 0; i < vClients.size(); i++) {
		if (vClients[i].MarkForDelete)
			continue;
		vClients2.push_back(vClients[i]);
		count++;
	}

	vClients = vClients2;

}

void MarkClientForDeletionInVector(vector <stClientData>& vClients, string AccountNumber, bool& deleteSuccess) {

	int clientIndex = FindClientIndexInVector(vClients, AccountNumber);

	if (clientIndex != -1) {
		vClients[clientIndex].MarkForDelete = true;
		deleteSuccess = true;
	}
	else {
		deleteSuccess = false;
		return;
	}
	RemoveDeletedClientsFromVector(vClients);

}

void DeleteClientFromFileByAccountNumber(string AccountNumber, bool& deleteSuccess) {

	vector <stClientData> vClients;
	ReadClientsFromFile(vClients);

	MarkClientForDeletionInVector(vClients, AccountNumber, deleteSuccess);

	if (deleteSuccess) {
		WriteClientsToFile(vClients);
	}
}

void InteractiveDeleteMultipleClients() {
	char deleteMore = 'n';
	char wantToDelete = 'n';
	bool deleteSuccess = false;

	string accountNumber;

	do {
		system("cls");

		cout << "\n\n";
		if (toupper(deleteMore) == 'N')
			cout << "Enter the client account number you want to delete from " << ClientsFile << ": ";
		else
			cout << "Enter the next client account number: ";
		cin >> accountNumber;

		cout << "\nDo you really want to delete the client " << accountNumber << "? (Y/N): ";
		cin >> wantToDelete;

		deleteSuccess = false;
		if (toupper(wantToDelete) == 'Y') {
			DeleteClientFromFileByAccountNumber(accountNumber, deleteSuccess);
		}

		if (deleteSuccess) {
			cout << "\n\nThe client with account number " << accountNumber << " was deleted successfully.\n";
		}
		else {
			cout << "The client with account number " << accountNumber << " was not found.\n";
		}

		cout << "\n\nDo you want to delete more clients? (Y/N): ";
		cin >> deleteMore;

	} while (toupper(deleteMore) == 'Y');

	cout << endl;
}

stClientData FindClientInFileByAccountNumber(string AccountNumber) {

	fstream MyFile;
	MyFile.open(ClientsFile, ios::in);

	if (MyFile.is_open()) {
		string line;
		stClientData CD;

		while (getline(MyFile, line)) {
			CD = ParseRecordToClient(line, "/#/");
			if (CD.AccountNumber == AccountNumber) {
				MyFile.close();
				return CD;
			}
		}

		MyFile.close();
	}

	return stClientData();
}

void FindClientByAccountNumber() {
	system("cls");
	string AccountNumber;
	AccountNumber = ReadAccountNumber();

	stClientData CD = FindClientInFileByAccountNumber(AccountNumber);
	PrintClientData(CD);

	cout << "\n";
}

void UpdateClientInVector(vector <stClientData>& vClients, string AccountNumber) {

	int IndexOfClients = FindClientIndexInVector(vClients, AccountNumber);

	cout << "\n\nEnter Client Data Info : \n";
	cout << string(25, '=') << endl;

	cout << "Enter PinCode? ";
	getline(cin >> ws, vClients[IndexOfClients].PinCode);
	cout << "Enter Name? ";
	getline(cin, vClients[IndexOfClients].Name);
	cout << "Enter Phone? ";
	getline(cin, vClients[IndexOfClients].Phone);
	cout << "Enter Account Balance? ";
	cin >> vClients[IndexOfClients].AccountBalance;
	cout << string(25, '=') << endl;


}

void UpdateClientInformation() {
	system("cls");
	string AccountNumber = ReadAccountNumber();

	vector <stClientData> vClients;

	ReadClientsFromFile(vClients);

	UpdateClientInVector(vClients, AccountNumber);

	WriteClientsToFile(vClients);

	cout << "\n";

}

string ReadAccountNumber() {
	string AccountNumber;

	cout << "Enter the Account Number : ";
	cin >> AccountNumber;

	while (!IfTheAccountNumperFound(AccountNumber)) {
		cout << "The Account Number not found!!!" << endl;
		cout << "Please enter a rigth one : ";
		cin >> AccountNumber;
	}
	return AccountNumber;
}
