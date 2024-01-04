#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <string>

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
    User(const string uname) : username(uname),password("Password@1234") {}
    virtual ~User(){}
    virtual void viewTransactions()=0;

};

class Employee : public User{
    private:
    static int employeeCounter;

    public:
    Employee() : User("employee" + to_string(++employeeCounter)) {}
    Employee(string uname) : User(uname){}
    void addCustomer(string userName,string password);
    void createAccount(Account* accountType, string customerName,string phoneNumber);
    void closeAccount(Account* account);
    void viewTransactions(Account* account) override;
    void deposit(Account* account,double amount,string depositorName);
    void withdraw(Account* account,double amount);
    void setOverdraftLimit(CurrentAccount* account,double limit);

};

// Implementation of viewTransactions() in Employee class
void Employee::viewTransactions(Account* account) {
    // Implement logic to view transactions for the specified account
    cout << "Viewing transactions for account " << account->getAccountNumber() << endl;
    // Include necessary details from the account to display
}

class Admin : public User{
    public:
    Admin(string uname) : User(uname) {}
    void addEmployee(string userName);
    void increaseDate();
    void setAnnualSavingInterest(double interestRate);
    void setOverdraftCharge(double charge);
    void viewTransactions() override;
};

void Admin::addEmployee(string userName) {
    Employee* newEmployee = new Employee(userName);
    // Implement adding the employee to the system
    cout << "Employee added successfully." << endl;
}

void Admin::increaseDate() {
    // Implement logic to increase the date by 1 day
    time_t t = time(0);
    struct tm* now = localtime(&t);
    now->tm_mday += 1; // Increase the day by 1
    mktime(now);
    cout << "Date increased by 1 day." << endl;
}

class Customer : public User {
    private:
    static int customerCounter;

    public:
    Customer() : User("customer" + to_string(++customerCounter)) {}
    Customer(string uname): User(uname) {}
    void viewTransactions(Account* account);
    void deposit(Account* account,double amount);
    void withdraw(Account* account,double amount);
    void viewTransactions() override;
};
 

 int main(){
    
    return 0;
 }