#include <iostream>
#include "BankAccount.hpp"

int main() {
    BankAccount account(1000, "John Doe");
    std::cout << account << std::endl;

    account.deposit(500);
    std::cout << account << std::endl;

    account.transferOwnership("Jane Doe");
    std::cout << "New owner: " << account.getAccountHolder() << std::endl;

    if (account.withdraw(1000)) {
        std::cout << "Successfully withdrew $1000" << std::endl;
        std::cout << "New balance: $" << account.getCurrentBalance() << std::endl;
    }
    else {
        std::cout << "Insufficient funds to withdraw $1000" << std::endl;
        std::cout << "You are $" << 1000 - account.getCurrentBalance() << " short" << std::endl;
    }

    return 0;
}
