#ifndef EXPENDITURE_H
#define EXPENDITURE_H

#include <string>
#include <ctime>
#include <chrono>
#include <stdexcept>
#include <sstream>
#include <iostream>

class Expenditure{
    private:
        std::string name;
        double amount;
        std::string type;
        std::string date;

        //validation functions for each attribute
        bool validate_amount(double amt);
        bool validate_name(const std::string &name);
        bool validate_type(const std::string &type);
        bool validate_date(const std::string &date);
        
        //returns the systems' date
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
        Expenditure():amount(0), date(nowDate()){}

        //setters
        void setName(const std::string &name);
        void setAmount(double amt);
        void setType(const std::string &type);
        void setDate(const std::string &date);

        //getters
        const std::string &getName() const;
        double getAmount() const;
        const std::string &getType() const;
        const std::string &getDate() const;
        
        void show() const;
};

#endif