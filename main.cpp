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
void filterDate(Manager &M);
void filterAmount(Manager &M);
void filterType(Manager &M);
void getTotal(Manager &M);
void getTotalDateRange(Manager &M);
void getTotalType(Manager &M);
void getTotalMonth(Manager &M);
void getTotalYear(Manager &M);


int main(){
    menu();
}

void menu(){
    Manager M;
    M.loadFromFile("data.csv");
    // Expenditure a("Botines Adidas", 120.56, "Deporte", "29/3/2026");
    // Expenditure b("Agua", 3.02, "Comida", "04/04/2025");
    // Expenditure c("Hamburguesa", 10.04, "Comida");
    // M.addExpenditure(a);
    // M.addExpenditure(b);
    // M.addExpenditure(c);
    size_t option, suboption;
    do{
        std::cout << "\n========== FINANCE MANAGER ==========" << std::endl;
        std::cout << "1. Expenditure management" << std::endl;
        std::cout << "2. Sort expenditures" << std::endl;
        std::cout << "3. Get amounts" << std::endl;
        std::cout << "4. Filter expenditures" << std::endl;
        std::cout << "5. Show all expenditures" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Your selection: ";
        option = getOpt(option);
        if(option == 0) {
            std::cout << "Saving data..." << std::endl;
            M.saveToFile("data.csv");
            std::cout << "Data saved successfully. Exiting." << std::endl;
            break;
        }
            
        switch(option){
            case 1:{
                std::cout << "\n\t--- Management ---" << std::endl;
                std::cout << "\n\t1. Add expenditure" << std::endl;
                std::cout << "\t2. Edit expenditure" << std::endl;
                std::cout << "\t3. Remove expenditure" << std::endl;
                std::cout << "\n\t0. Back" << std::endl;
                std::cout << "\nYour selection: ";
                suboption = getOpt(suboption);
                if(suboption == 0) break;
                else if (suboption == 1) handleAdd(M);
                else if (suboption == 2) handleEdit(M);
                else if (suboption == 3) handleRemove(M);
                }
                break;
            case 2:{
                std::cout << "\n\t--- Sorting ---" << std::endl;
                std::cout << "\t1. Sort by date" << std::endl;
                std::cout << "\t2. Sort by amount" << std::endl;
                std::cout << "\t3. Sort by type (alphabetical)" << std::endl;
                std::cout << "\n\t0. Back" << std::endl;
                std::cout << "\nYour selection: ";
                suboption = getOpt(suboption);
                if(suboption == 0) break;
                else if (suboption == 1) sortDate(M);
                else if (suboption == 2) sortAmount(M);
                else if (suboption == 3) sortType(M);
                break;    
            }
            case 3:{
                std::cout << "\n\t--- Totals ---" << std::endl;
                std::cout << "\t1. Get total expenditure" << std::endl;
                std::cout << "\t2. Get total in a date range" << std::endl;
                std::cout << "\t3. Get total by type" << std::endl;
                std::cout << "\t4. Get total in a month" << std::endl;
                std::cout << "\t5. Get total in a year" << std::endl;
                std::cout << "\n\t0. Back" << std::endl;
                std::cout << "\nYour selection: ";
                suboption = getOpt(suboption);
                if(suboption == 0) break;
                else if (suboption == 1) getTotal(M);
                else if (suboption == 2) getTotalDateRange(M);
                else if (suboption == 3) getTotalType(M);
                else if (suboption == 4) getTotalMonth(M);
                else if (suboption == 5) getTotalYear(M);
                break;
            }
            case 4:{
                std::cout << "\n\t--- Filters ---" << std::endl;
                std::cout << "\t1. Filter by date" << std::endl;
                std::cout << "\t2. Filter by amount" << std::endl;
                std::cout << "\t3. Filter by type" << std::endl;
                std::cout << "\n\t0. Back" << std::endl;
                std::cout << "\nYour selection: ";
                suboption = getOpt(suboption);
                if(suboption == 0) break;
                else if (suboption == 1) filterDate(M);
                else if (suboption == 2) filterAmount(M);
                else if (suboption == 3) filterType(M);
                break;
            }
            case 5:{
                std::cout << std::endl;
                M.showAll();
                break;
            }
        }
    }while(option != 0);
}

void handleAdd(Manager &M){
    std::string name, type, date;
    double amount;
    std::cout << "Name: ";
    std::getline(std::cin >> std::ws, name);
    std::cout << "Amount: ";
    while (!(std::cin >> amount)) {
        std::cout << "Invalid input. Please enter a valid number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Type: ";
    std::getline(std::cin, type);
    std::cout << "Date (DD/MM/YYYY) [Enter for today's date]: ";
    std::getline(std::cin, date);
    try {
        if (date.empty()) {
            Expenditure e(name, amount, type); 
            M.addExpenditure(e);
            std::cout << "Added: ";
            e.show();
        } else {
            Expenditure e(name, amount, type, date);
            M.addExpenditure(e);
            std::cout << "Added: ";
            e.show();
        }
    } catch (const std::exception& err) {
        std::cout << err.what() << std::endl;
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
    std::cout << std::endl;
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
    std::cout << std::endl;
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
    std::cout << std::endl;
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

void filterDate(Manager &M){
    std::string start, end;
    std::cout << "Enter start date (DD/MM/YYYY): ";
    std::getline(std::cin, start);
    std::cout << "Enter end date (DD/MM/YYYY): ";
    std::getline(std::cin, end);
    try {
        std::cout << "\n===Expenditures from " << start << " to " << end << "===\n";
        M.filterByDateRange(start, end);
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void filterAmount(Manager &M) {
    double min, max;
    std::cout << "Enter minimum amount: ";
    if (!(std::cin >> min)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input." << std::endl;
        return;
    }
    std::cout << "Enter maximum amount: ";
    if (!(std::cin >> max)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input." << std::endl;
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    try {
        std::cout << "\n===Expenditures between $" << min << " and $" << max << "===\n";
        M.filterByAmount(min, max);
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void filterType(Manager &M) {
    std::string type;
    std::cout << "Enter type to filter by: ";
    std::getline(std::cin, type);
    std::cout << "\n===Expenditures of type: " << type << "===\n";
    M.filterByType(type);
}

void getTotal(Manager &M){
    std::cout << "\n===Total amount spent: $" << M.getTotalAmount() << "===\n";
}

void getTotalDateRange(Manager &M){
    std::string start, end;
    std::cout << "Enter start date (DD/MM/YYYY): ";
    std::getline(std::cin, start);
    std::cout << "Enter end date (DD/MM/YYYY): ";
    std::getline(std::cin, end);
    try {
        std::cout << "\n===Total amount spent from " << start << " to " << end << ": $" << M.getTotalByDate(start, end) << "===\n";
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void getTotalType(Manager &M){
    std::string type;
    std::cout << "Enter type: ";
    std::getline(std::cin, type);
    std::cout << "\n===Total amount spent of type " << type << ": $" << M.getTotalByType(type) << "===\n";
}

void getTotalMonth(Manager &M) {
    int month, year;
    std::cout << "Enter month (1-12): ";
    if (!(std::cin >> month)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number." << std::endl;
        return;
    }
    std::cout << "Enter year (YYYY): ";
    if (!(std::cin >> year)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number." << std::endl;
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    try {
        std::cout << "\n=== Total amount spent in " << month << "/" << year << ": $" << M.getTotalByMonth(month, year) << " ===\n";
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void getTotalYear(Manager &M) {
    int year;
    std::cout << "Enter year (YYYY): ";
    if (!(std::cin >> year)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number." << std::endl;
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar para futuros getlines

    try {
        std::cout << "\n=== Total amount spent in " << year << ": $" <<  M.getTotalByYear(year) << " ===\n";
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}