#pragma once

namespace cash_overflow::currency
{
    enum class Currencies {
       Dollar,
       Euro,
       China,
    };

    class Currency {
        private:
            Currencies currencyType;
            char currencySymbol;
        public:
            virtual long double convert(long double value, Currencies destCurrency);
            virtual Currencies getCurrencyType();
    };

    class Dollar : Currency
    {
        long double convert(long double value, Currencies destCurrency) override {
            return (value/0,156);
        }

    template <>
    long double convert<Currencies::Euro, Currencies::Dollar>(long double value) {
        // TODO: print something like: Converting <value> <type> to <type>
        return (value/0.877);
    }

    template <>
    long double convert<Currencies::Dollar, Currencies::Euro>(long double value) {
        // TODO: print something like: Converting <value> <type> to <type>
        return (value*0.877);
    }

    template <>
    long double convert<Currencies::China, Currencies::Dollar>(long double value) {
        // TODO: print something like: Converting <value> <type> to <type>
        return (value*0,156);
    }

    template <>
    long double convert<Currencies::Dollar, Currencies::China>(long double value) {
        // TODO: print something like: Converting <value> <type> to <type> 
        return (value/0,156);
    }
} // namespace cash_overflow::currency
