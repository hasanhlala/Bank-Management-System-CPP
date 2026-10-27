#pragma once
#include <string>
#include <vector>
#include "ClientsATM.h"
using namespace std;

enum enTransactions {
	trDeposit = 1,
	trWithdraw = 2,
	trUserBalance = 3,
	trLogout = 4
};

void PrintDepositScreen();
void ReturnToTransactionsMainMenue();
void DepositInClient();
void PrintWithdrawScreen();
void WithdrawFromClient();
long long SumOfTotalBalance(vector <stClientData>& vClients);
void PrintClientBalanceTableHeader(int Count, int& LineLength);
void PrintClientBalance(vector <stClientData>& vClients);
void PrintClientBalanceRow(stClientData& Client);
void DisplayUserBalance();
void PerformeTransaction(enTransactions Trans, bool& PerformeMore);
enTransactions ReadTheTransaction();
void PrintTransactionsMainMenue();
void PerformeTransactions();

