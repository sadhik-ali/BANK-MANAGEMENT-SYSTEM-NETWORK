// ============================================================================
//  Bank Management System (console-based, beginner friendly)
//  Repository : https://github.com/sadhik-ali/NEWTWORK-STTC
//  Author     : Sadhik Ali
//  License    : Creative Commons Attribution 4.0 International (CC BY 4.0)
//               https://creativecommons.org/licenses/by/4.0/
//
//  Accounts are stored in a simple text file: accounts.txt
//  Transaction history is stored in: transactions.txt
// ============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

const string ACCOUNTS_FILE = "accounts.txt";
const string TRANSACTIONS_FILE = "transactions.txt";

// Convert a time to a readable string like 2026-10-25 14:30:00
string getCurrentTime() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[32];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
    return string(buffer);
}

// Remove the trailing newline from a line
string trimNewline(string s) {
    while (!s.empty() && (s.back() == '\n' || s.back() == '\r'))
        s.pop_back();
    return s;
}

// Find a line in the file that starts with "acc|" and return its balance part.
// Returns true if the account was found.
bool findAccount(const string& acc, double& balance, string& name) {
    ifstream file(ACCOUNTS_FILE);
    string line;
    while (getline(file, line)) {
        line = trimNewline(line);
        // expected format: accNo|name|balance
        size_t first = line.find('|');
        if (first == string::npos) continue;
        size_t second = line.find('|', first + 1);
        if (second == string::npos) continue; // skip malformed lines
        if (line.substr(0, first) == acc) {
            name = line.substr(first + 1, second - first - 1);
            balance = stod(line.substr(second + 1));
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

// Rewrite the whole accounts file after updating one account's balance.
void updateBalance(const string& acc, double newBalance) {
    ifstream in(ACCOUNTS_FILE);
    string line;
    // First read all lines into memory
    string lines[1000];
    int count = 0;
    while (getline(in, line) && count < 1000) {
        line = trimNewline(line);
        size_t first = line.find('|');
        size_t second = line.find('|', first + 1);
        if (first != string::npos && second != string::npos &&
            line.substr(0, first) == acc) {
            ostringstream value;
            value << fixed << setprecision(2) << newBalance;
            line = line.substr(0, second + 1) + value.str();
        }
        lines[count++] = line;
    }
    in.close();

    ofstream out(ACCOUNTS_FILE);
    for (int i = 0; i < count; i++)
        out << lines[i] << "\n";
    out.close();
}

// Append one line to the transaction history file.
// Format: accNo|type|amount|time
void saveTransaction(const string& acc, const string& type, double amount) {
    ofstream out(TRANSACTIONS_FILE, ios::app);
    out << acc << "|" << type << "|" << fixed << setprecision(2)
        << amount << "|" << getCurrentTime() << "\n";
    out.close();
}

// 1. Create a new account
void createAccount() {
    string acc, name;
    double balance;

    cout << "\nEnter account number: ";
    cin >> acc;

    double dummy;
    string dummyName;
    if (findAccount(acc, dummy, dummyName)) {
        cout << "Account number already exists!\n";
        return;
    }

    cin.ignore(); // remove leftover newline
    cout << "Enter account holder name: ";
    getline(cin, name);

    cout << "Enter initial balance: ";
    cin >> balance;

    ofstream out(ACCOUNTS_FILE, ios::app);
    out << acc << "|" << name << "|" << fixed << setprecision(2) << balance << "\n";
    out.close();

    saveTransaction(acc, "OPEN", balance);
    cout << "Account created successfully!\n";
}

// 2. Show account details
void viewAccount() {
    string acc;
    cout << "\nEnter account number: ";
    cin >> acc;

    double balance;
    string name;
    if (!findAccount(acc, balance, name)) {
        cout << "Account not found!\n";
        return;
    }

    cout << "\nAccount Number : " << acc << "\n";
    cout << "Name           : " << name << "\n";
    cout << "Balance        : " << fixed << setprecision(2) << balance << "\n";
}

// 3. Deposit money
void deposit() {
    string acc;
    cout << "\nEnter account number: ";
    cin >> acc;

    double balance, amount;
    string name;
    if (!findAccount(acc, balance, name)) {
        cout << "Account not found!\n";
        return;
    }

    cout << "Enter deposit amount: ";
    cin >> amount;
    if (amount <= 0) {
        cout << "Amount must be positive!\n";
        return;
    }

    updateBalance(acc, balance + amount);
    saveTransaction(acc, "DEPOSIT", amount);
    cout << "Deposited successfully. New balance: "
         << fixed << setprecision(2) << balance + amount << "\n";
}

// 4. Withdraw money
void withdraw() {
    string acc;
    cout << "\nEnter account number: ";
    cin >> acc;

    double balance, amount;
    string name;
    if (!findAccount(acc, balance, name)) {
        cout << "Account not found!\n";
        return;
    }

    cout << "Enter withdrawal amount: ";
    cin >> amount;
    if (amount <= 0) {
        cout << "Amount must be positive!\n";
        return;
    }
    if (amount > balance) {
        cout << "Insufficient balance!\n";
        return;
    }

    updateBalance(acc, balance - amount);
    saveTransaction(acc, "WITHDRAW", amount);
    cout << "Withdrawn successfully. New balance: "
         << fixed << setprecision(2) << balance - amount << "\n";
}

// 5. Show transaction history for one account
void showHistory() {
    string acc;
    cout << "\nEnter account number: ";
    cin >> acc;

    ifstream file(TRANSACTIONS_FILE);
    string line;
    int found = 0;

    cout << "\n--- Transaction History ---\n";
    while (getline(file, line)) {
        line = trimNewline(line);
        size_t first = line.find('|');
        if (first == string::npos) continue;
        if (line.substr(0, first) != acc) continue;

        size_t second = line.find('|', first + 1);
        size_t third = line.find('|', second + 1);

        string type = line.substr(first + 1, second - first - 1);
        string amount = line.substr(second + 1, third - second - 1);
        string time = line.substr(third + 1);

        cout << left << setw(10) << type << "  "
             << setw(12) << amount << "  " << time << "\n";
        found++;
    }
    file.close();

    if (found == 0)
        cout << "No transactions found for this account.\n";
}

// Main menu loop
int main() {
    int choice;

    while (true) {
        cout << "\n===== BANK MANAGEMENT SYSTEM =====\n";
        cout << "1. Create Account\n";
        cout << "2. View Balance\n";
        cout << "3. Deposit\n";
        cout << "4. Withdraw\n";
        cout << "5. Transaction History\n";
        cout << "6. Exit\n";
        cout << "Choose an option: ";

        if (!(cin >> choice)) {
            cout << "Invalid input!\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (choice) {
            case 1: createAccount(); break;
            case 2: viewAccount(); break;
            case 3: deposit(); break;
            case 4: withdraw(); break;
            case 5: showHistory(); break;
            case 6: cout << "Goodbye!\n"; return 0;
            default: cout << "Please choose 1-6.\n";
        }
    }
}
