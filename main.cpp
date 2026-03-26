#include "expenditure.h"
#include "manager.h"
#include <iostream>
#include <iomanip>
#include <limits>

void menu();

int main(){
    menu();
}

void menu(){
    Expenditure a("Botines Adidas", 120.56, "Deporte", "29/3/2026");
    // std::cout << a.getDate() << std::endl;
    // a.show();

    Manager M;
    // std::cout << "To add an expenditure, input 'name', 'amount', 'type' separated by a space." << std::endl;
    // std::string name, type;
    // double amount;
    // std::cin >> name >> amount >> type;
    Expenditure b("Agua", 3.02, "Comida", "04/04/2025");
    M.addExpenditure(a);
    M.addExpenditure(b);
    Expenditure c("Hamburguesa", 10.04, "Comida");
    // M.showAll();
    M.addExpenditure(c);
    // M.filterByAmount(1, 20);
    // std::cout << std::endl;
    // M.filterByDateRange("20/03/2026", "30/03/2026");
    // std::cout << std::endl;
    // M.showAll();
    // double mount;
    // std::ostringstream oss;
    // mount = M.getTotalByDate("20/03/2026", "30/03/2026");
    // oss << std::fixed << std::setprecision(2) << mount;
    // std::cout << "Total for 20/03/2026 to 30/03/2026 is $" << oss.str() << std::endl;
    size_t option, suboption, index;
    std::string name, type, date;
    double amount;
    std::cout << "1) Expenditure management" << std::endl;
    std::cout << "2) Sort expenditures" << std::endl;
    std::cout << "3) Get total amount" << std::endl;
    std::cout << "4) Filter expenditures" << std::endl;
    std::cout << "Your selection: ";
    std::cin >> option;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    switch(option){
        case 1:{
            std::cout << "\n\tPress '1' to Add expenditure" << std::endl;
            std::cout << "\tPress '2' to Edit expenditure" << std::endl;
            std::cout << "\tPress '3' to Remove expenditure" << std::endl;
            std::cout << "\n\tPress 'Esc' to go back" << std::endl;
            std::cout << "\nYour selection: ";
            std::cin >> suboption;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            switch(suboption){
                case 1:{
                    Expenditure e;
                    std::cout << "To add an expenditure, input 'name', 'amount', 'type' separated by a space. If date not needed press 'enter' after the data. " << std::endl;
                    std::cin >> name >> amount >> type;
                    e.setAmount(amount);
                    e.setName(name);
                    e.setType(type);
                    // if(date != ""){
                    //     e.setDate(date);
                    // }
                    M.addExpenditure(e);
                    std::cout << "Added: ";
                    e.show();
                    break;
                }
                case 2:{
                    std::cout << "Insert the index of the expenditure requested to edit: ";
                    std::cin >> index;
                    std::cout << "Now input the new 'name', 'amount', 'type', 'date'. " << std::endl;
                    std::cin >> name >> amount >> type >> date;
                    std::cout << " OLD: " << index << ". "; 
                    M.getExpenditure(index).show();
                    M.editExpenditure(index, name, amount, type, date);
                    std::cout << " NEW: " << index << ". "; 
                    M.getExpenditure(index).show();
                    break;
                }
                case 3:{
                    std::cout << "Insert the index of the expenditure requested to remove: ";
                    std::cin >> index;
                    index = index - 1;
                    std::cout << "Removed: ";
                    M.getExpenditure(index).show();
                    M.removeExpenditure(index);
                    break;
                }
            }
            break;
        }
        case 2:{
            std::cout << "\tPress '1' to sort by date" << std::endl;
            std::cout << "\tPress '2' to sort by amount" << std::endl;
            std::cout << "\tPress '3' to sort by type" << std::endl;
            std::cout << "\n\tPress 'Esc' to go back" << std::endl;
            break;
        }
        case 3:{
            std::cout << "\t1) Get total expenditure" << std::endl;
            std::cout << "\t2) Get total in a date range" << std::endl;
            std::cout << "\t3) Get total by type" << std::endl;
            std::cout << "\t4) Get total in a month" << std::endl;
            std::cout << "\t5) Get total in a year" << std::endl;
            std::cout << "Press 'Esc' to go back" << std::endl;
            break;
        }
        case 4:{
            std::cout << "\t1) Filter by date" << std::endl;
            std::cout << "\t2) Filter by type" << std::endl;
            std::cout << "\t3) Filter by amount" << std::endl;
            std::cout << "Press 'Esc' to go back" << std::endl;
            break;
        }
    }
}