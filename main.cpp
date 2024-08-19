#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
#include <string>
#include <cstring> // For strcpy
#include <limits>  // For numeric_limits

using namespace std;

const int maxName = 50;
const int maxMoney = 7;
const int maxNumber = 12;
const int typeSize = 4;
const string sep = " |";
const int totalLen = maxName + maxNumber + typeSize + maxMoney + sep.size() * 4;
const string sepLine = sep + string(totalLen - 1, '=') + '|';

class Bank {
private:
    unsigned long long account_number;
    char holder_name[51];
    int deposit;
    char type;
public:
    void clearScreen();
    void Get_Data();
    void Write_Data();
    void deposit_withdraw(int n, int option);
    void Display_Invidual_Records(unsigned long long n);
    void report() const;
    void Show_account() const;
    void dep(int);
    void draw(int x);
    unsigned long long retacno() const;
    int retdeposit() const;
    char rettype() const;
    void Modification_data();

    // Public setters
    void setAccountNumber(unsigned long long accNum) { account_number = accNum; }
    void setHolderName(const char* name) { strcpy(holder_name, name); }
    void setDeposit(int dep) { deposit = dep; }
    void setType(char accType) { type = accType; }
};

void Bank::Get_Data() {
    cout << "\n\n===========CREATE BANK ACCOUNT===========\n\n";
    cout << "\nEnter the Account Number:";
    cin >> account_number;
    while ((int)to_string(account_number).size() != 12) {
        cout << "The account number has to be of 12 digits. Please try again.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> account_number;
    }
    cout << "\n\nEnter Account Holder Name: ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.getline(holder_name, 51);
    cout << "\nWhich type of Account \n[S for Saving Account] (or)[C for Current Account]: ";
    cin.clear();
    cin >> type;
    type = toupper(type);
    while (type != 'S' && type != 'C') {
        cout << "Please enter either S or C to avoid data corruption: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> type;
        type = toupper(type);
    }
    if (type == 'S') {
        cout << "\nEnter the Initial Amount for Saving Account [Minimum 500/-]: ";
        cin >> deposit;
        while (deposit >= 1000000) {
            cout << "Maximum money is 1000000/-\nPlease try again: ";
            cin >> deposit;
        }
        cout << "\n\nAccount has been Created Successfully.";
    } else if (type == 'C') {
        cout << "\nEnter the Initial Amount for Current Account [Minimum 1000/-]: ";
        cin >> deposit;
        while (deposit >= 1000000) {
            cout << "Maximum money is 1000000/-\nPlease try again: ";
            cin >> deposit;
        }
        cout << "\n\nAccount has been Created Successfully.";
    }
}

void Bank::Write_Data() {
    ofstream outFile;
    outFile.open("account.dat", ios::binary | ios::app);
    Get_Data();
    outFile.write(reinterpret_cast<char*>(this), sizeof(*this));
    outFile.close();
}

void Bank::Modification_data() {
    cout << "\nAccount No: " << account_number;
    cout << "\nModify Account Holder Name: ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.getline(holder_name, 51);
    cout << "\nModify Type of Account : ";
    cin.clear();
    cin >> type;
    type = toupper(type);
    cout << "\nModify Total Balance Amount : ";
    cin >> deposit;
    while (deposit >= 1000000) {
        cout << "Maximum money is 1000000/-\nPlease try again: ";
        cin >> deposit;
    }
}

void Bank::Display_Invidual_Records(unsigned long long n) {
    bool flag = false;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile) {
        cout << "\n\nAn Error Occurred. Please try again.";
        return;
    }
    cout << "\nBALANCE DETAILS\n";

    while (inFile.read(reinterpret_cast<char*>(this), sizeof(*this))) {
        if (retacno() == n) {
            Show_account();
            flag = true;
        }
    }
    inFile.close();
    if (!flag)
        cout << "\n\nAccount Details not Found.";
}

void Bank::report() const {
    cout << sep <<
        setw(maxNumber) << account_number << sep <<
        setw(maxName) << holder_name << sep <<
        setw(typeSize) << type << sep <<
        setw(maxMoney) << deposit << sep << endl << sepLine << endl;
}

void Bank::dep(int x) {
    deposit += x;
}

void Bank::draw(int x) {
    deposit -= x;
}

void Bank::Show_account() const {
    cout << "\nAccount No: " << account_number;
    cout << "\nAccount Holder Name: ";
    cout << holder_name;
    if (type == 'S') {
        cout << "\nType of Account: Saving ";
    } else {
        cout << "\nType of Account: Current ";
    }
    cout << "\nTotal Balance: " << deposit;
}

unsigned long long Bank::retacno() const {
    return account_number;
}

int Bank::retdeposit() const {
    return deposit;
}

char Bank::rettype() const {
    return type;
}

void Bank::clearScreen() {
    // Cross-platform way to clear the console screen
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Delete_Account(unsigned long long);
void Get_All_Data();
void Deposit_Withdraw(unsigned long long, int);
void Credit();
void Account_Modification(unsigned long long);

void Add_Sample_Accounts() {
    Bank sampleAccount;
    ofstream outFile;
    outFile.open("account.dat", ios::binary | ios::app);
    if (!outFile) {
        cout << "Error opening file!";
        return;
    }

    // Sample account 1
    sampleAccount.setAccountNumber(123456789012);
    sampleAccount.setHolderName("John Doe");
    sampleAccount.setDeposit(5000);
    sampleAccount.setType('S'); // Saving Account
    outFile.write(reinterpret_cast<char*>(&sampleAccount), sizeof(sampleAccount));

    // Sample account 2
    sampleAccount.setAccountNumber(987654321098);
    sampleAccount.setHolderName("Jane Smith");
    sampleAccount.setDeposit(1500);
    sampleAccount.setType('C'); // Current Account
    outFile.write(reinterpret_cast<char*>(&sampleAccount), sizeof(sampleAccount));

    // Sample account 3
    sampleAccount.setAccountNumber(111111111111);
    sampleAccount.setHolderName("Alice Johnson");
    sampleAccount.setDeposit(750);
    sampleAccount.setType('S'); // Saving Account
    outFile.write(reinterpret_cast<char*>(&sampleAccount), sizeof(sampleAccount));

    // Sample account 4
    sampleAccount.setAccountNumber(222222222222);
    sampleAccount.setHolderName("Bob Brown");
    sampleAccount.setDeposit(2000);
    sampleAccount.setType('C'); // Current Account
    outFile.write(reinterpret_cast<char*>(&sampleAccount), sizeof(sampleAccount));

    outFile.close();
}

int main() {
    char my_url;
    char choice;
    unsigned long long account_number;
    Bank call;
    Add_Sample_Accounts(); // Add sample accounts when the program starts
    Credit();
    do {
        call.clearScreen();
        cout << "\n===========================";
        cout << "\n BANKING RECORD SYSTEM";
        cout << "\n===========================\n\n";
        cout << "\n\n01. CREATE NEW ACCOUNT";
        cout << "\n\n02. MODIFY AN ACCOUNT";
        cout << "\n\n03. BALANCE ENQUIRY OF ACCOUNT";
        cout << "\n\n04. DEPOSIT IN ACCOUNT";
        cout << "\n\n05. WITHDRAW FROM ACCOUNT";
        cout << "\n\n06. ALL ACCOUNT HOLDER LIST";
        cout << "\n\n07. CLOSE AN ACCOUNT";
        cout << "\n\n08. EXIT FROM PROGRAM";
        cout << "\n\nSELECT THE OPTION: ";
        cin >> choice;
        call.clearScreen();
        switch (choice) {
            case '1':
                call.Write_Data();
                break;
            case '2':
                cout << "\n\n\tAccount No: ";
                cin >> account_number;
                Account_Modification(account_number);
                break;
            case '3':
                cout << "\n\nAccount No: ";
                cin >> account_number;
                call.Display_Invidual_Records(account_number);
                break;
            case '4':
                cout << "\n\n\tAccount No: ";
                cin >> account_number;
                Deposit_Withdraw(account_number, 1);
                break;
            case '5':
                cout << "\n\n\tAccount No: ";
                cin >> account_number;
                Deposit_Withdraw(account_number, 2);
                break;
            case '6':
                Get_All_Data();
                break;
            case '7':
                cout << "\n\n\tAccount No: ";
                cin >> account_number;
                Delete_Account(account_number);
                break;
            case '8':
                cout << "\n\nThank you for using the Banking Record System!";
                break;
            default:
                cout << "\a";
        }
        cin.ignore();
        cin.get();
    } while (choice != '8');
    return 0;
}

void Delete_Account(unsigned long long n) {
    Bank acc;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile) {
        cout << "An error occurred. Please try again.";
        return;
    }
    outFile.open("Temp.dat", ios::binary);
    inFile.seekg(0, ios::beg);
    while (inFile.read(reinterpret_cast<char*>(&acc), sizeof(acc))) {
        if (acc.retacno() != n) {
            outFile.write(reinterpret_cast<char*>(&acc), sizeof(acc));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    rename("Temp.dat", "account.dat");
    cout << "\n\nAccount Deleted Successfully.";
}

void Get_All_Data() {
    Bank ac;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile) {
        cout << "An error occurred. Please try again.";
        return;
    }
    cout << sepLine << endl << sep <<
        setw(maxNumber) << "Account No" << sep <<
        setw(maxName) << "Account Holder Name" << sep <<
        setw(typeSize) << "Type" << sep <<
        setw(maxMoney) << "Balance" << sep << endl << sepLine << endl;

    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(ac))) {
        ac.report();
    }
    inFile.close();
}

void Deposit_Withdraw(unsigned long long n, int option) {
    int amount;
    bool found = false;
    Bank acc;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if (!File) {
        cout << "An error occurred. Please try again.";
        return;
    }
    while (!File.eof() && found == false) {
        File.read(reinterpret_cast<char*>(&acc), sizeof(acc));
        if (acc.retacno() == n) {
            acc.Show_account();
            if (option == 1) {
                cout << "\n\n\tTO DEPOSIT AMOUNT";
                cout << "\n\nEnter The amount to be deposited: ";
                cin >> amount;
                acc.dep(amount);
            }
            if (option == 2) {
                cout << "\n\n\tTO WITHDRAW AMOUNT";
                cout << "\n\nEnter The amount to be withdraw: ";
                cin >> amount;
                int bal = acc.retdeposit() - amount;
                if ((bal < 500 && acc.rettype() == 'S') || (bal < 1000 && acc.rettype() == 'C'))
                    cout << "Insufficient balance";
                else
                    acc.draw(amount);
            }
            int pos = (-1) * static_cast<int>(sizeof(acc));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char*>(&acc), sizeof(acc));
            cout << "\n\n\t Account updated";
            found = true;
        }
    }
    File.close();
    if (!found)
        cout << "\n\n Account not found ";
}

void Credit() {
    cout << "\n\n\n\n";
    cout << "\t\t\t\t\t--------------------------------------------\n";
    cout << "\t\t\t\t\t\tWELCOME TO OUR BANK SYSTEM PROJECT\n";
    cout << "\t\t\t\t\t\t============================================\n";
    cout << "\t\t\t\t\t\t  MADE BY : YOUR NAME\n";
    cout << "\t\t\t\t\t\t  COURSE : YOUR COURSE\n";
    cout << "\t\t\t\t\t\t  COLLEGE : YOUR COLLEGE\n";
    cout << "\t\t\t\t\t--------------------------------------------\n";
    cout << "\n\n\n\t\t\t\t\tPress any key to continue: ";
    cin.get();
}

void Account_Modification(unsigned long long n) {
    bool found = false;
    Bank acc;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if (!File) {
        cout << "An error occurred. Please try again.";
        return;
    }
    while (!File.eof() && found == false) {
        File.read(reinterpret_cast<char*>(&acc), sizeof(acc));
        if (acc.retacno() == n) {
            acc.Show_account();
            cout << "\n\nEnter The New Details of account" << endl;
            acc.Modification_data();
            int pos = (-1) * static_cast<int>(sizeof(acc));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char*>(&acc), sizeof(acc));
            cout << "\n\n\t Account Updated";
            found = true;
        }
    }
    File.close();
    if (!found)
        cout << "\n\n Account Not Found ";
}
