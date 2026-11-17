// Experiment 2: Class hierarchy for a real-world entity (Bank Account),
// demonstrating access specifiers and member functions.
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

class BankAccount {
private:                       // not accessible outside the class
    string accountNumber;
    double balance;
protected:                     // accessible in derived classes
    string holderName;
    void log(const string& msg) const { cout << "  [LOG " << accountNumber << "] " << msg << "\n"; }
public:                        // accessible everywhere
    BankAccount(string num, string holder, double initial)
        : accountNumber(num), balance(initial), holderName(holder) {}
    virtual ~BankAccount() = default;

    // member functions
    void deposit(double amt) {
        if (amt <= 0) { cout << "  Invalid deposit amount\n"; return; }
        balance += amt;
        log("Deposited " + to_string(amt));
    }
    virtual bool withdraw(double amt) {
        if (amt <= 0 || amt > balance) { cout << "  Withdrawal failed\n"; return false; }
        balance -= amt;
        log("Withdrew " + to_string(amt));
        return true;
    }
    double getBalance() const { return balance; }
    string getAccountNumber() const { return accountNumber; }
    virtual void display() const {
        cout << fixed << setprecision(2)
             << "  " << accountNumber << " | " << holderName << " | Balance: " << balance << "\n";
    }
protected:
    void setBalance(double b) { balance = b; }
};

class SavingsAccount : public BankAccount {
    double interestRate;
public:
    SavingsAccount(string num, string holder, double initial, double rate)
        : BankAccount(num, holder, initial), interestRate(rate) {}
    void addInterest() {
        double interest = getBalance() * interestRate / 100.0;
        deposit(interest);                       // uses public member of base
        log("Interest credited");                // uses protected member of base
    }
    void display() const override {
        cout << "  [Savings @" << interestRate << "%]";
        BankAccount::display();
    }
};

class CurrentAccount : public BankAccount {
    double overdraftLimit;
public:
    CurrentAccount(string num, string holder, double initial, double od)
        : BankAccount(num, holder, initial), overdraftLimit(od) {}
    bool withdraw(double amt) override {
        if (amt <= 0 || amt > getBalance() + overdraftLimit) { cout << "  Overdraft limit exceeded\n"; return false; }
        setBalance(getBalance() - amt);          // protected setter
        log("Withdrew (overdraft allowed) " + to_string(amt));
        return true;
    }
    void display() const override {
        cout << "  [Current, OD limit " << overdraftLimit << "]";
        BankAccount::display();
    }
};

int main() {
    SavingsAccount s("SB1001", "Asha", 10000, 4.0);
    CurrentAccount c("CA2001", "Ravi", 5000, 2000);

    cout << "--- Savings ---\n";
    s.deposit(2500);
    s.withdraw(1000);
    s.addInterest();
    s.display();

    cout << "--- Current ---\n";
    c.withdraw(6500);   // uses overdraft
    c.withdraw(1000);   // exceeds limit
    c.display();

    cout << "--- Polymorphic list ---\n";
    vector<BankAccount*> accts = {&s, &c};
    for (auto* a : accts) a->display();

    // s.balance = 5;   // ERROR: private member
    // s.holderName;    // ERROR: protected member
    return 0;
}
