#include "manager.h"
#include <stdexcept>
#include <sstream>
#include <tuple>

static std::tuple<int,int,int> parseDate(const std::string &date) {
    std::istringstream iss(date);
    int day, month, year;
    char sep1, sep2;
    if (!(iss >> day >> sep1 >> month >> sep2 >> year) || sep1 != '/' || sep2 != '/' || !iss.eof()) {
        throw std::invalid_argument("Invalid date format, expected DD/MM/YYYY");
    }
    return {year, month, day};
}

 void Manager::addExpenditure(const Expenditure &e) {
    list.push_back(e);
}

void Manager::removeExpenditure(size_t index){
    if(index >= list.size()){
        throw(std::invalid_argument("Invalid index: out of range."));
    }
    list.erase(list.begin() + index);
}

double Manager::getTotalAmount() const {
    double total = 0;
    for (const auto& e : list) {
        total += e.getAmount();
    }
    return total;
}

void Manager::showAll() const{
    for (const auto& e : list) {
        e.show();
    }
}

void Manager::filterByType(const std::string &type){
    for(const auto& e : list){
        if(e.getType() == type){
            e.show();
        }
    }
}

void Manager::filterByDateRange(const std::string &start, const std::string &end){
    auto startDate = parseDate(start);
    auto endDate = parseDate(end);
    if (startDate > endDate) {
        throw std::invalid_argument("Invalid range: Start date must be before end date");
    }

    for (const auto& e : list) {
        auto current = parseDate(e.getDate());
        if (current >= startDate && current <= endDate) {
            e.show();
        }
    }
}
