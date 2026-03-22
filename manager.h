#include <vector>
#include <memory>
#include "expenditure.h"

class Manager {
private:
    std::vector<Expenditure> list;
public:
    void addExpenditure(const Expenditure &e);
    void removeExpenditure(size_t index);
    void showAll() const;
    double getTotalAmount() const;
    void filterByType(const std::string &type);
    void filterByDateRange(const std::string &start, const std::string &end);
};