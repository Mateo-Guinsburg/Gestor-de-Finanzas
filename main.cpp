#include "expenditure.h"
#include <iostream>

int main(){
    Expenditure a("Botines Adidas", 120, "Deporte", "20/3/2026");
    std::cout << a.getDate() << std::endl;
    a.show();
}
