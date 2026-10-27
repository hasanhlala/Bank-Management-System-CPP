#pragma once
#include <string>
#include <vector>
using namespace std;

enum enTasks {
	tShowClientList = 1,
	tAddNewClient = 2,
	tDeleteClient = 3,
	tUpdateClient = 4,
	tFindClient = 5,
	tTransactions = 6,
	tManageUsers = 7,
	tLogOut = 8
};

enTasks WhatTheTask();
void PerformeTheTask(enTasks Task);
void PrintTheMainMenu();
void PrintEndCaption();
void StartTheProgram();
