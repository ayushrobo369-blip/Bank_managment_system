
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <cstdio>

using namespace std;

class temp {

    string Name, Full_nam, Acc_num, Dof, user;

    fstream file;

private:

    int password, Adher_number;

public:

    void Fill_form();
    void Deposit_money();
    void withdraw_money();
    void Update_account();

};

int main() {

    temp obj;
    char choise;

    do {

        cout << "\n-------------------------------" << endl;
        cout << "----- Welcome To Banking ------" << endl;
        cout << "-------------------------------" << endl;

        cout << "1. New Bank Account Registration" << endl;
        cout << "2. Deposit Money" << endl;
        cout << "3. Withdraw Money" << endl;
        cout << "4. Updating Account" << endl;
        cout << "5. Exit" << endl;

        cout << "\nPlease Select Option: ";
        cin >> choise;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choise) {

            case '1':
                obj.Fill_form();
                break;

            case '2':
                obj.Deposit_money();
                break;

            case '3':
                obj.withdraw_money();
                break;

            case '4':
                obj.Update_account();
                break;

            case '5':
                cout << "Thank you for using our banking system!" << endl;
                break;

            default:
                cout << "Invalid option..." << endl;
                break;
        }

    } while (choise != '5');

    return 0;
}


// --------------------------------
// ACCOUNT REGISTRATION
// --------------------------------

void temp::Fill_form() {

    cout << "\n--- Enter Account Details ---" << endl;

    cout << "Enter Name: ";
    getline(cin, Name);

    cout << "Enter Full Name: ";
    getline(cin, Full_nam);

    cout << "Enter Account Number: ";
    getline(cin, Acc_num);

    cout << "Enter Date of Birth: ";
    getline(cin, Dof);

    cout << "Enter Aadhaar Number: ";
    cin >> Adher_number;

    cout << "Enter Password: ";
    cin >> password;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nAre you sure about the details? (Yes/No): ";
    cin >> user;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (user == "Yes" || user == "yes") {

        file.open("BankData.txt", ios::out | ios::app);

        if (!file) {
            cout << "File Error!" << endl;
            return;
        }

        file << Name << "*"
             << Full_nam << "*"
             << Dof << "*"
             << Acc_num << "*"
             << Adher_number << "*"
             << password << "*"
             << 0 << endl;

        file.close();

        cout << "\nAccount Created Successfully!" << endl;

    }
    else {

        cout << "Registration Cancelled!" << endl;

    }

}


// --------------------------------
// DEPOSIT MONEY
// --------------------------------

void temp::Deposit_money() {

    string fileName, fileFull, fileDof;
    string fileAcc, fileAdher, filePassword, fileBalance;

    double balance, amount;
    bool found = false;

    cout << "\n--- Deposit Money ---" << endl;

    cout << "Enter Name: ";
    getline(cin, Name);

    cout << "Date of Birth: ";
    getline(cin, Dof);

    cout << "Account Number: ";
    getline(cin, Acc_num);

    cout << "Password: ";
    cin >> password;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    file.open("BankData.txt", ios::in);

    if (!file) {
        cout << "File Error!" << endl;
        return;
    }

    ofstream tempFile("TempBankData.txt");

    if (!tempFile) {
        cout << "Unable to create temporary file!" << endl;
        file.close();
        return;
    }

    while (
        getline(file, fileName, '*') &&
        getline(file, fileFull, '*') &&
        getline(file, fileDof, '*') &&
        getline(file, fileAcc, '*') &&
        getline(file, fileAdher, '*') &&
        getline(file, filePassword, '*') &&
        getline(file, fileBalance)
    ) {

        balance = stod(fileBalance);

        if (fileName == Name &&
            fileDof == Dof &&
            fileAcc == Acc_num &&
            filePassword == to_string(password)) {

            found = true;

            cout << "\nCredentials Verified!" << endl;
            cout << "Current Balance: " << balance << endl;

            cout << "Enter Deposit Amount: ";
            cin >> amount;

            if (amount > 0) {

                balance += amount;

                cout << "\nDeposit Successful!" << endl;
                cout << "Updated Balance: " << balance << endl;

            }
            else {

                cout << "Invalid Deposit Amount!" << endl;

            }

        }

        tempFile << fileName << "*"
                 << fileFull << "*"
                 << fileDof << "*"
                 << fileAcc << "*"
                 << fileAdher << "*"
                 << filePassword << "*"
                 << balance << endl;

    }

    file.close();
    tempFile.close();

    if (found) {

        remove("BankData.txt");
        rename("TempBankData.txt", "BankData.txt");

    }
    else {

        remove("TempBankData.txt");
        cout << "Invalid Credentials!" << endl;

    }

}


// --------------------------------
// WITHDRAW MONEY
// --------------------------------

void temp::withdraw_money() {

    string fileName, fileFull, fileDof;
    string fileAcc, fileAdher, filePassword, fileBalance;

    double balance, amount;
    bool found = false;

    cout << "\n--- Withdraw Money ---" << endl;

    cout << "Enter Name: ";
    getline(cin, Name);

    cout << "Date of Birth: ";
    getline(cin, Dof);

    cout << "Account Number: ";
    getline(cin, Acc_num);

    cout << "Password: ";
    cin >> password;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    file.open("BankData.txt", ios::in);

    if (!file) {
        cout << "File Error!" << endl;
        return;
    }

    ofstream tempFile("TempBankData.txt");

    if (!tempFile) {
        cout << "Unable to create temporary file!" << endl;
        file.close();
        return;
    }

    while (
        getline(file, fileName, '*') &&
        getline(file, fileFull, '*') &&
        getline(file, fileDof, '*') &&
        getline(file, fileAcc, '*') &&
        getline(file, fileAdher, '*') &&
        getline(file, filePassword, '*') &&
        getline(file, fileBalance)
    ) {

        balance = stod(fileBalance);

        if (fileName == Name &&
            fileDof == Dof &&
            fileAcc == Acc_num &&
            filePassword == to_string(password)) {

            found = true;

            cout << "\nCredentials Verified!" << endl;
            cout << "Current Balance: " << balance << endl;

            cout << "Enter Withdrawal Amount: ";
            cin >> amount;

            if (amount > 0 && amount <= balance) {

                balance -= amount;

                cout << "\nWithdrawal Successful!" << endl;
                cout << "Remaining Balance: " << balance << endl;

            }
            else {

                cout << "Invalid Amount or Insufficient Balance!" << endl;

            }

        }

        tempFile << fileName << "*"
                 << fileFull << "*"
                 << fileDof << "*"
                 << fileAcc << "*"
                 << fileAdher << "*"
                 << filePassword << "*"
                 << balance << endl;

    }

    file.close();
    tempFile.close();

    if (found) {

        remove("BankData.txt");
        rename("TempBankData.txt", "BankData.txt");

    }
    else {

        remove("TempBankData.txt");
        cout << "Invalid Credentials!" << endl;

    }

}


// --------------------------------
// UPDATE ACCOUNT
// --------------------------------

void temp::Update_account() {

    string fileName, fileFull, fileDof;
    string fileAcc, fileAdher, filePassword, fileBalance;

    bool found = false;

    cout << "\n--- Update Account Details ---" << endl;

    cout << "Enter Account Number: ";
    getline(cin, Acc_num);

    cout << "Enter Password: ";
    cin >> password;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    file.open("BankData.txt", ios::in);

    if (!file) {
        cout << "File Error!" << endl;
        return;
    }

    ofstream tempFile("TempBankData.txt");

    if (!tempFile) {
        cout << "Unable to create temporary file!" << endl;
        file.close();
        return;
    }

    while (
        getline(file, fileName, '*') &&
        getline(file, fileFull, '*') &&
        getline(file, fileDof, '*') &&
        getline(file, fileAcc, '*') &&
        getline(file, fileAdher, '*') &&
        getline(file, filePassword, '*') &&
        getline(file, fileBalance)
    ) {

        if (fileAcc == Acc_num &&
            filePassword == to_string(password)) {

            found = true;

            cout << "\nAccount Verified!" << endl;

            cout << "Enter New Name: ";
            getline(cin, fileName);

            cout << "Enter New Full Name: ";
            getline(cin, fileFull);

            cout << "Enter New Date of Birth: ";
            getline(cin, fileDof);

        }

        tempFile << fileName << "*"
                 << fileFull << "*"
                 << fileDof << "*"
                 << fileAcc << "*"
                 << fileAdher << "*"
                 << filePassword << "*"
                 << fileBalance << endl;

    }

    file.close();
    tempFile.close();

    if (found) {

        remove("BankData.txt");
        rename("TempBankData.txt", "BankData.txt");

        cout << "\nAccount Updated Successfully!" << endl;

    }
    else {

        remove("TempBankData.txt");
        cout << "Invalid Account Credentials!" << endl;

    }

}
