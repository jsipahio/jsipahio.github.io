#include "BankAccount.hpp"

BankAccount::BankAccount() {
    balance = 0;
    owner = "";
}

BankAccount::BankAccount(double startingBalance, std::string name) {
    balance = startingBalance;
    owner = name;
}

std::string BankAccount::getAccountHolder() const {
    return owner;
}

double BankAccount::getCurrentBalance() const {
    return balance;
}

void BankAccount::transferOwnership(std::string name) {
    owner = name;
}

void BankAccount::deposit(double amount) {
    if (amount < 0) {
        std::cerr << "Invalid deposit - should not be negative! Abort..." << std::endl;
        exit(1);
    }

    balance += amount;
}

bool BankAccount::withdraw(double amount) {
    if (amount < 0) {
        std::cerr << "Invalid withdrawl - should not be negative! Abort..." << std::endl;
        exit(2);
    }

    if (amount <= balance) {
        balance -= amount;
        return true;
    }
    else return false;
}

std::ostream& operator<<(std::ostream& out, const BankAccount& account) {
    out << "Balance: " << account.getCurrentBalance() << std::endl;
    out << "Ownder:  " << account.getAccountHolder() << std::endl;
    return out;
}
