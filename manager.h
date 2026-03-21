#include <vector>
#include <memory>
#include "expenditure.h"

class Manager {
private:
    std::vector<Expenditure> list;
public:
    void addExpenditure(Expenditure e);
    void showAll() const;
    double getTotal() const;
};