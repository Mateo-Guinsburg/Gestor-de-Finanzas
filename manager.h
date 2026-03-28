#ifndef MANAGER_H
#define MANAGER_H

#include <vector>
#include <memory>
#include "expenditure.h"

class Manager {
private:
    std::vector<Expenditure> list;
public:
    const Expenditure &getExpenditure(size_t index);
    void addExpenditure(const Expenditure &e);
    void removeExpenditure(size_t index);
    void editExpenditure(size_t index, const std::string& newName, double newAmount, const std::string& newType, const std::string& newDate);
    void updateAmount(size_t index, double newAmount);
    void updateName(size_t index, const std::string& newName);
    void updateType(size_t index, const std::string& newType);
    void updateDate(size_t index, const std::string& newDate);
    void sortExpenditures(const std::string& sortBy, bool ascending);    
    void showAll();
    double getTotalAmount() const;
    double getTotalByDate(const std::string &start, const std::string &end) const;
    double getTotalByType(const std::string &type) const;
    double getTotalByMonth(int month) const;
    double getTotalByYear(int year) const;
    void filterByType(const std::string &type);
    void filterByDateRange(const std::string &start, const std::string &end);
    void filterByAmount(double min, double max);
};

#endif