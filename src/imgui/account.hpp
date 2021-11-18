#pragma once

#include <tl/expected.hpp>
#include <vector>
#include <numbers>
#include <iostream>
#include "currency.hpp"
#include "error.h"

namespace cash_overflow::account
{
    enum class accountType {
        none = 0,
        Debit,
        Credit,
    };

    static bool isDebit(accountType type) {
        return type == accountType::Debit;
    }

    std::vector<unsigned int> db = {11333, 24444, 56666};
    class Account
    {
    private:
        unsigned int number_;
        std::string name_;
        long double balance_ = 0;
        currency::Currencies currentCurrency_ = currency::Currencies::Euro;
        accountType accountType_ = accountType::Debit;
        
    public:
        using Error = cash_overflow::error::Error;
        Account(unsigned int cardNumber): number_(cardNumber) {}
        static tl::expected<Account, Error> create(unsigned int cardNumber) {
           if(Account::exists(cardNumber)) {
               return Account{cardNumber};
           }
           else {
               return tl::make_unexpected("si fodeu");
           }
        }
        [[nodiscard]] static bool exists(unsigned int cardNumber) {
            return (std::ranges::find(db.begin(), db.end(), cardNumber) != db.end());
        }
        void deposit(long double value, currency::Currencies currency) {
            std::cout << value;
            if(currency != currentCurrency_)
                value = currency::convert<currency, currentCurrency_>;
            balance = balance + value;
            std::cout << test;
        }
        tl::expected<std::string, Error> withdraw(unsigned int value) {
            if((balance < 0 || ((balance - value) < 0)) && isDebit(accountType_)) [[unlikely]]
                tl::make_unexpected("Pobriii");
            else [[likely]] {
                balance = balance - value;
                return std::string ("Your current value is:")
            }
        }
        
    };
    
} // namespace cashoverflow::account
