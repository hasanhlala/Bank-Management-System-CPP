#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include "Menus.h"
#include "Clients.h"
#include "Common.h"
#include "Transactions.h"
#include "Users.h"
using namespace std;

enTasks WhatTheTask() {

	int n;
	cout << "\nEnter The number (1 to 8) ? ";
	cin >> n;
	return (enTasks)n;

}

void PerformeTheTask(enTasks Task) {

	system("cls");

	switch (Task) {
	case enTasks::tShowClientList:
		if (HasAccessOrDeny(enMainMenuPermissions::pListClients))
			DisplayAllClientsFromFile();
		ReturnToMainMenue();
		break;
	case enTasks::tAddNewClient:
		if (HasAccessOrDeny(enMainMenuPermissions::pAddNewClient))
			InteractiveAddMultipleClients();
		ReturnToMainMenue();
		break;
	case enTasks::tDeleteClient:
		if (HasAccessOrDeny(enMainMenuPermissions::pDeleteClient))
			InteractiveDeleteMultipleClients();
		ReturnToMainMenue();
		break;
	case enTasks::tUpdateClient:
		if (HasAccessOrDeny(enMainMenuPermissions::pUpdateClient))
			UpdateClientInformation();
		ReturnToMainMenue();
		break;
	case enTasks::tFindClient:
		if (HasAccessOrDeny(enMainMenuPermissions::pFindClient))
			FindClientByAccountNumber();
		ReturnToMainMenue();
		break;
	case enTasks::tTransactions:
		if (HasAccessOrDeny(enMainMenuPermissions::pTransactions))
			PerformeTransactions();
		else
			ReturnToMainMenue();
		break;
	case enTasks::tManageUsers:
		if (HasAccessOrDeny(enMainMenuPermissions::pManageUsers))
			PerformeUsersTransactions();
		else
			ReturnToMainMenue();
		break;
	case enTasks::tLogOut:
		LoginAction();
		break;
	}

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
	cout << string(5, ' ') << "[7] Manage Users.\n";
	cout << string(5, ' ') << "[8] Logout.\n";
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
	CreateDefaultAdminIfNoUsers();
	LoginAction();

	while (true) {
		
		PrintTheMainMenu();

		enTasks Task;
		Task = WhatTheTask();
        PerformeTheTask(Task);
		
	}



}
