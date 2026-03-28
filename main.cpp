#include "expenditure.h"
#include "manager.h"
#include <iostream>
#include <iomanip>
#include <limits>

void menu();
void handleAdd(Manager &M);
void handleRemove(Manager &M);
void handleEdit(Manager &M);
void sortDate(Manager &M);
void sortAmount(Manager &M);
void sortType(Manager &M);
size_t getOpt(size_t option);

int main(){
    menu();
}

void menu(){
    Expenditure a("Botines Adidas", 120.56, "Deporte", "29/3/2026");
    Manager M;
    Expenditure b("Agua", 3.02, "Comida", "04/04/2025");
    M.addExpenditure(a);
    M.addExpenditure(b);
    Expenditure c("Hamburguesa", 10.04, "Comida");
    M.addExpenditure(c);
    size_t option, suboption, userIndex, internalIndex;
    std::string name, type, date;
    double amount;
    std::cout << "1. Expenditure management" << std::endl;
    std::cout << "2. Sort expenditures" << std::endl;
    std::cout << "3. Get amounts" << std::endl;
    std::cout << "4. Filter expenditures" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Your selection: ";
    option = getOpt(option);
    if(option == 0) return;
    switch(option){
        case 1:{
            std::cout << "\n\t1. Add expenditure" << std::endl;
            std::cout << "\t2. Edit expenditure" << std::endl;
            std::cout << "\t3. Remove expenditure" << std::endl;
            std::cout << "\n\t0. Back" << std::endl;
            std::cout << "\nYour selection: ";
            suboption = getOpt(suboption);
            if(suboption == 0) return;
            else if (suboption == 1) handleAdd(M);
            else if (suboption == 2) handleEdit(M);
            else if (suboption == 3) handleRemove(M);
            }
            break;
        case 2:{
            std::cout << "\t1. Sort by date" << std::endl;
            std::cout << "\t2. Sort by amount" << std::endl;
            std::cout << "\t3. Sort by type (alphabetical)" << std::endl;
            std::cout << "\n\t0. Back" << std::endl;
            std::cout << "\nYour selection: ";
            suboption = getOpt(suboption);
            if(suboption == 0) return;
            else if (suboption == 1) sortDate(M);
            else if (suboption == 2) sortAmount(M);
            else if (suboption == 3) sortType(M);
            break;    
        }
        case 3:{
            std::cout << "\t1. Get total expenditure" << std::endl;
            std::cout << "\t2. Get total in a date range" << std::endl;
            std::cout << "\t3. Get total by type" << std::endl;
            std::cout << "\t4. Get total in a month" << std::endl;
            std::cout << "\t5. Get total in a year" << std::endl;
            std::cout << "\n\t0. Back" << std::endl;
            std::cout << "\nYour selection: ";
            suboption = getOpt(suboption);
            if(suboption == 0){return;}
            break;
        }
        case 4:{
            std::cout << "\t1. Filter by date" << std::endl;
            std::cout << "\t2. Filter by type" << std::endl;
            std::cout << "\t3. Filter by amount" << std::endl;
            std::cout << "\n\t4. Back" << std::endl;
            break;
        }
    }
}


void handleAdd(Manager &M){
    std::string name, type, date, inputLine;
    double amount;
    std::cout << "To add an expenditure, input 'name', 'amount', 'type', 'date' separated by a space." << std::endl; 
    std::cout << "(If date is not needed, press 'Enter' after 'type')" << std::endl;
    std::cout << "New expenditure: ";
    std::getline(std::cin, inputLine);
    std::stringstream ss(inputLine);
    if (!(ss >> name >> amount >> type)) {
        std::cout << "Invalid name/amount/type format." << std::endl;
        return;
    }
    if (ss >> date) {
        try {
            Expenditure e(name, amount, type, date);
            M.addExpenditure(e);
            std::cout << "Added: ";
            e.show();
        } catch (const std::exception& err) {
            std::cout << err.what() << std::endl;
        }
    } else {
        try {
            Expenditure e(name, amount, type);
            M.addExpenditure(e);
            std::cout << "Added: ";
            e.show();
        } catch (const std::exception& err) {
            std::cout << err.what() << std::endl;
        }
    }
}

void handleRemove(Manager &M){
    M.showAll();
    size_t userIdx, internalIdx;
    std::cout << "Insert the index of the expenditure requested to remove (or '0' to go back): ";
    std::cin >> userIdx;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if(std::cin.fail()){
        std::cin.clear();
        return;
    }
    if(userIdx == 0){return;}
    internalIdx = userIdx - 1;
    try {
        Expenditure aux = M.getExpenditure(internalIdx);
        M.removeExpenditure(internalIdx);
        std::cout << "Removed: ";
        aux.show();
    } 
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void handleEdit(Manager &M){
    M.showAll();
    std::cout << "Insert the index of the expenditure requested to edit (or '0' to go back): ";
    size_t userIdx, internalIdx;
    if(!(std::cin >> userIdx)){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if(userIdx == 0){return;}
    internalIdx = userIdx - 1;
    try {
        Expenditure aux = M.getExpenditure(internalIdx);
        std::cout << "\tPress '1' to edit name" << std::endl;
        std::cout << "\tPress '2' to edit amount" << std::endl;
        std::cout << "\tPress '3' to edit type" << std::endl;
        std::cout << "\tPress '4' to edit date" << std::endl;
        std::cout << "\tPress '0' to go back" << std::endl;
        std::cout << "Your selection: ";
        int editOption;
        if(!(std::cin >> editOption)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return;
        }
        if(editOption == 0){return;}
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        bool updated = false;
        switch (editOption) {
            case 1: {
                std::string newName;
                std::cout << "\tNew name: ";
                std::getline(std::cin, newName);
                M.updateName(internalIdx, newName);
                updated = true;
                break;
            }
            case 2: {
                double newAmount;
                std::cout << "\tNew amount: ";
                if(std::cin >> newAmount){
                    M.updateAmount(internalIdx, newAmount);
                    updated = true;
                }
                else{
                    std::cout << "Invalid amount." << std::endl;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
            case 3: {
                std::string newType;
                std::cout << "\tNew type: ";
                std::getline(std::cin, newType);
                M.updateType(internalIdx, newType);
                updated = true;
                break;
            }
            case 4: {
                std::string newDate;
                std::cout << "\tNew date: ";
                std::getline(std::cin, newDate);
                M.updateDate(internalIdx, newDate);
                updated = true;
                break;
            }
            default:
                std::cout << "Invalid option selected." << std::endl;
                break;
        }
        if(updated){
            std::cout << " OLD: " << userIdx << ". ";
            aux.show();
            std::cout << " NEW: " << userIdx << ". ";    
            M.getExpenditure(internalIdx).show();
        }
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void sortDate(Manager &M){
    int input;
    std::cout << "Press '1' to sort by descending, other for ascending: ";
    if (!(std::cin >> input)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    
    bool ascending = (input != 1);
    M.sortExpenditures("date", ascending);
    M.showAll();
}

void sortAmount(Manager &M){
    int input;
    std::cout << "Press '1' to sort by descending, other for ascending: ";
    if (!(std::cin >> input)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    
    bool ascending = (input != 1);
    M.sortExpenditures("amount", ascending);
    M.showAll();
}

void sortType(Manager &M){
    int input;
    std::cout << "Press '1' to sort by descending, other for ascending: ";
    if (!(std::cin >> input)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    
    bool ascending = (input != 1);
    M.sortExpenditures("type", ascending);
    M.showAll();
}

size_t getOpt(size_t option){
    std::cin.clear();
    std::cin >> option;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return option;
}
