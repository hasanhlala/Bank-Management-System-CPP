#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include "CommonATM.h"
#include "TransactionATM.h"
#include "ClientsATM.h"

extern stClientData CurrentClient;
using namespace std;

void PrintDepositScreen() {
	string DepositScreen = "Deposit Screen";
	int LineLength = 10 + DepositScreen.length() + 10;

	cout << string(LineLength, '-') << endl;
	cout << string(10, ' ') << DepositScreen << endl;
	cout << string(LineLength, '-') << endl;
}

void ReturnToTransactionsMainMenue() {
	cout << "\nPress Any Key to return to Transactions Main Menue....\n";
	system("pause>0");
}

void DepositInClient() {
	PrintDepositScreen();
	cout << "\n";

	cout << "The Following are the client data : ";
	PrintClientData(CurrentClient);

	int DepositAmmount = 0;
	cout << "Please enter a deposit ammount : ";
	cin >> DepositAmmount;

	char SureDeposit;
	cout << "Are you sure you want to add " << DepositAmmount << " to this Account ? y/n: ";
	cin >> SureDeposit;
	if (toupper(SureDeposit) == 'Y') {
		CurrentClient.AccountBalance += DepositAmmount;
		vector <stClientData> vClients;
		ReadClientsFromFile(vClients);
		int Index = FindClientIndexInVector(vClients, CurrentClient.AccountNumber);
		vClients[Index] = CurrentClient;
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

	cout << "The following are the clients details : \n";
	PrintClientData(CurrentClient);

	int WithdrawAmmount = 0;
	cout << "Please enter withdraw ammount? ";
	cin >> WithdrawAmmount;

	while (WithdrawAmmount > CurrentClient.AccountBalance) {

		cout << "Ammount Exceeds the balance, you can withdraw up to : " << CurrentClient.AccountBalance << endl;
		cout << "Please enter another amount? ";
		cin >> WithdrawAmmount;
	}

	char SureWithdraw;
	cout << "Are you sure you want to withdraw " << WithdrawAmmount << " from this Account ? y/n: ";
	cin >> SureWithdraw;
	if (toupper(SureWithdraw) == 'Y') {
		CurrentClient.AccountBalance -= WithdrawAmmount;

		vector <stClientData> vClients;
		ReadClientsFromFile(vClients);
		int Index = FindClientIndexInVector(vClients, CurrentClient.AccountNumber);
		vClients[Index] = CurrentClient;
		WriteClientsToFile(vClients);
		cout << "\nThe Account Balance after the withdrawing is : " << vClients[Index].AccountBalance << endl;
	}
	else {
		return;
	}

}

void PrintClientBalanceTableHeader(int Count, int& LineLength) {
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

void PrintClientBalance(vector <stClientData>& vClients) {

	int LineLength = 0;

	PrintClientBalanceTableHeader(vClients.size(), LineLength);
	if (vClients.size() != 0) {
		for (size_t i = 0; i < vClients.size(); i++) {
			if (vClients[i].AccountNumber == CurrentClient.AccountNumber) {
				PrintClientBalanceRow(vClients[i]);
				cout << "\n";
				break;
			}
		}
		cout << string(LineLength, '_') << endl;
	}

}

void PrintClientBalanceRow(stClientData& Client) {
	cout << "| " << setw(14) << left << Client.AccountNumber;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(14) << left << Client.AccountBalance << " |";
}

void DisplayUserBalance() {

	vector <stClientData> vClients;
	ReadClientsFromFile(vClients);
	PrintClientBalance(vClients);

}

void PerformeTransaction(enTransactions Trans, bool& PerformeMore) {

	system("cls");

	switch (Trans) {
	case enTransactions::trDeposit:
		DepositInClient();
		ReturnToTransactionsMainMenue();
		break;
	case enTransactions::trWithdraw:
		WithdrawFromClient();
		ReturnToTransactionsMainMenue();
		break;
	case enTransactions::trUserBalance:
		DisplayUserBalance();
		ReturnToTransactionsMainMenue();
		break;
	case enTransactions::trLogout:
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
	cout << string(8, ' ') << "[3] User Balances.\n";
	cout << string(8, ' ') << "[4] Logout.\n";
	cout << string(LineLength, '=') << endl;
}

void PerformeTransactions() {
	bool PerformeMore = true;

	while (PerformeMore) {
		enTransactions Trans;
		system("cls");
		PrintTransactionsMainMenue();
		Trans = ReadTheTransaction();
		PerformeTransaction(Trans, PerformeMore);
	}
}
