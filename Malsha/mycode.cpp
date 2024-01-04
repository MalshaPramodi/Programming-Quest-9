#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <iomanip>

class Account {
protected:
    std::string accountNumber;
    std::string customerName;
    std::string contactNumber;
    double balance;
    void logTransaction(const std::string& type, double amount, const std::string& depositorName = "") {
        std::ofstream file(accountNumber + "_transactions.txt", std::ios::app);
        if (file.is_open()) {
            std::time_t now = std::time(0);
            std::tm* timeInfo = std::localtime(&now);
             char buffer[80];
            std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo) ;
            file<<buffer<< " - " << type << " of LKR "<< std::fixed << std::setprecision(2) << amount;
            if (!depositorName.empty()) {
                file << " by " << depositorName;
            }
            file << "\n";
            file.close();
        } else {
            std::cout << "Error logging transaction.\n";
        }
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
        std::cout << "Account Number: " << accountNumber << "\n";
        std::cout << "Customer Name: " << customerName << "\n";
        std::cout << "Contact Number: " << contactNumber << "\n";
        std::cout << "Balance: LKR " << std::fixed << std::setprecision(2) << balance << "\n";

        std::ifstream file(accountNumber + "_transactions.txt");
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                std::cout << line << "\n";
            }
            file.close();
        } else {
            std::cout << "No transactions available.\n";
        }
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
    // Create a savings account
    SavingsAccount savingsAccount("S123", "John Doe", "1234567890", 0.03);

    // Deposit money into the savings account
    savingsAccount.deposit(1000.0, "External Depositor");

    // View transactions of the savings account
    savingsAccount.displayTransactions();

    // Create a current account
    CurrentAccount currentAccount("C456", "John Doe", "1234567890");

    // Withdraw money from the current account
    currentAccount.withdraw(2000.0);

    // View transactions of the current account
    currentAccount.displayTransactions();

    // Clean up
    return 0;
}
