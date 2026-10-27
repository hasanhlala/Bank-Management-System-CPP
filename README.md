# Bank Management System (C++)

<p align="center">
  Two console-based banking applications written in C++:<br>
  a full <b>Bank Management System</b> with user accounts and permissions for bank employees,<br>
  and a simplified <b>ATM System</b> for clients. Both use file-based storage.
</p>

<p align="center">
  <img alt="C++" src="https://img.shields.io/badge/C%2B%2B-Console%20App-00599C?logo=cplusplus&logoColor=white">
  <img alt="Platform" src="https://img.shields.io/badge/Platform-Windows-0078D6?logo=windows&logoColor=white">
  <img alt="IDE" src="https://img.shields.io/badge/IDE-Visual%20Studio%202022-5C2D91?logo=visualstudio&logoColor=white">
  <img alt="Version" src="https://img.shields.io/badge/version-4.0-success">
</p>

---

## Table of contents
- [Overview](#overview)
- [Features](#features)
- [Screenshots](#screenshots)
- [Getting started](#getting-started)
- [Usage](#usage)
- [Data format](#data-format)
- [Project structure](#project-structure)
- [Versions](#versions)
- [What I learned](#what-i-learned)
- [Roadmap](#roadmap)
- [Credits](#credits)
- [Author](#author)

## Overview

This repository simulates the core of a small bank system. It contains **two apps** that share the same client data file (`ClientsData`) and the same client structure:

| App | Used by | What it does |
|---|---|---|
| **Bank Management System** | Bank employee | Login with a user account, then manage clients, transactions and users according to the user's permissions |
| **ATM System** | Bank client | Logs in with account number and PIN code, then deposits, withdraws and checks the balance |

All data is stored in plain text files, so no database is required.

It started as the end-of-course project for Course 7 of the Programming Advices C++ track (v1.0), was extended with a transactions module (v2.0) and a user and permissions system (v3.0), and now includes the ATM System (v4.0).

## Features

### Bank Management System

**Login and users (v3.0)**
- Employee login with username and password
- A default `Admin` account is created automatically on the first run when no users exist
- **Manage Users:** list, add, delete, update and find users
- The `Admin` account cannot be deleted
- Usernames must be unique

**Permissions (v3.0)**
- Every user has either full access or a custom set of permissions (show clients, add, delete, update, find, transactions, manage users)
- A user without permission sees an "Access Denied" message instead of the screen
- Permissions are stored as bit flags in one number

**Client management (v1.0)**
- Add new clients, with a duplicate account number check
- Show all clients in a formatted table
- Update client information
- Delete clients, with confirmation
- Find a client by account number

**Transactions (v2.0)**
- **Deposit:** add money to a client account
- **Withdraw:** withdraw money, blocked when the amount exceeds the balance
- **Total Balances:** list every client's balance with the total sum
- Y/N confirmation before every transaction
- Input validation for the account number and withdraw amount

**Logout** returns to the login screen so another user can sign in.

### ATM System (v4.0)

- **Login** with account number and PIN code. A wrong pair shows an error and asks again
- **Deposit:** shows the client's data, asks for the amount and a Y/N confirmation, then saves the new balance to the file
- **Withdraw:** blocked when the amount is higher than the balance, with a Y/N confirmation before saving
- **User Balances:** shows the logged-in client's account number, name and balance
- **Logout** from the transactions menu
- Reads and writes the same `ClientsData` file as the Bank Management System

## Screenshots

| Main menu | Transactions menu |
|:---:|:---:|
| ![Main menu](screenshots/main-menu.png) | ![Transactions menu](screenshots/transactions-menu.png) |

## Getting started

### Requirements
- Windows
- Visual Studio 2022 with the **Desktop development with C++** workload

> The programs use `system("cls")` and `system("pause")`, so they target Windows.

### Build and run
```bash
git clone https://github.com/hasanhlala/Bank-Management-System-CPP.git
```
1. Open the `.sln` file inside the folder of the app you want (`BankMangementSystem` or `ATMSystem`) in Visual Studio.
2. Choose **Debug | x64**.
3. Press **Ctrl + F5** to build and run.

### First login (Bank Management System)

On the first run the program creates the default account:

| Username | Password | Permissions |
|---|---|---|
| `Admin` | `1234` | Full access |

Sign in with it, then open **Manage Users** to create your own accounts and change the password.

> The ATM System can only log in clients that already exist in `ClientsData`. Add clients first with the Bank Management System, or use the sample data in the `Data` folder.

## Usage

### Bank Management System

The program starts with the login screen:

```
==============================
          Login Screen
==============================
Enter Username?
Enter Password?
```

After a successful login, the main menu is shown:

```
=====================================
          Main Menue Screen
=====================================
     [1] Show Client List.
     [2] Add New Client.
     [3] Delete Client.
     [4] Update Client
     [5] Find Client.
     [6] Transactions.
     [7] Manage Users.
     [8] Logout.
=====================================
```

**Transactions** opens a second menu:

```
     [1] Deposit.
     [2] Withdraw.
     [3] Total Balances
     [4] Main Menue.
```

**Manage Users** opens a third menu:

```
     [1] List Users.
     [2] Add New User.
     [3] Delete User.
     [4] Update User.
     [5] Find User.
     [6] Main Menue.
```

### ATM System

The program starts with the login screen:

```
-------------------------
          Login
-------------------------
Enter the account number:
Enter PIN code:
```

After a successful login, the client sees the transactions menu:

```
                Transactions Main Menue
=======================================================
        [1] Deposit.
        [2] Withdraw.
        [3] User Balances.
        [4] Logout.
=======================================================
Choose what do you want to do? [1 to 4]?
```

## Data format

Fields are separated by `/#/` and each record is stored on one line.

**Clients** (`ClientsData`, used by both apps):

```
AccountNumber/#/PinCode/#/Name/#/Phone/#/Balance
```

Example with sample data:

```
A101/#/1234/#/Sample Client/#/0999000000/#/5000
```

**Users** (`UsersFile`, used by the Bank Management System):

```
UserName/#/Password/#/Permission
```

Example:

```
Admin/#/1234/#/-1
```

The permission is `-1` for full access, or the sum of the values below:

| Permission | Value |
|---|---|
| Show Client List | 1 |
| Add New Client | 2 |
| Delete Client | 4 |
| Update Client | 8 |
| Find Client | 16 |
| Transactions | 32 |
| Manage Users | 64 |

For example, a user who can only show and find clients has the permission `1 + 16 = 17`.

Sample data files are included in the `Data` folder.

## Project structure

```
.
├── BankMangementSystem/          # Bank Management System (employee app)
│   ├── main.cpp                      # Entry point
│   ├── Menus.cpp / .h                # Main menu and task handling
│   ├── Clients.cpp / .h              # Client records, file reading and writing
│   ├── Transactions.cpp / .h         # Deposit, withdraw, total balances
│   ├── Users.cpp / .h                # Login, users and permissions
│   └── Common.cpp / .h               # Shared helpers and file names
├── ATMSystem/                    # ATM System (client app)
│   └── ATMSystem/
│       └── ATMSystem/
│           ├── main.cpp              # Entry point
│           ├── ATMSystem.cpp / .h    # Login screen and program flow
│           ├── ClientsATM.cpp / .h   # Client structure, file reading and writing
│           ├── TransactionsATM.cpp   # Deposit, withdraw, balance, menu
│           ├── TransactionATM.h
│           ├── CommonATM.cpp / .h    # Shared helpers and file names
│           └── ATMSystem.vcxproj
├── Data/                         # Sample data files
├── Project1Course7/              # Original Course 7 project
├── screenshots/                  # Images used in this README
├── .gitattributes
├── .gitignore
└── README.md
```

## Versions

| Version | Description |
|---|---|
| [v1.0](../../releases/tag/v1.0) | Client management: add, show, update, delete, find |
| [v2.0](../../releases/tag/v2.0) | Adds the Transactions menu: deposit, withdraw, total balances |
| [v3.0](../../releases/tag/v3.0) | Adds login, user management and permissions, and splits the code into separate modules |
| [v4.0](../../releases/tag/v4.0) | Adds the ATM System alongside the Bank Management System |

## What I learned

- Designing menu-driven programs with `enum` and `switch`
- Using `struct` and `vector` to model and process records
- Reading and writing files with `fstream` and parsing delimited records
- Formatting console tables with `<iomanip>` (`setw`, `left`)
- Passing data by reference and splitting logic into small functions
- Validating user input and handling not-found cases safely
- Storing permissions as bit flags and checking them with bitwise operators (`|`, `&`)
- Splitting a project into several `.cpp` and header files, and sharing global variables (`CurrentUser`, `CurrentClient`) between them with `extern`
- Git workflow: small commits, branches, pull requests, tags and GitHub releases

## Roadmap

- [x] User login with permissions (Bank Management System)
- [x] PIN verification before transactions (ATM System)
- [ ] Transaction history log
- [ ] Transfer between accounts
- [ ] Portable screen clearing instead of `system("cls")`

## Credits

Based on the C++ course by Dr. Mohammed Abu-Hadhoud (Programming Advices). The Bank Management System was built as the end-of-course project for Course 7 and 8.

## Author

**Hassan Hlala**
Information Engineering student at Tishreen University, Syria

GitHub: [@hasanhlala](https://github.com/hasanhlala)
