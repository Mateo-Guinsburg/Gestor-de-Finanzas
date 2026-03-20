#include <string>
#include <ctime>
#include <chrono>
#include <stdexcept>
#include <sstream>

class Expenditure{
    private:
        std::string name;
        double amount;
        std::string type;
        std::string date;

        bool validate_amount(double amt);
        bool validate_name(const std::string &name);
        bool validate_type(const std::string &type);
        bool validate_date(const std::string &date);
        static std::string nowDate();
    public:
        //full parameter constructor 
        Expenditure(const std::string &name, double amount, const std::string &type, const std::string &date)
        :name(name), type(type), date(date){
             if (!validate_name(name)) {
                throw std::invalid_argument("Invalid name: cannot be empty.");
            }
            if (!validate_type(type)) {
                throw std::invalid_argument("Invalid type: cannot be empty.");
            }
            if(!validate_date(date)){
                throw std::invalid_argument("Invalid date: must be in DD/MM/YYYY format or date non-existent.");
            }
            if(validate_amount(amount)){
                this->amount = amount;
            };
        }
        //automatically fills date
        Expenditure(const std::string &name, double amount, const std::string &type)
        :name(name), type(type), date(nowDate()){
            if (!validate_name(name)) {
                throw std::invalid_argument("Invalid name: cannot be empty.");
            }
            if (!validate_type(type)) {
                throw std::invalid_argument("Invalid type: cannot be empty.");
            }
            if(validate_amount(amount)){
                this->amount = amount;
            };
        } 
        //default constructor
        Expenditure(const std::string &name, const std::string &type):name(name), amount(0), type(type), date(nowDate()){
            if (!validate_name(name)) {
                throw std::invalid_argument("Invalid name: cannot be empty.");
            }
            if (!validate_type(type)) {
                throw std::invalid_argument("Invalid type: cannot be empty.");
            }
        }

        void setName(const std::string &name);
        void setAmount(double amt);
        void setType(const std::string &type);
        void setDate(const std::string &date);

        const std::string &getName() const;
        double getAmount() const;
        const std::string &getType() const;
        const std::string &getDate() const;
};