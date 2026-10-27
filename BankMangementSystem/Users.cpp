#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include "Users.h"
#include "Clients.h"
#include "Common.h"
using namespace std;

stUserAccount CurrentUser;

bool CheckAccesPermission(enMainMenuPermissions Permission) {
	if (CurrentUser.Permission == enMainMenuPermissions::pAll)
		return true;
	return (CurrentUser.Permission & Permission) == Permission;
}

bool HasAccessOrDeny(enMainMenuPermissions Permission) {
	if (CheckAccesPermission(Permission))
		return true;

	string Message = "Access Denied! You don't have permission to do this.";
	int LineLength = Message.length() + 10;
	cout << string(LineLength, '-') << endl;
	cout << string(5, ' ') << Message << endl;
	cout << string(LineLength, '-') << endl;
	cout << "Please contact your admin.\n";
	return false;
}

void ReadUsersFromFile(vector<stUserAccount>& vUsers) {
	fstream MyFile;
	MyFile.open(UsersFile, ios::in);
	
	if (MyFile.is_open()) {
		string line;
		stUserAccount UA;

		while (getline(MyFile, line)) {
			UA = ParseRecordToUserAccount(line, "/#/");
			if (!line.empty())
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
		+ to_string((int)UserAccount.Permission);

	return SUA;
}

stUserAccount ReadUserAccount() {
	stUserAccount UserAccount;
	cout << "Enter Username? ";
	cin >> UserAccount.UserName;
	cout << "Enter Password? ";
	cin >> UserAccount.Passowrd;

	return UserAccount;
}

stUserAccount ParseRecordToUserAccount(string Record, string Diameter) {

	vector<string> vRecordData = SplitString(Record, Diameter);

	stUserAccount UA;

	if (vRecordData.empty()) {
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

	fstream MyFile;
	MyFile.open(UsersFile, ios::in);

	if (MyFile.is_open()) {
		string line;
		stUserAccount UA;

		while (getline(MyFile, line)) {
			UA = ParseRecordToUserAccount(line, "/#/");
			if (UA.UserName == UserAccount.UserName && UA.Passowrd == UserAccount.Passowrd) {
				MyFile.close();
				return true;
			}
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
		cout << "Invalid Username/Password!\n";
		CurrentUser = ReadUserAccount();
	}

	// load the full account (with its permissions) from the file
	vector<stUserAccount> vUsers;
	ReadUsersFromFile(vUsers);
	for (int i = 0; i < vUsers.size(); i++) {
		if (vUsers[i].UserName == CurrentUser.UserName) {
			CurrentUser = vUsers[i];
			break;
		}
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
	char Answer;

	cout << "\nDo you want to give this user full access? y/n? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
		return enMainMenuPermissions::pAll;

	const string Questions[7] = { "Show Client List", "Add New Client", "Delete Client",
		"Update Client", "Find Client", "Transactions", "Manage Users" };

	int Permission = 0;

	cout << "\nWhat permissions do you want to give this user ? \n";
	for (int i = 0; i < 7; i++) {
		cout << "[" << i + 1 << "] " << Questions[i] << " ? y/n ? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
			Permission |= (1 << i);
	}

	return (enMainMenuPermissions)Permission;
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

	return UA;
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
	while (toupper(AddMore) == 'Y') {
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
	string UserName = ReadUsername();

	while (!IfUsernameFoundInFile(UserName) || UserName == "Admin") {
		if (UserName == "Admin")
			cout << "\nThe Admin account can't be deleted!!\n";
		else
			cout << "\nThe Username was not found!!\n";
		cout << "Please Enter Again...\n";
		UserName = ReadUsername();
	}

	MarkUserAccountForDelete(vUsers, UserName);
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
	string UserName = ReadUsername();

	while (!IfUsernameFoundInFile(UserName)) {
		cout << "\nThe Username was not found!!\n";
		cout << "Please Enter a correct one...\n";
		UserName = ReadUsername();
	}

	stUserAccount UserAccountUpdate;
	UserAccountUpdate.UserName = UserName;
	UpdateAccountInfo(UserAccountUpdate);

	vector<stUserAccount> vUsers;
	ReadUsersFromFile(vUsers);
	ReplaceAccountWithUpdatedAccount(vUsers, UserAccountUpdate);
	LoadUsersAccountsFromVectorToFile(vUsers);

	if (UserAccountUpdate.UserName == CurrentUser.UserName)
		CurrentUser = UserAccountUpdate;

	PrintSuccesOfTheOperationMessage("The Update Opration are completed succefully..");
}

void PrintFindUserScreen() {
	string Title = "Find User";
	int LineLength = 10 + Title.length() + 10;
	cout << string(LineLength, '-') << endl;
	cout << string(10, ' ') << Title << endl;
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
	return stUserAccount();
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

void PerformeUserTransactions(enUsersTransactions UserTransaction, bool& PerformeMore) {

	system("cls");

	switch (UserTransaction) {
	case enUsersTransactions::utListUsers:
		DisplayAllUsersAccount();
		ReturnToUsersActionsMainMenu();
		break;
	case enUsersTransactions::utAddNewUser:
		InteractiveAddMultiUsersAccounts();
		ReturnToUsersActionsMainMenu();
		break;
	case enUsersTransactions::utDeleteUser:
		InteractiveDeleteMultiUsersAccounts();
		ReturnToUsersActionsMainMenu();
		break;
	case enUsersTransactions::utUpdateUser:
		UpdateUserAccount();
		ReturnToUsersActionsMainMenu();
		break;
	case enUsersTransactions::utFindUser:
		FindUserAccountFromFile();
		ReturnToUsersActionsMainMenu();
		break;
	case enUsersTransactions::utMainMenu:
		PerformeMore = false;
		break;
	}
}

void PerformeUsersTransactions() {

	bool PerformeMore = true;
	while (PerformeMore) {
		system("cls");
		PrintManageUsresMainMenue();
		enUsersTransactions UT = ReadUsersTransactions();
		PerformeUserTransactions(UT, PerformeMore);
	}
}

void CreateDefaultAdminIfNoUsers() {
	vector<stUserAccount> vUsers;
	ReadUsersFromFile(vUsers);

	if (vUsers.empty()) {
		stUserAccount Admin;
		Admin.UserName = "Admin";
		Admin.Passowrd = "1234";
		Admin.Permission = enMainMenuPermissions::pAll;
		AppendTheNewUserAccountRecordToFile(CreatUserAccountRecord(Admin));
	}
}
