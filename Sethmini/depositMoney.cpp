#include <iostream>
#include <string>

using namespace std;

class User {
public:
    virtual void depositMoney(double amount, string depositorName) = 0;
};

class Customer : public User {
private:
    double balance;

public:
    Customer() : balance(0) {} // Initialize balance to 0 for a new customer

    void depositMoney(double amount, string depositorName) override {
        // For demonstration, print a message indicating deposit
        cout << "Depositing " << amount << " for " << depositorName << endl;

        // Update the balance with the deposited amount
        balance += amount;
        cout << "New balance: " << balance << endl;
    }
};

int main() {
    // Example usage
    Customer customer;
    customer.depositMoney(100.0, "John Doe");

    return 0;
}
