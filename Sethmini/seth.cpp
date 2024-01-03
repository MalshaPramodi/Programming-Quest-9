#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

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
SavingsAccount(string accNo,string custName,string phoneNo,double initBalance,double interestRate);
void depositMoney(double amount,string depositorName) override;
void withdrawMoney(double amount) override;
void viewTransactions() override;
void saveTransactionToFile(string transactionInfo) override;
void calculateInterest();
};

class CurrentAccount:public Account{
    double overdraftCharge;
    double overdraftLimit;

public:
CurrentAccount(string accNo,string custName,string phoneNo,double initBalance,double charge,double limit);
void depositMoney(double amount,string depositorName) override;
void withdrawMoney(double amount) override;
void viewTransactions() override;
void saveTransactionToFile(string transactionInfo) override;
void setOverdraftLimit(double limit);
void applyOverdraftCharge();

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
    void addEmployee(string userName,string password);
    void increaseDate();
    void setAnnualSavingInterest(double interestRate);
    void setOverdraftCharge(double charge);
    void viewTransactions() override;
};

class Employee : public User{
    public:
    Employee(string uname,string pword) : User(uname,pword){}
    void addCustomer(string userName,string password);
    void createAccount(Account* accountType, string customerName,string phoneNumber);
    void closeAccount(Account* account);
    void viewTransactions(Account* account);
    void deposit(Account* account,double amount,string depositorName);
    void withdraw(Account* account,double amount);
    void setOverdraftLimit(CurrentAccount* account,double limit);

};

class Customer : public User {
    public:
    Customer(string uname,string pword): User(uname,pword) {}
    void viewTransactions(Account* account);
    void deposit(Account* account,double amount);
    void withdraw(Account* account,double amount);
    void viewTransactions() override;
};

//seth