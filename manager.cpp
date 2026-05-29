#include "manager.h"
#include <stdexcept>
#include <sstream>
#include <tuple>
#include <algorithm>
#include <fstream>
#include <iomanip>

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
    if(index >= list.size()){
        throw(std::invalid_argument("Invalid index: out of range."));
    }
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

double Manager::getTotalByMonth(int month, int year) const {
    if (month < 1 || month > 12) {
        throw std::invalid_argument("Invalid month: must be between 1 and 12.");
    }
    if (year < 0) {
        throw std::invalid_argument("Invalid year: cannot be negative.");
    }
    double total = 0;
    for (const auto& e : list) {
        auto [y, m, d] = parseDate(e.getDate()); 
        if (m == month && y == year) {
            total += e.getAmount();
        }
    }
    return total;
}

double Manager::getTotalByYear(int year) const {
    if (year < 0) {
        throw std::invalid_argument("Invalid year: cannot be negative.");
    }
    double total = 0;
    for (const auto& e : list) {
        auto [y, m, d] = parseDate(e.getDate());
        if (y == year) {
            total += e.getAmount();
        }
    }
    return total;
}

void Manager::showAll(){
    if (list.empty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }
    // Print header
    std::cout << std::left << std::setw(3) << "#" 
              << std::setw(20) << "Name" 
              << std::setw(8) << "Amount" 
              << std::setw(20) << "Type" 
              << std::setw(12) << "Date" << std::endl;
    std::cout << std::string(60, '-') << std::endl;  // Separator line
    
    for(size_t i = 0; i < list.size(); i++){
        std::cout << std::left << std::setw(3) << (i + 1);
        list[i].show();
    }
    std::cout << std::endl;
}

void Manager::filterByType(const std::string &type){
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

void Manager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file to save data." << std::endl;
        return;
    }
    for (size_t i = 0; i < list.size(); i++) {
        file << list[i].getName() << "," 
             << list[i].getAmount() << "," 
             << list[i].getType() << "," 
             << list[i].getDate() << "\n";
    }
    file.close();
}

void Manager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return; 
    }
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name, type, date, sAmount;
        
        if (std::getline(iss, name, ',') &&
            std::getline(iss, sAmount, ',') &&
            std::getline(iss, type, ',') &&
            std::getline(iss, date)) {
            
            try {
                double amount = std::stod(sAmount);
                Expenditure e(name, amount, type, date);
                list.push_back(e); 
            } catch (...) {
                std::cout << "Warning: Skipped a corrupted line in the data file." << std::endl;
            }
        }
    }
    file.close();
}

MonthlyStats Manager::getMonthlyStats(int month, int year) const {
    MonthlyStats stats = {0.0, 0.0, 0.0, 0.0, ""};

    for (size_t i = 0; i < list.size(); i++) {
        auto date = parseDate(list[i].getDate());
        if (std::get<1>(date) == month && std::get<0>(date) == year) {
            stats.totalSpent += list[i].getAmount();
            if (list[i].getAmount() > stats.maxExpense) {
                stats.maxExpense = list[i].getAmount();
                stats.maxExpenseName = list[i].getName();
            }
        }
    }

    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int max_days = days_in_month[month - 1];
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)) {
            max_days = 29;
    }
    stats.dailyAverage = stats.totalSpent / max_days;
    stats.weeklyAverage = stats.totalSpent / 4.33; 
    return stats;
}