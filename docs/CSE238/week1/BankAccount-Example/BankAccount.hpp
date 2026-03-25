#ifndef BANKACCOUNT_HPP
#define BANKACCOUNT_HPP

#include <string>
#include <iostream>

#include <string>
#include <iostream>

class BankAccount {
public:
    BankAccount();
    BankAccount(double startingBalance, std::string name);

    std::string getAccountHolder() const;
    double getCurrentBalance() const;

    void transferOwnership(std::string name);
    void deposit(double amount);
    bool withdraw(double amount);
private:
    double balance;
    std::string owner;
};

std::ostream& operator<<(std::ostream& out, const BankAccount& account);

#endif
