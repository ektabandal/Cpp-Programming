
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>
using namespace std;

class Account {
public:
    int accNo;
    string name;
    string type;
    double balance;

    void input() {
        cout << "Enter Account Number: ";
        cin >> accNo;
        cin.ignore();

        cout << "Enter Customer Name: ";
        getline(cin, name);

        cout << "Enter Account Type (Savings/Current): ";
        getline(cin, type);

        cout << "Enter Initial Balance: ";
        cin >> balance;
    }

    void display() const {
        cout << left << setw(10) << accNo
             << setw(25) << name
             << setw(15) << type
             << setw(15) << balance << endl;
    }
};

vector<Account> accounts;

void saveToFile() {
    ofstream file("accounts.txt");
    for (auto &a : accounts) {
        file << a.accNo << "|"
             << a.name << "|"
             << a.type << "|"
             << a.balance << "\n";
    }
}

void loadFromFile() {
    accounts.clear();
    ifstream file("accounts.txt");
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string temp;
        Account a;

        getline(ss, temp, '|');
        a.accNo = stoi(temp);

        getline(ss, a.name, '|');
        getline(ss, a.type, '|');

        getline(ss, temp);
        a.balance = stod(temp);

        accounts.push_back(a);
    }
}

void createAccount() {
    Account a;
    a.input();

    for (auto &x : accounts) {
        if (x.accNo == a.accNo) {
            cout << "Account already exists!\n";
            return;
        }
    }

    accounts.push_back(a);
    saveToFile();
    cout << "Account Created Successfully!\n";
}

Account* findAccount(int accNo) {
    for (auto &a : accounts)
        if (a.accNo == accNo)
            return &a;
    return nullptr;
}

void deposit() {
    int accNo;
    double amount;

    cout << "Enter Account Number: ";
    cin >> accNo;

    Account* a = findAccount(accNo);

    if (!a) {
        cout << "Account Not Found!\n";
        return;
    }

    cout << "Enter Amount: ";
    cin >> amount;

    a->balance += amount;
    saveToFile();

    cout << "Deposit Successful!\n";
}

void withdraw() {
    int accNo;
    double amount;

    cout << "Enter Account Number: ";
    cin >> accNo;

    Account* a = findAccount(accNo);

    if (!a) {
        cout << "Account Not Found!\n";
        return;
    }

    cout << "Enter Amount: ";
    cin >> amount;

    if (amount > a->balance) {
        cout << "Insufficient Balance!\n";
        return;
    }

    a->balance -= amount;
    saveToFile();

    cout << "Withdrawal Successful!\n";
}

void balanceInquiry() {
    int accNo;
    cout << "Enter Account Number: ";
    cin >> accNo;

    Account* a = findAccount(accNo);

    if (!a) {
        cout << "Account Not Found!\n";
        return;
    }

    cout << "Current Balance: " << a->balance << endl;
}

void searchAccount() {
    int accNo;
    cout << "Enter Account Number: ";
    cin >> accNo;

    Account* a = findAccount(accNo);

    if (!a) {
        cout << "Account Not Found!\n";
        return;
    }

    cout << "\nAccount Details\n";
    cout << left << setw(10) << "Acc No"
         << setw(25) << "Name"
         << setw(15) << "Type"
         << setw(15) << "Balance" << endl;

    a->display();
}

void displayAllAccounts() {
    if (accounts.empty()) {
        cout << "No Accounts Found!\n";
        return;
    }

    cout << left << setw(10) << "Acc No"
         << setw(25) << "Name"
         << setw(15) << "Type"
         << setw(15) << "Balance" << endl;

    for (auto &a : accounts)
        a.display();
}

void updateAccount() {
    int accNo;
    cout << "Enter Account Number: ";
    cin >> accNo;
    cin.ignore();

    Account* a = findAccount(accNo);

    if (!a) {
        cout << "Account Not Found!\n";
        return;
    }

    cout << "Enter New Name: ";
    getline(cin, a->name);

    cout << "Enter New Account Type: ";
    getline(cin, a->type);

    saveToFile();
    cout << "Account Updated Successfully!\n";
}

void deleteAccount() {
    int accNo;
    cout << "Enter Account Number: ";
    cin >> accNo;

    for (auto it = accounts.begin(); it != accounts.end(); ++it) {
        if (it->accNo == accNo) {
            accounts.erase(it);
            saveToFile();
            cout << "Account Deleted Successfully!\n";
            return;
        }
    }

    cout << "Account Not Found!\n";
}

bool login() {
    string user, pass;

    cout << "\n===== ADMIN LOGIN =====\n";
    cout << "Username: ";
    cin >> user;
    cout << "Password: ";
    cin >> pass;

    return (user == "ektabandal" && pass == "2366");
}

int main() {
    loadFromFile();

    if (!login()) {
        cout << "Invalid Login!\n";
        return 0;
    }

    int choice;

    do {
        cout << "\n\n===== BANK MANAGEMENT SYSTEM =====\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Balance Inquiry\n";
        cout << "5. Search Account\n";
        cout << "6. Display All Accounts\n";
        cout << "7. Update Account\n";
        cout << "8. Delete Account\n";
        cout << "9. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: balanceInquiry(); break;
            case 5: searchAccount(); break;
            case 6: displayAllAccounts(); break;
            case 7: updateAccount(); break;
            case 8: deleteAccount(); break;
            case 9: cout << "Thank You!\n"; break;
            default: cout << "Invalid Choice!\n";
        }

    } while (choice != 9);

    return 0;
}
