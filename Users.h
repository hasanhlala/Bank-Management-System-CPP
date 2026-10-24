#pragma once
#include <string>
#include <vector>
using namespace std;

enum enMainMenuPermissions {
	pAll = -1,
	pNoThing = 0,
	pListClients = 1,
	pAddNewClient = 2,
	pDeleteClient = 4,
	pUpdateClient = 8,
	pFindClient = 16,
	pTransactions = 32,
	pManageUsers = 64
};

struct stUserAccount {
	string UserName;
	string Passowrd;
	enMainMenuPermissions Permission = enMainMenuPermissions::pNoThing;
	bool MarkForDelete = false;
};

enum enUsersTransactions {
	utListUsers = 1,
	utAddNewUser = 2,
	utDeleteUser = 3,
	utUpdateUser = 4,
	utFindUser = 5,
	utMainMenu = 6
};

extern stUserAccount CurrentUser;   // the user who is logged in now

bool CheckAccesPermission(enMainMenuPermissions Permission);
bool HasAccessOrDeny(enMainMenuPermissions Permission);
void ReadUsersFromFile(vector<stUserAccount>& vUsers);
void PrintloginScreen();
string CreatUserAccountRecord(stUserAccount UserAccount);
stUserAccount ReadUserAccount();
stUserAccount ParseRecordToUserAccount(string Record, string Diameter = "/#/");
bool IfTheUsernameAndPassFound(stUserAccount UserAccount);
void LoginToAccount();
void LoginAction();
void PrintManageUsresMainMenue();
enUsersTransactions ReadUsersTransactions();
void PrintUserTableHeader(int Users);
void PrintUserRow(stUserAccount& UA);
void PrintUsersListTable(vector <stUserAccount>& vUsers);
void DisplayAllUsersAccount();
void ReturnToUsersActionsMainMenu();
void PrintAddNewUserScreen();
bool IfUsernameFoundInFile(string Username);
enMainMenuPermissions ReadUserPermission();
stUserAccount ReadNewUserInfo();
void AppendTheNewUserAccountRecordToFile(string UserAccountRecord);
void InteractiveAddSingleUserAccount();
void InteractiveAddMultiUsersAccounts();
void PrintDeleteScreen();
void MarkUserAccountForDelete(vector <stUserAccount>& vUsers, string Username);
void LoadUsersAccountsFromVectorToFile(vector<stUserAccount>& vUsers);
void InteractiveDeleteSingleUserAccount(vector <stUserAccount>& vUsers);
void InteractiveDeleteMultiUsersAccounts();
void PrintUpdateUserAccountScreen();
void UpdateAccountInfo(stUserAccount& UAA);
void ReplaceAccountWithUpdatedAccount(vector<stUserAccount>& vUsers,stUserAccount UAA);
void UpdateUserAccount();
void PrintFindUserScreen();
string ReadUsername();
void PrintSingleUserAccount(stUserAccount& UA);
stUserAccount CopyUserAccountFromVector(vector<stUserAccount> vUsers,string Username);
void FindUserAccountFromFile();
void PerformeUserTransactions(enUsersTransactions UserTransaction, bool& PerformeMore);
void PerformeUsersTransactions();
void CreateDefaultAdminIfNoUsers();
