#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Forward declaration of Customer class
class Customer;

// Function to get password without displaying it
string getPassword();

// TransactionLog class to handle logging
class TransactionLog {
private:
    string accountNumber;
    string accountType;  // New member variable to store account type
    ofstream logFile;

public:
    // Constructor to open the log file
    TransactionLog(const string& accountNumber, const string& accountType)
        : accountNumber(accountNumber), accountType(accountType), logFile(accountNumber + "_" + accountType + "_transactions.txt", ios::app) {
        if (!logFile.is_open()) {
            cerr << "Error opening transaction log file." << endl;
        }
    }

    // Destructor to close the log file
    ~TransactionLog() {
        logFile.close();
    }

    // Function to log a transaction
    void logTransaction(const string& transactionType, double amount) {
        if (logFile.is_open()) {
            logFile << "Type: " << transactionType << ", Amount: " << amount << endl;
        }
    }
};

// Base class for User
class User {
protected:
    string username;
    string password;

public:
    User(const string& username, const string& password)
        : username(username), password(password) {}

    virtual void login() = 0;
    virtual string getPassword() const = 0;
    virtual int displayMenu() = 0;
    virtual void performAction(int choice) = 0;
};

// Forward declaration of BankEmployee class
class BankEmployee;

// Derived class for Administrator
class Administrator : public User {
public:
    Administrator(const string& username)
        : User(username, "Password@1234") {}

    void login() override;
    string getPassword() const override;
    int displayMenu() override;
    void performAction(int choice) override;

    void increaseDate();
};

// Derived class for Customer
class Customer : public User {
private:
    string name;
    string mobileNumber;
    double balance;
    string accountNumber;
    string accountType;  // New member variable to store account type
    TransactionLog* transactionLog;

public:
    Customer(const string& username, const string& accountNumber, const string& accountType)
        : User(username, "Password@1234"), name("John Doe"), mobileNumber("1234567890"), balance(0.0), accountNumber(accountNumber), accountType(accountType), transactionLog(nullptr) {}

    ~Customer() {
        delete transactionLog;
    }

    string getUsername() const {
        return username;
    }

    string getAccountNumber() const {
        return accountNumber;
    }

    string getAccountType() const {
        return accountType;
    }

    void login() override;
    string getPassword() const override;
    int displayMenu() override;
    void performAction(int choice) override;

    void deposit(double amount, const string& accountType);
    void withdraw(double amount);

    void logTransaction(const string& transactionType, double amount);
};

// Derived class for Bank Employee
class BankEmployee : public User {
private:
    vector<Customer> customers;

public:
    BankEmployee(const string& username)
        : User(username, "Password@1234") {}

    void login() override;
    string getPassword() const override;
    int displayMenu() override;
    void performAction(int choice) override;

    void addCustomer();
    void createAccount(const string& accountType);
    void depositMoney();
};

// Implementation of Administrator class
void Administrator::login() {
    cout << "Administrator logged in." << endl;
    int choice;
    do {
        choice = displayMenu();
        performAction(choice);
    } while (choice != 3); // 3 is the option for Exit
}

string Administrator::getPassword() const {
    return password;
}

int Administrator::displayMenu() {
    cout << "Administrator Menu:" << endl;
    cout << "1. Increase Date" << endl;
    cout << "2. Add Employee" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    return choice;
}

void Administrator::performAction(int choice) {
    switch (choice) {
    case 1:
        increaseDate();
        break;
    case 2:
        cout << "Adding Employee... (placeholder)" << endl;
        break;
    default:
        cout << "Invalid choice. Try again." << endl;
    }
}

void Administrator::increaseDate() {
    cout << "Date increased by 1 day." << endl;
}

// Implementation of Customer class
void Customer::login() {
    transactionLog = new TransactionLog(accountNumber, accountType);

    cout << "Customer logged in." << endl;
    int choice;
    do {
        choice = displayMenu();
        performAction(choice);
    } while (choice != 4);
}

string Customer::getPassword() const {
    return password;
}

int Customer::displayMenu() {
    cout << "Customer Menu:" << endl;
    cout << "1. Deposit Money" << endl;
    cout << "2. Withdraw Money" << endl;
    cout << "3. View Transactions" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    return choice;
}

void Customer::performAction(int choice) {
    switch (choice) {
    case 1:
        deposit(500.0, accountType);
        break;
    case 2:
        withdraw(200.0);
        break;
    case 3:
        // View Transactions
        break;
    default:
        cout << "Invalid choice. Try again." << endl;
    }
}

void Customer::deposit(double amount, const string& accountType) {
    balance += amount;
    cout << "Deposit successful. New balance: " << balance << endl;

    logTransaction("Deposit", amount);
}

void Customer::withdraw(double amount) {
    if (balance >= amount) {
        balance -= amount;
        cout << "Withdrawal successful. New balance: " << balance << endl;

        logTransaction("Withdrawal", amount);
    }
    else {
        cout << "Insufficient funds." << endl;
    }
}

void Customer::logTransaction(const string& transactionType, double amount) {
    if (transactionLog) {
        transactionLog->logTransaction(transactionType, amount);

        ofstream transactionFile(accountNumber + "_" + accountType + "_transactions.txt", ios::app);
        if (transactionFile.is_open()) {
            transactionFile << "Type: " << transactionType << ", Amount: " << amount << endl;
            transactionFile.close();
        }
        else {
            cerr << "Error opening transaction file for account " << accountNumber << "." << endl;
        }
    }
}

// Implementation of BankEmployee class
void BankEmployee::login() {
    cout << "Bank Employee logged in." << endl;
    int choice;
    do {
        choice = displayMenu();
        performAction(choice);
    } while (choice != 7);
}

string BankEmployee::getPassword() const {
    return password;
}

int BankEmployee::displayMenu() {
    cout << "Bank Employee Menu:" << endl;
    cout << "1. Add Customer" << endl;
    cout << "2. Create Saving Account" << endl;
    cout << "3. Create Current Account" << endl;
    cout << "4. Close Customer's Account" << endl;
    cout << "5. Deposit Money" << endl;
    cout << "6. Withdraw Money" << endl;
    cout << "7. Exit" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    return choice;
}

void BankEmployee::performAction(int choice) {
    switch (choice) {
    case 1:
        addCustomer();
        break;
    case 2:
        createAccount("Saving");
        break;
    case 3:
        createAccount("Current");
        break;
    case 5:
        depositMoney();
        break;
    default:
        cout << "Invalid choice. Try again." << endl;
    }
}

void BankEmployee::addCustomer() {
    string newCustomerUsername;
    cout << "Enter new customer's username: ";
    cin >> newCustomerUsername;

    string newAccountNumber;
    cout << "Enter new customer's account number: ";
    cin >> newAccountNumber;

    string accountType;
    cout << "Enter account type (Saving/Current): ";
    cin >> accountType;

    auto it = find_if(customers.begin(), customers.end(), [newAccountNumber](const Customer& customer) {
        return customer.getAccountNumber() == newAccountNumber;
        });

    if (it != customers.end()) {
        cout << "Customer with account number " << newAccountNumber << " already exists." << endl;
    }
    else {
        Customer newCustomer(newCustomerUsername, newAccountNumber, accountType);
        customers.push_back(newCustomer);
        cout << "Customer added successfully." << endl;

        ofstream transactionFile(newAccountNumber + "_" + accountType + "_transactions.txt");
        if (!transactionFile.is_open()) {
            cerr << "Error creating transaction file for account " << newAccountNumber << "." << endl;
        }
    }
}

void BankEmployee::createAccount(const string& accountType) {
    string customerUsername;
    cout << "Enter customer's username: ";
    cin >> customerUsername;

    auto it = find_if(customers.begin(), customers.end(), [customerUsername](const Customer& customer) {
        return customer.getUsername() == customerUsername;
        });

    if (it != customers.end()) {
        Customer& customer = *it;

        customer.logTransaction("Account Creation - " + accountType, 0.0);

        cout << "Account created successfully for " << customerUsername << " - Type: " << accountType << endl;
    }
    else {
        cout << "Customer with username " << customerUsername << " not found." << endl;
    }
}

void BankEmployee::depositMoney() {
    string customerAccountNumber;
    cout << "Enter customer's account number: ";
    cin >> customerAccountNumber;

    auto it = find_if(customers.begin(), customers.end(), [customerAccountNumber](const Customer& customer) {
        return customer.getAccountNumber() == customerAccountNumber;
        });

    if (it != customers.end()) {
        Customer& customer = *it;

        double amount;
        cout << "Enter the deposit amount: ";
        cin >> amount;

        customer.deposit(amount, customer.getAccountType());  // Pass account type to deposit method
    }
    else {
        cout << "Customer with account number " << customerAccountNumber << " not found." << endl;
    }
}

// Main function
int main() {
    cout << "-------------------- LMN Online Banking System ----------------------------------" << endl;

    string username;
    cout << "Enter username: ";
    cin >> username;

    User* currentUser;

    if (username.find("admin") != string::npos) {
        currentUser = new Administrator(username);
    }
    else if (username.find("employee") != string::npos) {
        currentUser = new BankEmployee(username);
    }
    else if (username.find("customer") != string::npos) {
        currentUser = new Customer(username, "123456", "Saving");  // Example account number "123456"
    }
    else {
        cout << "Unknown user type. Exiting program." << endl;
        return 1;
    }

    cout << "Enter password: ";
    string enteredPassword = getPassword();

    if (enteredPassword == currentUser->getPassword()) {
        currentUser->login();
        delete currentUser;
    }
    else {
        cout << "Incorrect password. Exiting program." << endl;
        delete currentUser;
        return 1;
    }

    return 0;
}

// Function to get password without displaying it
string getPassword() {
    string password;
    char ch;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (!password.empty()) {
                cout << "\b \b";
                password.pop_back();
            }
        }
        else {
            cout << '*';
            password.push_back(ch);
        }
    }
    cout << endl;
    return password;
}
