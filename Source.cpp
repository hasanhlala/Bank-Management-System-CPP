
//The Programer Hasan Hlala
//This Program is a simple example of Banks Programs
//I write this code as a project in the end of the 7 course of Abo Hadhoud courses 

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;


string ClientsFile = "ClientsData";
string UsersFile = "UsersFile";

struct stClientData {
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	int AccountBalance;
	bool MarkForDelete = false;
};

struct stUserAccount {
	string UserName;
	string Passowrd;
	enMainMenuPermissions Permission;
	bool MarkForDelete = false;
};

enum enTasks {
	ChowClientList = 1,
	AddNewClient = 2,
	DeleteClient = 3,
	UpdateClientInfo = 4,
	FindClient = 5,
	Transactions = 6,
	ManageUsers = 7,
	LogOut = 8
};

enum enTransactions {
	Deposit = 1,
	Withdraw = 2,
	TotalBalance = 3,
	MainMenue = 4
};

enum enUsersTransactions {
	ListUsers = 1,
	AddNewuser = 2,
	DeleteUser = 3,
	UpdateUser = 4,
	Finduser = 5,
	MainMenue = 6
};

enum enMainMenuPermissions {
	pAll = -1,
	pNoThing = 0,
	pListClients = 1,
	pAddNewClient = 2,
	pDeleteClient = 4,
	pUpdateClient = 8,
	pFindClient = 16,
	pTransactons = 32,
	pManageUsers = 64,

};



vector<string> SplitString(string S1, string delim);
stClientData ReadClientData();
void PrintClientData(stClientData CD);
void AppendClientRecordToFile(string Record);
string CreateClientRecord(stClientData CD, string Diameter);
stClientData ParseRecordToClient(string Record,string Diameter);
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
void ReturnToTransactionsMainMenue();
string ReadAccountNumber();
void PrintDepositScreen();
void DepositInClient();
void PerformeTransaction(enTransactions Trans, bool& PerformeMore);
enTransactions ReadTheTransaction();
void PrintTransactionsMainMenue();
void PerformeTransactions();
enTasks WhatTheTask();
void PerformeTheTask(enTasks Task);
void PrintTheMainMenu();
void PrintEndCaption();
long long SumOfTotalBalance(vector <stClientData>& vClients);
void PrintClientBalanceTableHeader(int Count, int& LineLength);
void PrintClientBalanceTable(vector <stClientData>& vClients);
void PrintClientBalanceRow(stClientData& Client);
void DisplayTotalBalance();
void PrintWithdrawScreen();
void WithdrawFromClient();
void PrintloginScreen();
bool IfTheUsernameAndPassFound(stUserAccount UserAccount);
void LoginToAccount(stUserAccount& UserAccount);
void LoginAction();
void PrintManageUsresMainMenue();
enUsersTransactions ReadUsersTransactions();
void PrintUserTableHeader(int Users);
void PrintUserRow(stUserAccount& UA);
void PrintUsersListTable(vector <stUserAccount>& vUsers);
void DisplayAllUsersAccount();
void ReturnToUsersActionsMainMenu();
void ReturnToUsersActionsMainMenu();
void PrintAddNewUserScreen();
bool IfUsernameFoundInFile(string Username);
stUserAccount ReadNewUserInfo();
void InteractiveAddSingleUserAccount();
void PerformeUserTransactions(enUsersTransactions UserTransaction);
void PerformeUsersTransactions();
void ReadUsersFromFile(vector<stUserAccount>& vUsers);
string CreatUserAccountRecord(stUserAccount UserAccount);
stUserAccount ReadUserAccount();
stUserAccount ParseRecordToUserAccount(string Record, string Diameter = "/#/");
void AppendTheNewUserAccountRecordToFile(string UserAccountRecord);
enMainMenuPermissions ReadUserPermission();
bool CheckAccesPermission(enMainMenuPermissions Permission);

stUserAccount CurrentUser;
void StartTheProgram();







int main() {

	StartTheProgram();

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

bool CheckAccesPermission(enMainMenuPermissions Permission) {
	if (CurrentUser.Permission == enMainMenuPermissions::pAll)
		return true;
	return (CurrentUser.Permission & Permission) == Permission;
}

vector<string> SplitString(string S1, string delim) {

	vector <string> vString;

	short pos = 0;
	string sWord;

	while ((pos = S1.find(delim)) != std::string::npos) {

		sWord = S1.substr(0, pos);
		if (sWord != "") {
			vString.push_back(sWord);
		}

		S1.erase(0, pos + delim.length());

	}

	if (S1 != " ") {
		vString.push_back(S1);
	}

	return vString;

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

void PrintSuccesOfTheOperationMessage(string Message) {
	int LineLength = 10 + Message.length() + 10;
	cout << "\n\n";
	cout << string(LineLength, '-') << endl;
	cout << string(10,' ') << Message << endl;
	cout << string(LineLength, '-') << endl;
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

stClientData ParseRecordToClient(string Record, string Diameter = "/#/") {

	vector<string> vRecordData = { "" };
	vRecordData = SplitString(Record, Diameter);

	stClientData ClientData;

	if (vRecordData.size() == 0) {
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
		ClientData.AccountBalance = stod(vRecordData[4]);
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
			client = ParseRecordToClient(line,"/#/");
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

	string Record = "";

	fstream MyFile;
    MyFile.open(ClientsFile, ios::in);

	if (MyFile.is_open()) {
		string line;
		stClientData CD = {};

		while (getline(MyFile, line)) {
			CD = ParseRecordToClient(line,"/#/");
			if (CD.AccountNumber == AccountNumber)
				return CD;
		}

		MyFile.close();
	}


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
	string AccountNumber;
	cout << "Enter the Account Number of client you want to update it : ";
	cin >> AccountNumber;

	vector <stClientData> vClients;

	ReadClientsFromFile(vClients);

	UpdateClientInVector(vClients, AccountNumber);

	WriteClientsToFile(vClients);

	cout << "\n";

}

void ReturnToMainMenue() {
	cout << "\nPress any key to return to main menue...." << endl;
	system("pause>0");
}

void PrintDepositScreen() {
	string DepositScreen = "Deposit Screen";
	int LineLength = 10 + DepositScreen.length() + 10;

	cout << string(LineLength, '-') << endl;
	cout << string(10, ' ') << DepositScreen << endl;
	cout << string(LineLength, '-') << endl;
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

void ReturnToTransactionsMainMenue() {
	cout << "\nPress Any Key to return to Transactions Main Menue....\n";
	system("pause>0");
}

void DepositInClient() {
	PrintDepositScreen();
	cout << "\n";

	vector <stClientData> vClients;
	string AccountNumber = ReadAccountNumber();

	ReadClientsFromFile(vClients);
	int Index = FindClientIndexInVector(vClients, AccountNumber);

	cout << "The Following are the client data : ";
	PrintClientData(vClients[Index]);
	
	int DepositAmmount = 0;
	cout << "Please enter a deposit ammount : ";
	cin >> DepositAmmount;

	char SureDeposit;
	cout << "Are you sure you want to add " << DepositAmmount << "to this Account ? y/n: ";
	cin >> SureDeposit;
	if (toupper(SureDeposit) == 'Y') {
		vClients[Index].AccountBalance += DepositAmmount;
		WriteClientsToFile(vClients);
		cout << "The Account Balance after the addition is : " << vClients[Index].AccountBalance << endl;
	}
	else {
		return;
	}

}

void PrintWithdrawScreen() {

	string Withdraw = "Withdraw Screen";
	int LineLength = 10 + Withdraw.length() + 10;

	cout << "\n";

	cout << string(LineLength, '-') << endl;
	cout << string(10, ' ') << Withdraw << string(10, ' ') << endl;
	cout << string(LineLength, '-') << endl;

	cout << "\n\n";
}

void WithdrawFromClient() {

	PrintWithdrawScreen();

	string AccountNumber = ReadAccountNumber();

	vector <stClientData> vClients;
	ReadClientsFromFile(vClients);
	
	int Index = FindClientIndexInVector(vClients,AccountNumber);

	cout << "The following are the clients details : \n";
	PrintClientData(vClients[Index]);

	int WithdrawAmmount = 0;
	cout << "Please enter withdraw ammount? ";
	cin >> WithdrawAmmount;

	while (WithdrawAmmount > vClients[Index].AccountBalance) {

		cout << "Ammount Exceeds the balance, you can withdraw up to : " << vClients[Index].AccountBalance << endl;
		cout << "Please enter another amount? ";
		cin >> WithdrawAmmount;
	}

	char SureWithdraw;
	cout << "Are you sure you want to withdraw " << WithdrawAmmount << " from this Account ? y/n: ";
	cin >> SureWithdraw;
	if (toupper(SureWithdraw) == 'Y') {
		vClients[Index].AccountBalance -= WithdrawAmmount;
		WriteClientsToFile(vClients);
		cout << "The Account Balance after the withdrawing is : " << vClients[Index].AccountBalance << endl;
	}
	else {
		return;
	}

}

long long SumOfTotalBalance(vector <stClientData>& vClients) {
	long long Sum = 0;

	for (stClientData& C : vClients) {
		Sum += C.AccountBalance;
	}

	return (long long)Sum;

}

void PrintClientBalanceTableHeader(int Count,int &LineLength) {
	const int totalWidth = 2 + 14 + 2 + 40 + 2 + 14 + 2; // compute rough width including separators
	cout << "\n\t\t\t\tBalance List (" << Count << ") Client(s)." << endl;
	cout << string(totalWidth, '_') << "\n\n";
	cout << "| " << setw(14) << left << "Account Number"
		<< "| " << setw(40) << left << "Client Name"
		<< "| " << setw(14) << left << "Balance"
		<< " |" << endl;
	cout << string(totalWidth, '_') << "\n";

	LineLength = totalWidth;
}

void PrintClientBalanceTable(vector <stClientData>& vClients) {
	
	int LineLength = 0;

	PrintClientBalanceTableHeader(vClients.size(),LineLength);
	if (vClients.size() != 0) {
		for (size_t i = 0; i < vClients.size(); i++) {
			PrintClientBalanceRow(vClients[i]);
			cout << "\n";
		}
	}
	
	string TotalBalanceString = "Total Balance = ";
	cout << "\n";
	cout << string((LineLength / 2) - (TotalBalanceString.length() / 2), ' ') << "Total Balance = " << SumOfTotalBalance(vClients);

}

void PrintClientBalanceRow(stClientData& Client) {
	cout << "| " << setw(14) << left << Client.AccountNumber;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(14) << left << Client.AccountBalance << " |";
}


void DisplayTotalBalance() {

	vector <stClientData> vClients;
	ReadClientsFromFile(vClients);
	PrintClientBalanceTable(vClients);

}

void PerformeTransaction(enTransactions Trans,bool &PerformeMore) {

	system("cls");

	switch (Trans) {
	case enTransactions::Deposit:
		DepositInClient();
		ReturnToTransactionsMainMenue();
		break;
	case enTransactions::Withdraw :
		WithdrawFromClient();
		ReturnToTransactionsMainMenue();
		break;
	case enTransactions::TotalBalance :
		DisplayTotalBalance();
		ReturnToTransactionsMainMenue();
		break;
	case enTransactions::MainMenue :
		PerformeMore = false;
		break;
	}
}

enTransactions ReadTheTransaction() {
	int n;
	cout << "Choose what do you want to do? [1 to 4]? ";
	cin >> n;
	return (enTransactions)n;
}

void PrintTransactionsMainMenue() {
	string MainMenue = "Transactions Main Menue";
	int LineLength = 16 + MainMenue.length() + 16;
	cout << '\n';
	cout << string(16, ' ') << MainMenue << endl;
	cout << string(LineLength, '=') << endl;
	cout << string(8, ' ') << "[1] Deposit.\n";
	cout << string(8, ' ') << "[2] Withdraw.\n";
	cout << string(8, ' ') << "[3] Total Balances\n";
	cout << string(8, ' ') << "[4] Main Menue.\n";
	cout << string(LineLength, '=') << endl;
}

void PerformeTransactions() {
	bool PerformeMore = true;

	while (PerformeMore) {
		enTransactions Trans;
		system("cls");
		PrintTransactionsMainMenue();
		Trans = ReadTheTransaction();
		PerformeTransaction(Trans,PerformeMore);
	}
}

void PerformeTheTask(enTasks Task) {

	system("cls");

	switch (Task) {
	case enTasks::ChowClientList:
        DisplayAllClientsFromFile();
		ReturnToMainMenue();
		break;
	case enTasks::AddNewClient:
        InteractiveAddMultipleClients();
		ReturnToMainMenue();
		break;
	case enTasks::DeleteClient:
        InteractiveDeleteMultipleClients();
		ReturnToMainMenue();
		break;
	case enTasks::FindClient:
        FindClientByAccountNumber();
		ReturnToMainMenue();
		break;
	case enTasks::UpdateClientInfo:
        UpdateClientInformation();
		ReturnToMainMenue();
		break;
	case enTasks::Transactions :
		PerformeTransactions();
		ReturnToMainMenue();
	case enTasks::ManageUsers:
		break;
	case enTasks::LogOut :
		LoginAction();
		break;
		
	}

}

void ReadUsersFromFile(vector<stUserAccount>& vUsers) {
	fstream MyFile;
	MyFile.open(UsersFile, ios::in);
	
	if (MyFile.is_open()) {
		string line;
		stUserAccount UA;

		while (getline(MyFile, line)) {
			UA = ParseRecordToUserAccount(line, "/#/");
			vUsers.push_back(UA);
		}

		MyFile.close();
	}

	
 }

void PrintloginScreen() {
	string LoginScreen = "Login Screen";
	int LineLength = 10 + LoginScreen.length() + 10;

	cout << string(LineLength, '=') << endl;
	cout << string(10, ' ') << LoginScreen << endl;
	cout << string(LineLength, '=') << endl;
}

string CreatUserAccountRecord(stUserAccount UserAccount) {
	string SUA = "";
	SUA += UserAccount.UserName + "/#/"
		+ UserAccount.Passowrd + "/#/"
		+ to_string(UserAccount.Permission);

	return SUA;
}

stUserAccount ReadUserAccount() {
	stUserAccount UserAccount;
	cout << "Enter Username? ";
	cin >> UserAccount.UserName;
	cout << "Enter Passoerd? ";
	cin >> UserAccount.Passowrd;

	return UserAccount;
}

stUserAccount ParseRecordToUserAccount(string Record, string Diameter = "/#/") {

	vector<string> vRecordData = { "" };
	vRecordData = SplitString(Record, Diameter);

	stUserAccount UA;

	if (vRecordData.size() == 0) {
		return UA;
	}

	UA.UserName = vRecordData[0];

	if (vRecordData.size() >= 2) {
		UA.Passowrd = vRecordData[1];
	}
	if (vRecordData.size() >= 3) {
		UA.Permission = enMainMenuPermissions(stoi(vRecordData[2]));
	}

	return UA;
}


bool IfTheUsernameAndPassFound(stUserAccount UserAccount) {
	
	string Record = "";

	fstream MyFile;
	MyFile.open(UsersFile, ios::in);

	if (MyFile.is_open()) {
		string line;
		stUserAccount UA = {};

		while (getline(MyFile, line)) {
			UA = ParseRecordToUserAccount(line, "/#/");
			if (UA.UserName == UserAccount.UserName && UA.Passowrd == UserAccount.Passowrd);
				return true;
		}

		MyFile.close();
		
	}
	return false;
}

void LoginToAccount() {

	CurrentUser = ReadUserAccount();

	while (!IfTheUsernameAndPassFound(CurrentUser)) {
		system("cls");
		PrintloginScreen();
		cout << "Invalid Username/Passowrd!\n";
		CurrentUser = ReadUserAccount();
	}

}

void LoginAction() {
	system("cls");
	PrintloginScreen();

	LoginToAccount();
}

void PrintManageUsresMainMenue() {

	string MainMenue = "Manage Users Main Menue";
	int LineLength = 10 + MainMenue.length() + 10;

	cout << string(LineLength, '=') << endl;
	cout << string(10, ' ') << MainMenue << endl;
	cout << string(LineLength, '=') << endl;

	cout << string(5, ' ') << "[1] List Users.\n";
	cout << string(5, ' ') << "[2] Add New User.\n";
	cout << string(5, ' ') << "[3] Delete User.\n";
	cout << string(5, ' ') << "[4] Update User.\n";
	cout << string(5, ' ') << "[5] Find User.\n";
	cout << string(5, ' ') << "[6] Main Menue.\n";
	cout << string(LineLength, '=') << endl;
}

enUsersTransactions ReadUsersTransactions() {
	int n;
	cout << "\nEnter what you want to do (1 to 6) : ";
	cin >> n;
	return enUsersTransactions(n);
}

void PrintUserTableHeader(int Users) {
	string Title = "Users List (" + to_string(Users) + ") User.";
	int LineLength = 15 + Title.length() + 15;
	cout << string(15, ' ') << Title  << endl;
	cout << string(LineLength, '_') << endl;
	cout << " |" << setw(14) << left << "User Name";
	cout << " |" << setw(10) << left << "Passowrd";
	cout << " |" << setw(14) << left << "Permission" << endl;
	
}

void PrintUserRow(stUserAccount& UA) {
	cout << " |" << setw(14) << left << UA.UserName;
	cout << " |" << setw(14) << left << UA.Passowrd;
	cout << " |" << setw(14) << left << UA.Permission;
}

void PrintUsersListTable(vector <stUserAccount>& vUsers) {
	PrintUserTableHeader(vUsers.size());

	for (int i = 0; i < vUsers.size(); i++) {
		PrintUserRow(vUsers[i]);
		cout << "\n";
	}
}

void DisplayAllUsersAccount() {
	vector <stUserAccount> vUsers;
	ReadUsersFromFile(vUsers);
	PrintUsersListTable(vUsers);
}

void ReturnToUsersActionsMainMenu() {
	cout << "\nPress Any Key to return to Users Actions Main Menue....\n";
	system("pause>0");
}

void PrintAddNewUserScreen() {
	string Title = "Add New User Screen";
	int LineLength = 10 + Title.length() + 10;
	cout << string(LineLength, '-') << endl;
	cout << string(10, ' ') << Title << endl;
	cout << string(LineLength, '-') << endl;
}

bool IfUsernameFoundInFile(string Username) {
	fstream MyFile;
	MyFile.open(UsersFile, ios::in);

	if (MyFile.is_open()) {
		string line;
		stUserAccount UA;
		while (getline(MyFile, line)) {
			UA = ParseRecordToUserAccount(line, "/#/");
			if (UA.UserName == Username)
				return true;
		}
		MyFile.close();
	}
	return false;
}

enMainMenuPermissions ReadUserPermission() {
	enMainMenuPermissions Permission = pNoThing;
	char chArr[8];int count = 0;
	char All;

	cout << "\nDo you want to gave this user full action? y/n? ";
	cin >> All;
	if (All == 'y')
		return enMainMenuPermissions(-1);
		
	cout << "\nWhat the permission you want to gave it to this user ? \n";
	cout << "[1] Show Client List ? y/n ? ";
	cin >> chArr[count++];
	cout << "\n[2] Add New Client ? y/n ?";
	cin >> chArr[count++];
	cout << "\n[3] Delete Client ? y/n ?";
	cin >> chArr[count++];
	cout << "\n[4] Update Client ? y/n ?";
	cin >> chArr[count++];
	cout << "\n[5] Find Client ? y/n ?";
	cin >> chArr[count++];
	cout << "\n[6] Transactions ? y/n ?";
	cin >> chArr[count++];
	cout << "\n[7] Manage Users ? y/n ?";
	cin >> chArr[count++];

	int p = 1;
	for (int i = 0; i < count; i++) {
		if (chArr[i] == 'y')
			Permission = enMainMenuPermissions(Permission | enMainMenuPermissions(p));
		p *= 2;
	}

	return Permission;
}

stUserAccount ReadNewUserInfo() {
	stUserAccount UA;
	cout << "Adding New User: \n\n";
	UA = ReadUserAccount();
	
	while (IfUsernameFoundInFile(UA.UserName)) {
		system("cls");
		PrintAddNewUserScreen();
		cout << "The Username is already found in the file!!\n";
		cout << "Please enter another one...\n";
		UA = ReadUserAccount();
	}

	UA.Permission = ReadUserPermission();
	
}

void AppendTheNewUserAccountRecordToFile(string UserAccountRecord) {
	fstream MyFile;
	MyFile.open(UsersFile, ios::out | ios::app);

	if (MyFile.is_open()) {
		MyFile << UserAccountRecord << endl;
	}
}

void InteractiveAddSingleUserAccount() {
	stUserAccount UserAccount = ReadNewUserInfo();
	AppendTheNewUserAccountRecordToFile(CreatUserAccountRecord(UserAccount));
}

void InteractiveAddMultiUsersAccounts() {
	char AddMore = 'y';
	while (toupper(AddMore)) {
		system("cls");
		PrintAddNewUserScreen();
		InteractiveAddSingleUserAccount();
		PrintSuccesOfTheOperationMessage("The operation completed succefully!!");
		cout << "\nDo you want to add more accounts ? y/n ? ";
		cin >> AddMore;
	}
}

void PrintDeleteScreen() {
	string Title = "Delete User";
	int LineLength = 10 + Title.length() + 10;
	cout << string(LineLength, '-') << endl;
	cout << string(10, ' ') << Title << endl;
	cout << string(LineLength, '-') << endl;

}

void MarkUserAccountForDelete(vector <stUserAccount>& vUsers, string Username) {
	for (int i = 0; i < vUsers.size(); i++) {
		if (vUsers[i].UserName == Username)
			vUsers[i].MarkForDelete = true;
	}
}

void LoadUsersAccountsFromVectorToFile(vector<stUserAccount>& vUsers) {
	fstream MyFile;
	MyFile.open(UsersFile, ios::out);

	if (MyFile.is_open()) {
		string line;
		for (int i = 0; i < vUsers.size(); i++) {
			if (!vUsers[i].MarkForDelete) {
				line = CreatUserAccountRecord(vUsers[i]);
				MyFile << line << endl;
			}
		}
		MyFile.close();
	}

}

void InteractiveDeleteSingleUserAccount(vector <stUserAccount>& vUsers) {
	cout << "\nEnter the account you want to delete it : \n";
	stUserAccount UserAccountDelete = ReadUserAccount();

	while (!IfUsernameFoundInFile(UserAccountDelete.UserName)) {
		cout << "\nuncorrect Username/Passowrd!!\n";
		cout << "Please Enter Again...\n";
		UserAccountDelete = ReadUserAccount();
	}

	MarkUserAccountForDelete(vUsers, UserAccountDelete.UserName);
}

void InteractiveDeleteMultiUsersAccounts() {
	vector <stUserAccount> vUsers;
	ReadUsersFromFile(vUsers);
	char DeleteMore = 'y';

	while (DeleteMore == 'y') {
		system("cls");
		PrintDeleteScreen();
		InteractiveDeleteSingleUserAccount(vUsers);
		PrintSuccesOfTheOperationMessage("The operation completed succefully...");
		cout << "\nDo you want to delete more ? y/n ?";
		cin >> DeleteMore;
	}
	LoadUsersAccountsFromVectorToFile(vUsers);
}

void PrintUpdateUserAccountScreen() {
	string Title = "Update User Account";
	int LineLength = 10 + Title.length() + 10;
	cout << string(LineLength, '-') << endl;
	cout << string(10, ' ') << Title << endl;
	cout << string(LineLength, '-') << endl;
}

void UpdateAccountInfo(stUserAccount& UAA) {
	cout << "\nEnter the new passowrd : ";
	cin >> UAA.Passowrd;
	cout << "Enter the new permission : \n";
	UAA.Permission = ReadUserPermission();
}

void ReplaceAccountWithUpdatedAccount(vector<stUserAccount>& vUsers,stUserAccount UAA) {
	for (int i = 0; i < vUsers.size(); i++) {
		if (vUsers[i].UserName == UAA.UserName) {
			vUsers[i] = UAA;
			break;
		}
	}
}

void UpdateUserAccount() {
	PrintUpdateUserAccountScreen();
	stUserAccount UserAccountUpdate = ReadUserAccount();

	while (!IfTheUsernameAndPassFound(UserAccountUpdate)) {
		cout << "\nUncorrect Username/Passowrd!!\n";
		cout << "Please Enter a correct one...\n";
		UserAccountUpdate = ReadUserAccount();
	}
	UpdateAccountInfo(UserAccountUpdate);
	PrintSuccesOfTheOperationMessage("The Update Opration are completed succefully..");
	vector<stUserAccount> vUsers;
	ReadUsersFromFile(vUsers);
	ReplaceAccountWithUpdatedAccount(vUsers,UserAccountUpdate);
	LoadUsersAccountsFromVectorToFile(vUsers);
}

void PrintFindUserScreen() {
	string Title = "Find User";
	int LineLength = 10 + Title.length() + 10;
	cout << string(LineLength, '-') << endl;
	cout << string(10, ' ') << endl;
	cout << string(LineLength, '-') << endl;
}

string ReadUsername() {
	string username;
	cout << "\nEnetr the username you want it : ";
	cin >> username;
	return username;
}

void PrintSingleUserAccount(stUserAccount& UA) {
	
	cout << "\n\n";
	cout << string(25, '=') << endl;
	cout << "        Username: " << UA.UserName << endl;
	cout << "        Passowrd: " << UA.Passowrd << endl;
	cout << string(25, '=') << endl;
	cout << "\n\n";
 }

stUserAccount CopyUserAccountFromVector(vector<stUserAccount> vUsers,string Username) {
	for (int i = 0; i < vUsers.size(); i++) {
		if (vUsers[i].UserName == Username)
			return vUsers[i];
	}
}

void FindUserAccountFromFile() {
	PrintFindUserScreen();
	string UserName = ReadUsername();

	while (!IfUsernameFoundInFile(UserName)) {
		cout << "\nThe Username you enterd it didnt found!!\n";
		cout << "Please enter anothe one...\n";
		UserName = ReadUsername();
	}

	vector <stUserAccount> vUsers;
	ReadUsersFromFile(vUsers);
	stUserAccount UA = CopyUserAccountFromVector(vUsers, UserName);
	PrintSingleUserAccount(UA);
}

void PerformeUserTransactions(enUsersTransactions UserTransaction) {

	switch (UserTransaction) {
	case enUsersTransactions::ListUsers :
		DisplayAllUsersAccount();
		ReturnToUsersActionsMainMenu();
		break;
	case enUsersTransactions::AddNewuser:
		InteractiveAddMultiUsersAccounts();
		ReturnToUsersActionsMainMenu();
		break;
	case enUsersTransactions::DeleteUser:
		InteractiveDeleteMultiUsersAccounts();
		ReturnToUsersActionsMainMenu();
		break;
	case enUsersTransactions::UpdateUser:
		UpdateUserAccount();
		ReturnToUsersActionsMainMenu();
		break;
	case enUsersTransactions::Finduser:
		FindUserAccountFromFile();
		ReturnToUsersActionsMainMenu();
		break;
	case enUsersTransactions::MainMenue:
		ReturnToMainMenue();
		break;
	}
}

void PerformeUsersTransactions() {

	bool PerformeMore = true;
	while (PerformeMore) {
		system("cls");
		PrintManageUsresMainMenue();
		enUsersTransactions UT = ReadUsersTransactions();
		PerformeUserTransactions(UT);
	}
}

enTasks WhatTheTask() {

	int n;
	cout << "\nEnter The number (1 to 7) ? ";
	cin >> n;
	return (enTasks)n;

}

void PrintTheMainMenu() {

	system("cls");

	string MainMenu = "Main Menue Screen";
	int LengthOfLine = 10 + MainMenu.length() + 10;
	cout << string(LengthOfLine, '=') << endl;
	cout << string(10, ' ') << MainMenu << string(10, ' ') << endl;
	cout << string(LengthOfLine, '=') << endl;
	cout << string(5, ' ') << "[1] Show Client List.\n";
	cout << string(5, ' ') << "[2] Add New Client.\n";
	cout << string(5, ' ') << "[3] Delete Client.\n";
	cout << string(5, ' ') << "[4] Update Client\n";
	cout << string(5, ' ') << "[5] Find Client.\n";
	cout << string(5, ' ') << "[6] Transactions.\n";
	cout << string(5, ' ') << "[7] Exit.\n";
	cout << string(LengthOfLine, '=') << endl;

}

void PrintEndCaption() {

	system("cls");

	string s = "\nThe Programe end ...........\n";
	int LengthOfLine = s.length() + 5 + 5;

	cout << string(LengthOfLine, '=') << endl;
	cout << string(5, ' ') << "\nThe Programe end ...........\n" << string(5, ' ') << endl;
	cout << string(LengthOfLine, '=') << endl;
}

void StartTheProgram() {
	LoginAction();

	while (true) {
		
		PrintTheMainMenu();

		enTasks Task;
		Task = WhatTheTask();
        PerformeTheTask(Task);
		
	}



}