#pragma once

#include <string>
#include <vector>
#include <ranges>
#include "account.hpp" // card class
#include "money.hpp" // money class
// #include "db.hpp" // db class (save and load users)

namespace cash_overflow::user
{
    class User
    {
    private:
        std::string fullName;
        int userId;
        int age;
        std::vector<account::Account> accounts;
        money::Money money;
    public:
        User(std::string _fullName, int _age): fullName{_fullName}, age{_age} {}; //test here
        [[nodiscard]] std::string getFullName() const { return fullName; }
        [[nodiscard]] int getAge() const { return age; }

        void addNewAccount(unsigned int cardNumber) {
             account::Account::create(cardNumber).value().deposit(90);
        }
        void deleteAccount(unsigned int cardNumber) {
            // menu with user accounts
        }
        void cardOperations(unsigned int ) {
        
                // TODO: Output card operations and pick one of the options
            
                // TODO: Output message with error saying the card doesn't ex
        }
    };
    
} // namespace cash_overflow::user