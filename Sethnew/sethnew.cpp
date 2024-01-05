#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime> // For date manipulation (example)

using namespace std;

class Transaction {
public:
    string transactionInfo;
    // Include other transaction details as needed (e.g., date, time, amount)
    Transaction(string info) : transactionInfo(info) {}
};

class Account{

    protected:
    string accountNumber;
    string customerName;
    string phoneNumber;
    double balance;

    public:
    virtual void depositMoney(double amount, string depositorName)=0;
    virtual void withdrawMoney(double amount)= 0;
    virtual void viewTransactions()=0;
    virtual void saveTransactionToFile(string transactionInfo)=0;
};

class SavingsAccount : public Account{
    double annualInterestrate;

public:
//SavingsAccount(string accNo,string custName,string phoneNo,double initBalance,double interestRate);
void depositMoney(double amount,string depositorName) override{
    cout<<"Depositing "<<amount<<" for "<< depositorName <<endl;
    balance +=amount;
    saveTransactionToFile("Deposit: " + to_string(amount) + " by " + depositorName);
}

void withdrawMoney(double amount) override{
    if(balance>=amount){
        cout<<"Withdrawing "<<amount<<endl;
        balance -=amount;
        saveTransactionToFile("Withdrawal: " + to_string(amount));
    }
    else{
        cout<<"Insufficient balance in the account!"<<endl;
    }
}

void viewTransactions() override{
    ifstream transactionFile("transactions.txt");
    if(transactionFile.is_open()){
        string line;
        cout<<"Transaction History:"<<endl;
        while(getline(transactionFile,line)){
            cout<< line <<endl;
        }
        transactionFile.close();
    }
    else{
        cout<<"No transaction history found!"<<endl;
    }

}
void saveTransactionToFile(string transactionInfo) override{
    ofstream transactionFile("transactions.txt", ios::app);
        if (transactionFile.is_open()) {
            transactionFile << transactionInfo << endl;
            transactionFile.close();
        } else {
            cout << "Unable to save transaction." << endl;
        }
}

void calculateInterest(){
    // Assuming the interest is calculated annually and added to the balance
    double interestAmount = balance * (annualInterestrate / 100);
    balance += interestAmount;
    saveTransactionToFile("Interest added: " + to_string(interestAmount));
    cout << "Interest calculated and added to the account." << endl;
}

};

class CurrentAccount:public Account{
    double overdraftCharge;
    double overdraftLimit;

public:
CurrentAccount(string accNo,string custName,string phoneNo,double initBalance,double charge,double limit) : accountNumber(accNo), customerName(custName), phoneNumber(phoneNo), balance(initBalance),
          overdraftCharge(charge), overdraftLimit(limit) {}

void depositMoney(double amount,string depositorName) override{
    cout << "Depositing " << amount << " for " << depositorName << endl;
        balance += amount;
        saveTransactionToFile("Deposit: " + to_string(amount) + " by " + depositorName);
}
void withdrawMoney(double amount) override{
    if (balance + overdraftLimit >= amount) {
            cout << "Withdrawing " << amount << endl;
            balance -= amount;
            saveTransactionToFile("Withdrawal: " + to_string(amount));
            if (balance < 0) {
                applyOverdraftCharge();
            }
        } else {
            cout << "Insufficient balance!" << endl;
        }
}
void viewTransactions() override{
     ifstream transactionFile("transactions.txt");
        if (transactionFile.is_open()) {
            string line;
            cout << "Transaction History:" << endl;
            while (getline(transactionFile, line)) {
                cout << line << endl;
            }
            transactionFile.close();
        } else {
            cout << "No transaction history found." << endl;
        }
}
void saveTransactionToFile(string transactionInfo) override{
    ofstream transactionFile("transactions.txt", ios::app);
        if (transactionFile.is_open()) {
            transactionFile << transactionInfo << endl;
            transactionFile.close();
        } else {
            cout << "Unable to save transaction." << endl;
        }
}
void setOverdraftLimit(double limit){
    overdraftLimit = limit;

}
void applyOverdraftCharge(){
     cout << "Applying overdraft charge." << endl;
        balance -= overdraftCharge;
        saveTransactionToFile("Overdraft Charge Applied: " + to_string(overdraftCharge));
}

};

class User{
    protected:
    string username;
    string password;

    public:
    User(const string uname,string pword) : username(uname),password(pword) {}
    virtual ~User(){}
    virtual void viewTransactions()=0;

};


class Admin : public User{
    public:
    Admin(string uname,string pword) : User(uname,pword) {}
    Employee employees[100]; // Assuming a maximum of 100 employees

    int employeeCount = 0; // Counter to track the number of employees added

    void addEmployee(string userName,string password){
        // Logic to create and add an employee to the system
        if (employeeCount < 100) {
            employees[employeeCount++] = Employee(userName, password);
            cout << "Employee added successfully." << endl;
        } else {
            cout << "Employee limit reached. Cannot add more employees." << endl;
        }
     
    }
    void increaseDate(){
         // Logic to increase the date by 1 day (Example: Modify the system date)
        time_t now = time(0); // Get current system time
        tm* currentDate = localtime(&now); // Convert to local time
        currentDate->tm_mday += 1; // Increase day by 1
        mktime(currentDate); // Convert back to time_t format
        cout << "Date increased by 1 day." << endl;
    }
    void setAnnualSavingInterest(double interestRate){
         // Logic to set annual saving interest rate
        // Example: Assuming a SavingsAccount class exists with a method to set interest rate
        SavingsAccount::setAnnualInterestRate(interestRate);
        cout << "Annual saving interest rate set to: " << interestRate << "%" << endl;
    }
    void setOverdraftCharge(double charge){
         // Logic to set overdraft charge
        // Example: Assuming CurrentAccount class exists with a method to set overdraft charge
        CurrentAccount::setOverdraftCharge(charge);
        cout << "Overdraft charge set to: " << charge << endl;
    }
    void viewTransactions() override{
         // Logic to view transactions for admin
        // Example: Display transaction logs or history
        ifstream transactionFile("transactions.txt");
        if (transactionFile.is_open()) {
            string line;
            cout << "Transaction History:" << endl;
            while (getline(transactionFile, line)) {
                cout << line << endl;
            }
            transactionFile.close();
        } else {
            cout << "No transaction history found." << endl;
        }
    }
};

class Employee : public User{
    public:
    Employee(string uname,string pword) : User(uname,pword){}
    Customer customers[100]; // Assuming a maximum of 100 customers
    
    int customerCount = 0; // Counter to track the number of customers added
    SavingsAccount accounts[100]; // Array to store accounts
    int accountCount = 0;

    Account* accounts[100]; // Array to store accounts
    int accountCount = 0;


    void addCustomer(string userName,string password){
        // Logic to create and add a customer to the system
        if (customerCount < 100) {
            customers[customerCount++] = Customer(userName, password);
            cout << "Customer " << userName << " added successfully." << endl;
        } else {
            cout << "Customer limit reached. Cannot add more customers." << endl;
        }
    }
    void createAccount(Account* accountType, string customerName,string phoneNumber){
         // Logic to create an account for a customer
        if (accountCount < 100) {
            accounts[accountCount++] = SavingsAccount(accNo, custName, phoneNo, initBalance, interestRate);
            cout << "Savings Account created for " << custName << " with account number: " << accNo << endl;
        } else {
            cout << "Account limit reached. Cannot create more accounts." << endl;
        }
    }
    void closeAccount(Account* account){
        // Logic to close an account
        for (int i = 0; i < accountCount; ++i) {
            if (accounts[i].accountNumber == accNo) {
                // Shift elements to remove the closed account
                for (int j = i; j < accountCount - 1; ++j) {
                    accounts[j] = accounts[j + 1];
                }
                accountCount--;
                cout << "Account " << accNo << " closed successfully." << endl;
                return;
            }
        }
        cout << "Account " << accNo << " not found." << endl;
    }
    void viewTransactions(Account* account){
        // Logic to view transactions for an account
        ifstream transactionFile("transactions.txt");
        if (transactionFile.is_open()) {
            string line;
            cout << "Transaction History for Account " << account->accountNumber << ":" << endl;
            while (getline(transactionFile, line)) {
                cout << line << endl;
            }
            transactionFile.close();
        } else {
            cout << "No transaction history found." << endl;
        }
    }
    void deposit(Account* account,double amount,string depositorName){
        double balance;
        // Logic to deposit money into an account
        account->balance += amount;
        cout << "Depositing " << amount << " for " << depositorName << " into Account " << account->accountNumber << endl;
    }
    void withdraw(Account* account,double amount){
         // Logic to withdraw money from an account
        if (account->balance >= amount) {
            account->balance -= amount;
            cout << "Withdrawing " << amount << " from Account " << account->accountNumber << endl;
        } else {
            cout << "Insufficient balance in Account " << account->accountNumber << endl;
        }
    }
    void setOverdraftLimit(CurrentAccount* account,double limit){
        // Logic to set overdraft limit for a current account
        account->overdraftLimit = limit;
        cout << "Overdraft limit set for Account " << account->accountNumber << ": " << limit << endl;
    }

};

class Customer : public User 
{
    public:
    Customer(string uname,string pword): User(uname,pword) {}
    
    void viewTransactions(Account* account){
        // Logic to view transactions for an account
        ifstream transactionFile("transactions.txt");
        if (transactionFile.is_open()) {
            string line;
            cout << "Transaction History for Account " << account->accountNumber << ":" << endl;
            while (getline(transactionFile, line)) {
                cout << line << endl;
            }
            transactionFile.close();
        } else {
            cout << "No transaction history found." << endl;
        }
    }
    void deposit(Account* account,double amount){
         // Logic to deposit money into an account
        account->balance += amount;
        cout << "Depositing " << amount << " into Account " << account->accountNumber << endl;
    }
    }
    
    void withdraw(Account* account,double amount){
        // Logic to withdraw money from an account
        if (account->balance >= amount) {
            account->balance -= amount;
            cout << "Withdrawing " << amount << " from Account " << account->accountNumber << endl;
        } else {
            cout << "Insufficient balance in Account " << account->accountNumber << endl;
        }
    }

    void viewTransactions() override {
        // Logic to view transactions for the customer (all accounts)
        cout << "Viewing all transactions for customer " << username << ":" << endl;
        for (int i = 0; i < accountCount; ++i) {
            viewTransactions(accounts[i]);
        }
    }
};
