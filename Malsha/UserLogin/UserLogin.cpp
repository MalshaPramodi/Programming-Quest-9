#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

// Base class for User
class User {
protected:
    string username;
    string password;

public:
    User(const string& username, const string& password)
        : username(username), password(password) {}

    virtual void login() = 0; // Pure virtual function
};

// Derived class for Administrator
class Administrator : public User {
public:
    Administrator(const string& username, const string& password)
        : User(username, password) {}

    void login() override {
        cout << "Administrator logged in." << endl;
    }

    void increaseDate() {
        // Code to increase date by 1 day
        cout << "Date increased by 1 day." << endl;
    }

    // Other functionalities for Administrator
};

// Derived class for Bank Employee
class BankEmployee : public User {
public:
    BankEmployee(const string& username, const string& password)
        : User(username, password) {}

    void login() override {
        cout << "Bank Employee logged in." << endl;
    }

    // Other functionalities for Bank Employee
};

// Derived class for Customer
class Customer : public User {
private:
    string name;
    string mobileNumber;
    double balance;

public:
    Customer(const string& username, const string& password, const string& name, const string& mobileNumber)
        : User(username, password), name(name), mobileNumber(mobileNumber), balance(0.0) {}

    void login() override {
        cout << "Customer logged in." << endl;
    }

    void deposit(double amount) {
        balance += amount;
        cout << "Deposit successful. New balance: " << balance << endl;
    }

    void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            cout << "Withdrawal successful. New balance: " << balance << endl;
        } else {
            cout << "Insufficient funds." << endl;
        }
    }

    // Other functionalities for Customer
};

int main() {
    string adminUsername, adminPassword, employeeUsername, employeePassword, customerUsername, customerPassword;
    cout<<"hi"<<endl;

    cout << "Enter Administrator username: ";
    cin >> adminUsername;
    cout << "Enter Administrator password: ";
    cin >> adminPassword;

    cout << "Enter Bank Employee username: ";
    cin >> employeeUsername;
    cout << "Enter Bank Employee password: ";
    cin >> employeePassword;

    cout << "Enter Customer username: ";
    cin >> customerUsername;
    cout << "Enter Customer password: ";
    cin >> customerPassword;

    // Creating instances with user inputs
    Administrator admin(adminUsername, adminPassword);
    BankEmployee employee(employeeUsername, employeePassword);
    Customer customer(customerUsername, customerPassword, "John Doe", "1234567890");

    // Logging in
    admin.login();
    employee.login();
    customer.login();

    // Simulating deposit and withdrawal for customer
    customer.deposit(500.0);
    customer.withdraw(200.0);

    return 0;
}
