# 💰 Personal Finance Manager

A robust, console-based Personal Finance Manager built in C++. This application allows users to track their daily expenditures, analyze spending habits, and persist data seamlessly using CSV files. 

Developed with a strong focus on clean architecture, memory safety, and object-oriented programming (OOP) principles.

## ✨ Features

- **CRUD Operations:** Easily Add, View, Edit, and Remove expenditures with strict input validation.
- **Data Persistence:** Automatically loads and saves data to `data.csv`, ensuring no information is lost between sessions.
- **Advanced Sorting & Filtering:** - Sort records by Date, Amount, or Type (Ascending/Descending) using custom C++ lambdas.
  - Filter expenditures by specific date ranges, amount thresholds, or categories.
- **Financial Insights:** Calculate total spending, or break it down by specific months and years.
- **Robust Error Handling:** Implements safe `std::cin` buffer clearing and `try-catch` blocks to prevent crashes (Segmentation Faults) or infinite loops from invalid user inputs.

## 📂 Project Structure

- `main.cpp`: Handles the user interface with a mennu, input parsing, and buffer cleaning.
- `manager.h / .cpp`: Core business logic, vector management, sorting algorithms, and CSV file I/O operations.
- `expenditure.h / .cpp`: The data model representing a single transaction, including strict format validation (e.g., leap year date formats, positive amounts).
- `makefile`: Automated build script for easy compilation.

## 🚀 How to Run

### Prerequisites
- A C++ compiler (e.g., `g++`)
- `make` utility

### Compilation & Execution
1. Clone the repository and navigate to the project folder in your terminal.
2. Build the project using the makefile:
    ```bash
    make
3. Run the compiled executable:
    ```bash
    ./exp

🗺️ Roadmap (Future Improvements)

    [ ] Enhanced UI Formatting: Implement advanced tabular formatting (using std::setw and std::left from <iomanip>) to display expenditures in a perfectly aligned, clean console grid.

    [ ] Statistical Analysis: Add analytical modules to calculate weekly and monthly spending averages, providing users with deeper insights into their financial trends.

Developed as a first-year Computer Engineering project in Nebrija University (Madrid, Spain), trying to demonstrate proficiency in C++ data structures, exception handling, and file streams.