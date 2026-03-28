#include "manager.h"
#include <stdexcept>
#include <sstream>
#include <tuple>
#include <algorithm>

static std::tuple<int,int,int> parseDate(const std::string &date) {
    std::istringstream iss(date);
    int day, month, year;
    char sep1, sep2;
    if (!(iss >> day >> sep1 >> month >> sep2 >> year) || sep1 != '/' || sep2 != '/' || !iss.eof()) {
        throw std::invalid_argument("Invalid date format, expected DD/MM/YYYY");
    }
    return {year, month, day};
}

const Expenditure & Manager::getExpenditure(size_t index){
    return list[index];
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

void Manager::editExpenditure(size_t index, const std::string& newName, double newAmount, const std::string& newType, const std::string& newDate){
    if (index >= list.size()) {
        throw std::invalid_argument("Invalid index: out of range.");
    }
    Expenditure original = list[index];
    try {
        list[index].setName(newName);
        list[index].setAmount(newAmount);
        list[index].setType(newType);
        list[index].setDate(newDate);
    } catch (const std::invalid_argument& e) {
        list[index] = original;
        throw;
    }
}

void Manager::updateAmount(size_t index, double newAmount){
    if (index >= list.size()) throw std::invalid_argument("Invalid index: out of range.");
    list[index].setAmount(newAmount); 
}
void Manager::updateName(size_t index, const std::string& newName){
    if (index >= list.size()) throw std::invalid_argument("Invalid index: out of range.");
    list[index].setName(newName); 
}
void Manager::updateType(size_t index, const std::string& newType){
    if (index >= list.size()) throw std::invalid_argument("Invalid index: out of range.");
    list[index].setType(newType); 
}
void Manager::updateDate(size_t index, const std::string& newDate){
    if (index >= list.size()) throw std::invalid_argument("Invalid index: out of range.");
    list[index].setDate(newDate); 
}

double Manager::getTotalAmount() const {
    double total = 0;
    for (const auto& e : list) {
        total += e.getAmount();
    }
    return total;
}

double Manager::getTotalByDate(const std::string &start, const std::string &end) const{
    double total = 0;
    auto startDate = parseDate(start);
    auto endDate = parseDate(end);
    if(startDate > endDate){
        throw std::invalid_argument("Invalid range: Start date must be before end date");
    }
    for (const auto& e : list) {
        auto current = parseDate(e.getDate());
        if(current >= startDate && current <= endDate){
            total += e.getAmount();
        }
    }
    return total;
}

double Manager::getTotalByType(const std::string &type) const{
    double total = 0;
    for (const auto& e : list) {
        if(type == e.getType()){
            total += e.getAmount();
        }
    }
    return total;
}

// double Manager::getTotalByMonth(int month) const{}
// double Manager::getTotalByYear(int year) const{}

void Manager::showAll(){
    if (list.empty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }
    sortExpenditures("date", true);
    for(size_t i = 0; i < list.size(); i++){
        std::cout << i + 1 << ". ";
        list[i].show();
    }
    std::cout << std::endl;
}

void Manager::filterByType(const std::string &type){
    sortExpenditures("type", true);
    for(size_t i = 0; i < list.size(); i++){
        if(list[i].getType() == type){
            std::cout << i + 1 << ". ";
            list[i].show();
        }
    }
}

void Manager::filterByDateRange(const std::string &start, const std::string &end){
    auto startDate = parseDate(start);
    auto endDate = parseDate(end);
    if (startDate > endDate) {
        throw std::invalid_argument("Invalid range: Start date must be before end date");
    }
    sortExpenditures("date", true);
    for(size_t i = 0; i < list.size(); i++){
        auto current = parseDate(list[i].getDate());
        if(current >= startDate && current <= endDate){
            std::cout << i + 1 << ". ";
            list[i].show();
        }
    }
}

void Manager::filterByAmount(double min, double max){
    if(min > max){
        throw(std::invalid_argument("Invalid range: Minimum amount must be less than maximum amount."));
    }
    sortExpenditures("amount", true);
    for(size_t i = 0; i < list.size(); i++){
        if(list[i].getAmount() >= min && list[i].getAmount() <= max){
            std::cout << i + 1 << ". ";
            list[i].show();
        }
    }
}

void Manager::sortExpenditures(const std::string& sortBy, bool ascending){
    auto comparator = [&](const Expenditure& a, const Expenditure& b){
        if (sortBy == "date") {
            auto dateA = parseDate(a.getDate());
            auto dateB = parseDate(b.getDate());
            return ascending ? (dateA < dateB) : (dateA > dateB);
        } else if (sortBy == "amount") {
            return ascending ? (a.getAmount() < b.getAmount()) : (a.getAmount() > b.getAmount());
        } else if (sortBy == "type") {
            return ascending ? (a.getType() < b.getType()) : (a.getType() > b.getType());
        }
        return false; // Default: no sort if invalid sortBy
    };
    std::sort(list.begin(), list.end(), comparator);
}