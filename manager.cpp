#include "manager.h"

void Manager::addExpenditure(Expenditure e) {
    list.push_back(e);
}

double Manager::getTotal() const {
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