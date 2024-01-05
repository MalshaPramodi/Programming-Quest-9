#include <iostream>
#include <conio.h>
#include <string>

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
            break;
            // Add more cases for additional options
        default:
            cout << "Invalid choice. Try again." << endl;
        }
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
    BankEmployee(const string& username)
        : User(username, "Password@1234") {}

    void login() override {
        cout << "Bank Employee logged in." << endl;
        int choice;
        do {
            choice = displayMenu();
            performAction(choice);
        } while (choice != 9); // 9 is the option for Exit
    }

    string getPassword() const override {
        return password;
    }

    int displayMenu() override {
        cout << "Bank Employee Menu:" << endl;
        cout << "1. Add Customer" << endl;
        cout << "2. Create Saving Account" << endl;
        cout << "3. Create Current Account" << endl;
        cout << "4. Close Customer's Account" << endl;
        cout << "5. Deposit Money" << endl;
        cout << "6. Withdraw Money" << endl;
        cout << "7. Set Overdraft Limit" << endl;
        cout << "8. View Transactions" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        return choice;
    }

    void performAction(int choice) override {
        switch (choice) {
        case 1:
            cout << "Adding Customer... (placeholder)" << endl;
            break;
            // Add more cases for additional options
        default:
            cout << "Invalid choice. Try again." << endl;
        }
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
    Customer(const string& username)
        : User(username, "Password@1234"), name("John Doe"), mobileNumber("1234567890"), balance(0.0) {}

    void login() override {
        cout << "Customer logged in." << endl;
        int choice;
        do {
            choice = displayMenu();
            performAction(choice);
        } while (choice != 4); // 4 is the option for Exit
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
            deposit(500.0);
            break;
        case 2:
            withdraw(200.0);
            break;
            // Add more cases for additional options
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    }

    void deposit(double amount) {
        balance += amount;
        cout << "Deposit successful. New balance: " << balance << endl;
    }

    void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            cout << "Withdrawal successful. New balance: " << balance << endl;
        }
        else {
            cout << "Insufficient funds." << endl;
        }
    }

    // Other functionalities for Customer
};

int main() {
    cout << "-------------------- LMN Online Banking System ----------------------------------" << endl;

    string username;
    cout << "Enter username: ";
    cin >> username;

    User* currentUser;

    // Identify the type of user based on the username
    if (username.find("admin") != string::npos) {
        currentUser = new Administrator(username);
    }
    else if (username.find("employee") != string::npos) {
        currentUser = new BankEmployee(username);
    }
    else if (username.find("customer") != string::npos) {
        currentUser = new Customer(username);
    }
    else {
        cout << "Unknown user type. Exiting program." << endl;
        return 1;
    }

    cout << "Enter password: ";
    string enteredPassword = getPassword();

    // Check if the entered password is correct
    if (enteredPassword == currentUser->getPassword()) {
        // Login the user and display the menu
        currentUser->login();

        delete currentUser; // Release memory allocated for the user
    }
    else {
        cout << "Incorrect password. Exiting program." << endl;
        delete currentUser; // Release memory allocated for the user
        return 1;
    }

    return 0;
}

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
