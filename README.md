Library Management System (C++)

This is a simple "Library Management System" I built in C++ to practice object-oriented programming and file handling. The project manages books, members, and transactions in a library. It’s completely console-based and uses CSV files for storage, so all data is persistent between runs.


Features:

- Add and search books by ID  
- Add and search members by ID  
- Issue and return books with transaction history  
- Store data in CSV files (auto-generated if missing)  
- Basic due date and fine system (placeholder, can be expanded)  
- Error handling for invalid input  


How to Run:
    
1. Clone the repository or download the source code.  
2. Compile the program:  
    bash
    g++ LibraryManagement.cpp -o LibraryManagement

3.Run the program:
    * On Windows: LibraryManagement.exe
    * On Linux/Mac: ./LibraryManagement


Project Files;

* LibraryManagement.cpp - main source code
* books.csv - stores book details
* members.csv - stores member details
* transactions.csv - stores issue/return records
* .gitignore - ignores generated files and binaries
	


What I Learned:

* How to use classes, vectors, and file streams in C++
* Validating user input and handling errors gracefully
* Working with persistent data storage using CSV
* Designing a small system that can be extended with new features


Possible Improvements:

* Real fine calculation based on return date
* More advanced search (by title, author, or member name)
* Reports: most borrowed books, active members, etc.
* Database integration (MySQL/SQLite) instead of CSV
* GUI version using Qt or another C++ framework


Author

Made by Priyanshu Sharma
* GitHub: https://github.com/Priyanshu7830


