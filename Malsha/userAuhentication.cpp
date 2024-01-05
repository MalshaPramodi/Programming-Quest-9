#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <string>

class User {
protected:
    std::string username;
    std::string password;

public:
    User(const std::string& uname, const std::string& pwd)
        : username(uname), password(pwd) {}

    virtual ~User() {}

    virtual bool authenticate(const std::string& enteredPassword) const {
        return password == enteredPassword;
    }

    const std::string& getUsername() const {
        return username;
    }
};

class Administrator : public User {
public:
    Administrator(const std::string& uname)
        : User(uname, "Password@1234") {}

    void increaseDate() {
        // Implement date increase logic
    }

    // Add more functionalities specific to Administrator
};

class BankEmployee : public User {
public:
    BankEmployee(const std::string& uname)
        : User(uname, "Password@1234") {}

    // Add functionalities specific to BankEmployee
};

class Customer : public User {
public:
    Customer(const std::string& uname)
        : User(uname, "Password@1234") {}

    // Add functionalities specific to Customer
};

class Account {
protected:
    std::string accountNumber;
    std::string customerName;
    std::string contactNumber;
    double balance;

    void logTransaction(const std::string& type, double amount, const std::string& depositorName = "") {
        // Implement transaction logging
    }

public:
    Account(const std::string& accNum, const std::string& custName, const std::string& contactNum)
        : accountNumber(accNum), customerName(custName), contactNumber(contactNum), balance(0.0) {}

    virtual ~Account() {}

    virtual void deposit(double amount, const std::string& depositorName) {
        balance += amount;
        logTransaction("Deposit", amount, depositorName);
    }

    virtual void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            logTransaction("Withdrawal", amount);
        } else {
            std::cout << "Insufficient funds!\n";
        }
    }

    virtual void displayTransactions() const {
        // Implement transaction display logic
    }
};

class SavingsAccount : public Account {
    double annualInterestRate;

public:
    SavingsAccount(const std::string& accNum, const std::string& custName, const std::string& contactNum,
                   double interestRate)
        : Account(accNum, custName, contactNum), annualInterestRate(interestRate) {}

    void deposit(double amount, const std::string& depositorName) override {
        balance += amount;
        logTransaction("Deposit", amount, depositorName);
        calculateInterest();
    }

    void calculateInterest() {
        double interest = balance * annualInterestRate;
        balance += interest;
        logTransaction("Interest", interest);
    }
};

class CurrentAccount : public Account {
public:
    CurrentAccount(const std::string& accNum, const std::string& custName, const std::string& contactNum)
        : Account(accNum, custName, contactNum) {}

    void withdraw(double amount) override {
        if (balance >= amount) {
            balance -= amount;
            logTransaction("Withdrawal", amount);
        } else {
            std::cout << "Insufficient funds!\n";
        }
    }
};

int main() {
    // Authentication
    std::string enteredUsername;
    std::string enteredPassword;

    std::cout << "Enter username: ";
    std::cin >> enteredUsername;
    std::cout << "Enter password: ";
    std::cin >> enteredPassword;

    User* currentUser = nullptr;

    // Check user type and authenticate
    if (enteredUsername.substr(0, 3) == "adm" && enteredUsername.size() == 6) {
        currentUser = new Administrator(enteredUsername);
    } else if (enteredUsername.substr(0, 3) == "emp" && enteredUsername.size() == 6) {
        currentUser = new BankEmployee(enteredUsername);
    } else if (enteredUsername.substr(0, 3) == "cus" && enteredUsername.size() == 6) {
        currentUser = new Customer(enteredUsername);
    } else {
        std::cout << "Invalid username!\n";
        return 1;
    }

    if (currentUser->authenticate(enteredPassword)) {
        std::cout << "Authentication successful!\n";

        // Now you can proceed with user-specific functionalities
        // For example:
        if (dynamic_cast<Administrator*>(currentUser) != nullptr) {
            Administrator* admin = dynamic_cast<Administrator*>(currentUser);
            admin->increaseDate();
            // Add more functionalities for Administrator
        } else if (dynamic_cast<BankEmployee*>(currentUser) != nullptr) {
            BankEmployee* employee = dynamic_cast<BankEmployee*>(currentUser);
            // Add more functionalities for BankEmployee
        } else if (dynamic_cast<Customer*>(currentUser) != nullptr) {
            Customer* customer = dynamic_cast<Customer*>(currentUser);
            // Add more functionalities for Customer
        }

        // Clean up
        delete currentUser;
        return 0;
    } else {
        std::cout << "Authentication failed!\n";
        // Clean up
        delete currentUser;
        return 1;
    }
}
