# Personal Finance Manager in C++

This is a console project I built during my first year of Computer Engineering at Nebrija University. The idea was to create a daily expense tracker to practice core C++ concepts like Object-Oriented Programming (OOP), memory management, and file reading/writing (I/O).

## Features

- **Full Management:** You can add, view, edit, and delete expenditures. Everything has strict validation.
- **No lost data:** Everything you input saves automatically to a `data.csv` file. When you open the program again, it loads your entire history.
- **Filters & Sorting:** You can sort expenses by date, amount, or type. You can also filter to see only a specific date range or a particular type of expense.
- **Crash-proof:** It features `try-catch` blocks and keyboard buffer clearing. If the program asks for a number and you type a letter, it won't crash or go into an infinite loop; it warns you and lets you try again.
- **Statistics:** It calculates how much you spent in total, shows daily/weekly averages, and tells you what your most expensive purchase of the month was.

## Main Files

- `main.cpp`: Handles the interactive menus and user input.
- `manager.h / .cpp`: It handles the expenditure vector, sorting/searching algorithms, and the `.csv` file processing.
- `expenditure.h / .cpp`: The class representing a single expense. It self-validates its own data before allowing an object to be created.
- `makefile`: To compile everything quickly without typing long commands.

## How to test it

If you have a C++ compiler (like `g++`) and `make` installed, just open your terminal in the project folder and run:

```bash
make
./exp

## Recent Updates

[x] Table formatting: Used std::setw so the console displays expenses neatly aligned in columns.

[x] Statistical Analysis: Added daily/weekly averages and key monthly metrics.