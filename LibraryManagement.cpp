#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>
#include <limits>

using namespace std;

// ======== BOOK CLASS ========
class Book {
public:
    int id;
    string title;
    string author;
    int quantity;

    void input() {
        while (true) {
            cout << "Enter Book ID: "; cin >> id;
            if(cin.fail() || id <= 0){ cin.clear(); cin.ignore(1000,'\n'); cout<<"Invalid ID. Try again.\n"; continue; }
            break;
        }
        cin.ignore(1000,'\n');
        cout << "Enter Title: "; getline(cin, title);
        cout << "Enter Author: "; getline(cin, author);
        while (true) {
            cout << "Enter Quantity: "; cin >> quantity;
            if(cin.fail() || quantity < 0){ cin.clear(); cin.ignore(1000,'\n'); cout<<"Invalid quantity. Try again.\n"; continue; }
            break;
        }
        cin.ignore(1000,'\n');
    }

    void display() {
        cout << "ID: " << id << " | Title: " << title << " | Author: " << author
             << " | Quantity: " << quantity << endl;
    }
};

// ======== MEMBER CLASS ========
class Member {
public:
    int id;
    string name;

    void input() {
        while (true) {
            cout << "Enter Member ID: "; cin >> id;
            if(cin.fail() || id <=0){ cin.clear(); cin.ignore(1000,'\n'); cout<<"Invalid ID. Try again.\n"; continue; }
            break;
        }
        cin.ignore(1000,'\n');
        cout << "Enter Member Name: "; getline(cin, name);
    }

    void display() {
        cout << "ID: " << id << " | Name: " << name << endl;
    }
};

// ======== TRANSACTION CLASS ========
class Transaction {
public:
    int bookID;
    int memberID;
    string action; // "Issued" or "Returned"
    string date;

    Transaction(int bID, int mID, string act) {
        bookID = bID;
        memberID = mID;
        action = act;

        // get current date
        time_t now = time(0);
        tm *ltm = localtime(&now);
        stringstream ss;
        ss << 1900 + ltm->tm_year << "-" 
           << 1 + ltm->tm_mon << "-" 
           << ltm->tm_mday;
        date = ss.str();
    }

    string toCSV() {
        return to_string(bookID) + ";" + to_string(memberID) + ";" + action + ";" + date;
    }
};

// ======== FILE HANDLING ========
vector<Book> loadBooks() {
    vector<Book> books;
    ifstream file("books.csv");
    string line;
    while(getline(file,line)) {
        if(line.empty()) continue;
        Book b;
        stringstream ss(line);
        string temp;
        getline(ss,temp,';'); b.id = stoi(temp);
        getline(ss,b.title,';');
        getline(ss,b.author,';');
        getline(ss,temp,';'); b.quantity = stoi(temp);
        books.push_back(b);
    }
    file.close();
    return books;
}

void saveBooks(vector<Book> &books) {
    ofstream file("books.csv");
    for(auto b: books)
        file << b.id << ";" << b.title << ";" << b.author << ";" << b.quantity << endl;
}

vector<Member> loadMembers() {
    vector<Member> members;
    ifstream file("members.csv");
    string line;
    while(getline(file,line)) {
        if(line.empty()) continue;
        Member m;
        stringstream ss(line);
        string temp;
        getline(ss,temp,';'); m.id = stoi(temp);
        getline(ss,m.name,';');
        members.push_back(m);
    }
    file.close();
    return members;
}

void saveMembers(vector<Member> &members) {
    ofstream file("members.csv");
    for(auto m: members)
        file << m.id << ";" << m.name << endl;
}

void logTransaction(Transaction t) {
    ofstream file("transactions.csv", ios::app);
    file << t.toCSV() << endl;
    file.close();
}

// ======== FUNCTIONALITIES ========

// Book Management
void addBook() {
    vector<Book> books = loadBooks();
    Book b;
    b.input();
    // Check duplicate ID
    for(auto bk: books){ if(bk.id == b.id){ cout<<"Book ID already exists.\n"; return; } }
    books.push_back(b);
    saveBooks(books);
    cout<<"Book added successfully!\n";
}

void displayBooks() {
    vector<Book> books = loadBooks();
    cout<<"\n===== BOOK LIST =====\n";
    for(auto b: books) b.display();
}

void searchBook() {
    vector<Book> books = loadBooks();
    int id;
    cout<<"Enter Book ID to search: "; cin >> id;
    for(auto b: books){ if(b.id == id){ b.display(); return; } }
    cout<<"Book not found.\n";
}

// Member Management
void addMember() {
    vector<Member> members = loadMembers();
    Member m;
    m.input();
    for(auto mem: members){ if(mem.id==m.id){ cout<<"Member ID already exists.\n"; return; } }
    members.push_back(m);
    saveMembers(members);
    cout<<"Member added successfully!\n";
}

void displayMembers() {
    vector<Member> members = loadMembers();
    cout<<"\n===== MEMBER LIST =====\n";
    for(auto m: members) m.display();
}

void searchMember() {
    vector<Member> members = loadMembers();
    int id; cout<<"Enter Member ID to search: "; cin >> id;
    for(auto m: members){ if(m.id==id){ m.display(); return; } }
    cout<<"Member not found.\n";
}

// Issue / Return with Fine System
void issueBook() {
    vector<Book> books = loadBooks();
    vector<Member> members = loadMembers();
    int bookID, memberID;
    cout<<"Enter Member ID: "; cin >> memberID;
    bool memberFound = false;
    for(auto m: members) if(m.id==memberID) memberFound=true;
    if(!memberFound){ cout<<"Member not found.\n"; return; }

    cout<<"Enter Book ID to issue: "; cin >> bookID;
    for(auto &b: books){
        if(b.id==bookID){
            if(b.quantity>0){
                b.quantity--;
                saveBooks(books);
                logTransaction(Transaction(bookID,memberID,"Issued"));
                cout<<"Book issued successfully! Due in 7 days.\n";
                return;
            } else { cout<<"Book not available.\n"; return; }
        }
    }
    cout<<"Book not found.\n";
}

void returnBook() {
    vector<Book> books = loadBooks();
    int bookID, memberID;
    cout<<"Enter Member ID: "; cin >> memberID;
    cout<<"Enter Book ID to return: "; cin >> bookID;

    for(auto &b: books){
        if(b.id==bookID){
            b.quantity++;
            saveBooks(books);
            logTransaction(Transaction(bookID,memberID,"Returned"));
            cout<<"Book returned successfully!\n";
            // Fine calculation placeholder: In real case, calculate days and fine
            cout<<"(Fine system placeholder: 0 if returned on time)\n";
            return;
        }
    }
    cout<<"Book not found.\n";
}

// Display Transaction History
void displayTransactions() {
    ifstream file("transactions.csv");
    string line;
    cout<<"\n===== TRANSACTION HISTORY =====\n";
    while(getline(file,line)){
        if(line.empty()) continue;
        stringstream ss(line);
        string bookID, memberID, action, date;
        getline(ss,bookID,';'); getline(ss,memberID,';'); getline(ss,action,';'); getline(ss,date,';');
        cout<<"BookID: "<<bookID<<" | MemberID: "<<memberID<<" | Action: "<<action<<" | Date: "<<date<<endl;
    }
    file.close();
}

// ======== MAIN MENU ========
int main(){
    int choice;
    do{
        cout<<"\n===== LIBRARY MANAGEMENT SYSTEM =====\n";
        cout<<"1. Add Book\n2. Display Books\n3. Search Book\n";
        cout<<"4. Add Member\n5. Display Members\n6. Search Member\n";
        cout<<"7. Issue Book\n8. Return Book\n9. Transaction History\n10. Exit\n";
        cout<<"Enter your choice: "; cin>>choice;
        switch(choice){
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: addMember(); break;
            case 5: displayMembers(); break;
            case 6: searchMember(); break;
            case 7: issueBook(); break;
            case 8: returnBook(); break;
            case 9: displayTransactions(); break;
            case 10: cout<<"Exiting...\n"; break;
            default: cout<<"Invalid choice!\n";
        }
    } while(choice!=10);
    return 0;
}
