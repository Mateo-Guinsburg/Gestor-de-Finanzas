#include "expenditure.h"

std::string Expenditure::nowDate(){
    auto now = std::chrono::system_clock::now(); 
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm{};
    localtime_r(&t, &tm); // or localtime_s on Windows
    char date[11];
    std::strftime(date, sizeof(date), "%d-%m-%Y", &tm);
    return std::string(date);
}

void Expenditure::setName(const std::string &name){this->name = name;}
void Expenditure::setAmount(double amt){
    if(amt < 0){
        throw(std::invalid_argument("Negative amount not allowed."));
    }
    amount = amt;
}
void Expenditure::setType(const std::string &type){this->type = type;}
// void Expenditure:: setDate(const std::string &date); later implementation


const std::string & Expenditure::getName() const{return name;}
double Expenditure::getAmount() const{return amount;}
const std::string & Expenditure::getType() const{return type;}
const std::string & Expenditure::getDate() const{return date;}

