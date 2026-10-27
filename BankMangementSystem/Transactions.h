#pragma once
#include <string>
#include <vector>
#include "Clients.h"
using namespace std;

enum enTransactions {
	trDeposit = 1,
	trWithdraw = 2,
	trTotalBalance = 3,
	trMainMenu = 4
};

void PrintDepositScreen();
void ReturnToTransactionsMainMenue();
void DepositInClient();
void PrintWithdrawScreen();
void WithdrawFromClient();
long long SumOfTotalBalance(vector <stClientData>& vClients);
void PrintClientBalanceTableHeader(int Count,int &LineLength);
void PrintClientBalanceTable(vector <stClientData>& vClients);
void PrintClientBalanceRow(stClientData& Client);
void DisplayTotalBalance();
void PerformeTransaction(enTransactions Trans,bool &PerformeMore);
enTransactions ReadTheTransaction();
void PrintTransactionsMainMenue();
void PerformeTransactions();
