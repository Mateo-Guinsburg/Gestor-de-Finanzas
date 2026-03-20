#include <string>
#include <ctime>
#include <chrono>
#include <stdexcept>

class Expenditure{
    private:
        std::string name;
        double amount;
        std::string type;
        std::string date;

        static std::string nowDate();
    public:
        Expenditure(const std::string &name, double amount, const std::string &type, const std::string &date):
        name(name), amount(amount), type(type), date(date){} //full parameter constructor 
        Expenditure(const std::string &name, double amount, const std::string &type):
        name(name), amount(amount), type(type), date(nowDate()){} //automatically fills date
        Expenditure(const std::string &name, const std::string &type):name(name), amount(0), type(type), date(nowDate()){}

        void setName(const std::string &name);
        void setAmount(double amt);
        void setType(const std::string &type);
        void setDate(const std::string &date);

        const std::string &getName() const;
        double getAmount() const;
        const std::string &getType() const;
        const std::string &getDate() const;
};

//Defensive enhancements

// Add Expenditure(..., std::string date = nowDate()) to avoid duplicate ctors.
// Validate amount >= 0 either in constructor or setAmount.