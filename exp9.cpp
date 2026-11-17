// Experiment 9: Custom exception hierarchy for banking transactions
#include <iostream>
#include <exception>
#include <string>
#include <sstream>
using namespace std;

class BankException : public exception {
protected:
    string msg;
public:
    explicit BankException(string m) : msg(std::move(m)) {}
    const char* what() const noexcept override { return msg.c_str(); }
};

class InsufficientFundsException : public BankException {
public:
    double balance, requested;
    InsufficientFundsException(double bal, double req)
        : BankException(build(bal, req)), balance(bal), requested(req) {}
private:
    static string build(double bal, double req) {
        ostringstream o;
        o << "Insufficient funds: balance=" << bal << ", requested=" << req;
        return o.str();
    }
};

class InvalidAmountException : public BankException {
public:
    explicit InvalidAmountException(double amt)
        : BankException("Invalid amount: " + to_string(amt)) {}
};

class AccountNotFoundException : public BankException {
public:
    explicit AccountNotFoundException(const string& id)
        : BankException("Account not found: " + id) {}
};

class DailyLimitExceededException : public BankException {
public:
    explicit DailyLimitExceededException(double limit)
        : BankException("Daily withdrawal limit exceeded (limit " + to_string((long)limit) + ")") {}
};

class Account {
    string id;
    double balance;
    double withdrawnToday = 0;
    static constexpr double DAILY_LIMIT = 20000;
public:
    Account(string i, double b) : id(i), balance(b) {}
    const string& getId() const { return id; }
    double getBalance() const { return balance; }
    void deposit(double amt) {
        if (amt <= 0) throw InvalidAmountException(amt);
        balance += amt;
    }
    void withdraw(double amt) {
        if (amt <= 0) throw InvalidAmountException(amt);
        if (withdrawnToday + amt > DAILY_LIMIT) throw DailyLimitExceededException(DAILY_LIMIT);
        if (amt > balance) throw InsufficientFundsException(balance, amt);
        balance -= amt;
        withdrawnToday += amt;
    }
};

class Bank {
    Account accounts[2] = {Account("A100", 15000), Account("B200", 3000)};
public:
    Account& find(const string& id) {
        for (auto& a : accounts) if (a.getId() == id) return a;
        throw AccountNotFoundException(id);
    }
    void transfer(const string& from, const string& to, double amt) {
        Account& src = find(from);
        Account& dst = find(to);
        src.withdraw(amt);
        dst.deposit(amt);
        cout << "  Transfer OK: " << amt << " from " << from << " to " << to << "\n";
    }
};

int main() {
    Bank bank;
    struct Test { string from, to; double amt; };
    Test tests[] = {
        {"A100", "B200", 5000},     // ok
        {"B200", "A100", 10000},    // insufficient funds
        {"A100", "B200", -10},      // invalid amount
        {"A100", "Z999", 100},      // account not found
        {"A100", "B200", 9000},     // ok
        {"A100", "B200", 8000},     // daily limit (5000+9000+8000 > 20000)
    };
    for (const auto& t : tests) {
        cout << "Transfer " << t.amt << " " << t.from << " -> " << t.to << "\n";
        try {
            bank.transfer(t.from, t.to, t.amt);
        } catch (const InsufficientFundsException& e) {
            cout << "  [InsufficientFunds] " << e.what() << " (short by " << e.requested - e.balance << ")\n";
        } catch (const InvalidAmountException& e) {
            cout << "  [InvalidAmount] " << e.what() << "\n";
        } catch (const BankException& e) {            // catches remaining derived types
            cout << "  [BankException] " << e.what() << "\n";
        } catch (...) {
            cout << "  Unknown error\n";
        }
    }
    cout << "Final balances: A100=" << bank.find("A100").getBalance()
         << ", B200=" << bank.find("B200").getBalance() << "\n";
    return 0;
}
