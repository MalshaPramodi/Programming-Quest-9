#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>
#include <conio.h>

using namespace std;

// Function to get password without displaying it
string getPassword();

// Base class for User
class User {
protected:
    string username;
    string password;

public:
    User(const string& username, const string& password)
        : username(username), password(password) {}

    virtual void login() = 0; // Pure virtual function
    virtual string getPassword() const = 0; // Pure virtual function
    virtual int displayMenu() = 0; // Pure virtual function
    virtual void performAction(int choice) = 0; // Pure virtual function
};

// Derived class for Administrator
class Administrator : public User {
public:
    Administrator(const string& username)
        : User(username, "Password@1234") {}

    void login() override {
        cout << "Administrator logged in." << endl;
        int choice;
        do {
            choice = displayMenu();
            performAction(choice);
        } while (choice != 3); // 3 is the option for Exit
    }

    string getPassword() const override {
        return password;
    }

    int displayMenu() override {
        cout << "Administrator Menu:" << endl;
        cout << "1. Increase Date" << endl;
        cout << "2. Add Employee" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        return choice;
    }

    void performAction(int choice) override {
        switch (choice) {
        case 1:
            increaseDate();
            break;
        case 2:
            cout << "Adding Employee... (placeholder)" << endl;
            addEmployee();
            break;
        case 3:
            cout << "Exiting Administrator Menu." << endl;
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    }

    void increaseDate() {
        // Code to increase date by 1 day
        time_t now = time(0);
        tm* currentTime = localtime(&now);

        currentTime->tm_mday += 1; // Increase day by 1

        mktime(currentTime); // Update the time structure

        cout << "Date increased by 1 day." << endl;
        cout << "New Date: " << asctime(currentTime); // Print the updated date
    }

    // Other functionalities for Administrator
    void addEmployee() {
        string newEmployeeUsername;
        cout << "Enter new employee's username: ";
        cin >> newEmployeeUsername;

        // Create a file named by employee username (ex: employee001)
        ofstream employeeFile(newEmployeeUsername + ".txt");

        if (employeeFile.is_open()) {
            employeeFile << "Welcome to the system, " << newEmployeeUsername << "!\n";
            employeeFile.close();
            cout << "Employee '" << newEmployeeUsername << "' added successfully." << endl;
        }
        else {
            cout << "Failed to create file for the employee." << endl;
        }
    }
};

// Derived class for Customer
class Customer : public User {
private:
    string name;
    string mobileNumber;
    double balance;
    string accountFileName;

public:
    Customer(const string& username, const string& accountFileName)
        : User(username, "Password@1234"), name("Admin"), mobileNumber("1234567890"), balance(0.0), accountFileName(accountFileName) {
        loadAccountData();
    }

    void login() override {
        cout << "Customer logged in." << endl;
        int choice;
        do {
            choice = displayMenu();
            performAction(choice);
        } while (choice != 4); // 4 is the option for Exit

        saveAccountData();
    }

    string getUsername() const {
        return username;
    }

    string getAccountFileName() const {
        return accountFileName;
    }

    string getPassword() const override {
        return password;
    }

    int displayMenu() override {
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

    void performAction(int choice) override {
        switch (choice) {
        case 1:
            deposit();
            break;

        case 2:
            withdraw();
            break;

        case 3:
            viewTransactions();
            break;
        case 4:
            cout << "Exiting Customer Menu." << endl;
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    }

    void deposit() {
        double amount;
        cout << "Enter Deposit amount: ";
        cin >> amount;
        balance += amount;
        logTransaction(amount, "Deposit");
        cout << "Deposit successful. New balance: " << balance << endl;
    }

    void withdraw() {
        double amount;
        cout << "Enter withdrawal amount: ";
        cin >> amount;
        if (balance >= amount) {
            balance -= amount;
            logTransaction(amount, "Withdrawal");
            cout << "Withdrawal successful. New balance: " << balance << endl;
        }
        else {
            cout << "Insufficient funds." << endl;
        }
    }

    void viewTransactions() const {
        cout << "Transaction History:" << endl;
        ifstream transactionFile(getTransactionFileName());
        if (transactionFile.is_open()) {
            string line;
            while (getline(transactionFile, line)) {
                cout << line << endl;
            }
            transactionFile.close();
        }
        else {
            cout << "No transaction history found." << endl;
        }
    }

private:
    string getTransactionFileName() const {
        return accountFileName;
    }

    void logTransaction(double amount, const string& type) {
        ofstream transactionFile(getTransactionFileName(), ios::app);
        if (!transactionFile.is_open()) {
            cout << "Error opening transaction file." << endl;
            return;
        }
        transactionFile << "Amount: " << amount << ", Type: " << type << ", Date: " << getCurrentDateTime() << endl;
        transactionFile.close();
    }

    string getCurrentDateTime() const {
        time_t now = time(0);
        tm* currentTime = localtime(&now);
        char formattedTime[20];
        strftime(formattedTime, sizeof(formattedTime), "%Y-%m-%d %H:%M:%S", currentTime);
        return formattedTime;
    }

    // Other functionalities for Customer
    void loadAccountData() {
        ifstream accountFile(accountFileName);

        if (accountFile.is_open()) {
            accountFile >> name >> mobileNumber >> balance;
            accountFile.close();
        }
    }

    void saveAccountData() {
        ofstream accountFile(accountFileName, ios::app);

        if (accountFile.is_open()) {
            accountFile << name << "\n" << mobileNumber << "\n" << balance << "\n";
            accountFile.close();
        }
        else {
            cout << "Error saving account data." << endl;
        }
    }
};

// Derived class for Bank Employee
class BankEmployee : public User {
private:
    vector<Customer> customers;

public:
    BankEmployee(const string& username)
        : User(username, "Password@1234") {}

    void login() override {
        cout << "Bank Employee logged in." << endl;
        int choice;
        do {
            choice = displayMenu();
            performAction(choice);
        } while (choice != 7); // 7 is the option for Exit
    }

    string getPassword() const override {
        return password;
    }

    int displayMenu() override {
        cout << "Bank Employee Menu:" << endl;
        cout << "1. Add Customer" << endl;
        cout << "2. Close Customer's Account" << endl;
        cout << "3. Deposit Money" << endl;
        cout << "4. Withdraw Money" << endl;
        cout << "5. Set Overdraft Limit" << endl;
        cout << "6. View Transactions" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        return choice;
    }

    void performAction(int choice) override {
        switch (choice) {
        case 1:
            cout << "Adding Customer... (placeholder)" << endl;
            addCustomer();
            break;

        case 2:
            closeAccount();
            break;

        case 3:
            deposit();
            break;

        case 4:
            withdraw();
            break;

        case 6:
            viewTransactions();
            break;

        case 7:
            cout << "Exiting Bank Employee Menu." << endl;
            break;

        default:
            cout << "Invalid choice. Try again." << endl;
        }
    }

    void addCustomer() {
        string newCustomerUsername;
        cout << "Enter new customer's username: ";
        cin >> newCustomerUsername;

        string newAccountNumber = generateUniqueAccountNumber();

        string accountType;
        cout << "Enter account type (Saving/Current): ";
        cin >> accountType;

        string accountFileName(newAccountNumber + "_" + accountType + ".txt");
        ofstream accountFile(accountFileName);

        if (accountFile.is_open()) {
            accountFile << newAccountNumber << "\nWelcome to the system, " << newCustomerUsername << "!\n";
            accountFile.close();
            cout << "Customer '" << newCustomerUsername << "' added successfully with account number: " << newAccountNumber << endl;

            Customer newCustomer(newCustomerUsername, accountFileName);
            customers.push_back(newCustomer);
        }
        else {
            cout << "Failed to create file for the customer." << endl;
        }
    }

    string generateUniqueAccountNumber() {
        static int accountCounter = 100000;
        return to_string(accountCounter++);
    }

    void closeAccount() {
        string customerUsername;
        cout << "Enter customer's username: ";
        cin >> customerUsername;

        for (auto it = customers.begin(); it != customers.end(); ++it) {
            if (it->getUsername() == customerUsername) {
                customers.erase(it);
                cout << "Account for customer " << customerUsername << " closed successfully" << endl;
                break;
            }
        }
}
    void deposit() {
        string customerUsername;
        cout << "Enter customer's username: ";
        cin >> customerUsername;

        for (Customer& customer : customers) {
            if (customer.getUsername() == customerUsername) {
                double amount;
                customer.deposit();
                break;
            }
        }
    }

    void withdraw() {
        string customerUsername;
        cout << "Enter customer's username: ";
        cin >> customerUsername;

        for (Customer& customer : customers) {
            if (customer.getUsername() == customerUsername) {
                double amount;
                customer.withdraw();
                break;
            }
        }
    }

    void viewTransactions() {
        string customerUsername;
        cout << "Enter customer's username: ";
        cin >> customerUsername;

        for (const Customer& customer : customers) {
            if (customer.getUsername() == customerUsername) {
                customer.viewTransactions();
                break;
            }
        }
    }
};

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
    cin.ignore();
    cout << endl;
    return password;
}

int main() {
    cout << "-------------------- LMN Online Banking System ----------------------------------" << endl;

    string username;
    cout << "Enter username: ";
    cin >> username;

    User* currentUser = nullptr;

    if (username.find("admin") != string::npos) {
        currentUser = new Administrator(username);
    }
    else if (username.find("employee") != string::npos) {
        currentUser = new BankEmployee(username);
    }
    else if (username.find("customer") != string::npos) {
        string accountFileName = username + ".txt";
        currentUser = new Customer(username, accountFileName);
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