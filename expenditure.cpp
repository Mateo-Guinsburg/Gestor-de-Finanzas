#include "expenditure.h"
#include <iomanip>

bool Expenditure::validate_amount(double amt){
    if(amt < 0){
        throw(std::invalid_argument("Invalid amount: cannot be negative."));
    }
    return true;
}

bool Expenditure::validate_name(const std::string &name) {
    return !name.empty();
}

bool Expenditure::validate_type(const std::string &type) {
    return !type.empty();
}

bool Expenditure::validate_date(const std::string &date) {
    std::istringstream iss(date);
    int day, month, year;
    char sep1, sep2;
    if (!(iss >> day >> sep1 >> month >> sep2 >> year) || sep1 != '/' || sep2 != '/' || !iss.eof()) {
        return false;
    }
    if (month < 1 || month > 12) return false;
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int max_days = days_in_month[month - 1];
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)) {
        max_days = 29;  // Leap year February
    }
    if (day < 1 || day > max_days) return false;
    return true;
}

std::string Expenditure::nowDate(){
    auto now = std::chrono::system_clock::now(); 
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm{};
    localtime_r(&t, &tm); 
    //localtime_s(&tm, &t); //on Windows
    char date[11];
    std::strftime(date, sizeof(date), "%d/%m/%Y", &tm);
    return std::string(date);
}

void Expenditure::setName(const std::string &name) {
    if (validate_name(name)) {
        this->name = name;
    } else {
        throw std::invalid_argument("Invalid name: cannot be empty.");
    }
}
void Expenditure::setType(const std::string &type) {
    if (validate_type(type)) {
        this->type = type;
    } else {
        throw std::invalid_argument("Invalid type: cannot be empty.");
    }
}
void Expenditure::setDate(const std::string &date) {
    if (validate_date(date)) {
        this->date = date;
    } else {
        throw std::invalid_argument("Invalid date: must be in DD/MM/YYYY format.");
    }
}
void Expenditure::setAmount(double amt){
    if(validate_amount(amt)){
        amount = amt;
    }
}

const std::string & Expenditure::getName() const{return name;}
double Expenditure::getAmount() const{return amount;}
const std::string & Expenditure::getType() const{return type;}
const std::string & Expenditure::getDate() const{return date;}

void Expenditure::show() const{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << amount;
    std::cout << name << " | $" << oss.str() << " | " << type << " | " << date << std::endl;
}
