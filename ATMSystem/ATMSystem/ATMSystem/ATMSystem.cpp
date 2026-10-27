// ATMSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include "ClientsATM.h"
#include "CommonATM.h"
#include "TransactionATM.h"

using namespace std;


void PrintLoginScreen() {
    string Title = "Login";
    int LineLength = 10 + Title.length() + 10;

    cout << string(LineLength, '-') << endl;
    cout << string(10, ' ') << Title << endl;
    cout << string(LineLength, '-') << endl;

}

void Login() {
    PrintLoginScreen();
    ReadClientAccountNumberAndPinCode();

    while (!CheckIfClientIsFoundInFileAndLoadData()) {
        system("cls");
        PrintLoginScreen();
        cout << "\nWrong AccountNumber/PIN code!!!\n";
        cout << "Please enter a rigth client info...\n";
        ReadClientAccountNumberAndPinCode();
    }

}

void StartATMSystemProgram() {
    bool PerformeMore = true;
    Login();
    while (true) {
        system("cls");
        PrintTransactionsMainMenue();
        enTransactions Trans = ReadTheTransaction();
        PerformeTransaction(Trans, PerformeMore);
    }

}

























// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
