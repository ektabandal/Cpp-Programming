
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <sstream>
using namespace std;

class Book {
public:
    int bookId;
    string title;
    string author;
    bool issued;

    void display() const {
        cout << left << setw(10) << bookId
             << setw(30) << title
             << setw(25) << author
             << setw(12) << (issued ? "Issued" : "Available") << endl;
    }
};

class Member {
public:
    int memberId;
    string name;

    void display() const {
        cout << left << setw(10) << memberId
             << setw(30) << name << endl;
    }
};

vector<Book> books;
vector<Member> members;

void saveBooks() {
    ofstream file("books.txt");
    for (auto &b : books)
        file << b.bookId << "|" << b.title << "|" << b.author << "|" << b.issued << "\n";
}

void loadBooks() {
    books.clear();
    ifstream file("books.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string temp;
        Book b;

        getline(ss, temp, '|'); b.bookId = stoi(temp);
        getline(ss, b.title, '|');
        getline(ss, b.author, '|');
        getline(ss, temp); b.issued = stoi(temp);

        books.push_back(b);
    }
}

void saveMembers() {
    ofstream file("members.txt");
    for (auto &m : members)
        file << m.memberId << "|" << m.name << "\n";
}

void loadMembers() {
    members.clear();
    ifstream file("members.txt");
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string temp;
        Member m;

        getline(ss, temp, '|');
        m.memberId = stoi(temp);

        getline(ss, m.name);

        members.push_back(m);
    }
}

Book* findBook(int id) {
    for (auto &b : books)
        if (b.bookId == id) return &b;
    return nullptr;
}

Member* findMember(int id) {
    for (auto &m : members)
        if (m.memberId == id) return &m;
    return nullptr;
}

void addBook() {
    Book b;

    cout << "Book ID: ";
    cin >> b.bookId;
    cin.ignore();

    cout << "Title: ";
    getline(cin, b.title);

    cout << "Author: ";
    getline(cin, b.author);

    b.issued = false;

    books.push_back(b);
    saveBooks();

    cout << "Book Added Successfully!\n";
}

void displayBooks() {
    if (books.empty()) {
        cout << "No Books Available!\n";
        return;
    }

    cout << left << setw(10) << "ID"
         << setw(30) << "Title"
         << setw(25) << "Author"
         << setw(12) << "Status" << endl;

    for (auto &b : books)
        b.display();
}

void searchByTitle() {
    string title;
    cin.ignore();
    cout << "Enter Title: ";
    getline(cin, title);

    bool found = false;

    for (auto &b : books) {
        if (b.title.find(title) != string::npos) {
            b.display();
            found = true;
        }
    }

    if (!found)
        cout << "No Book Found!\n";
}

void searchByAuthor() {
    string author;
    cin.ignore();
    cout << "Enter Author: ";
    getline(cin, author);

    bool found = false;

    for (auto &b : books) {
        if (b.author.find(author) != string::npos) {
            b.display();
            found = true;
        }
    }

    if (!found)
        cout << "No Book Found!\n";
}

void addMember() {
    Member m;

    cout << "Member ID: ";
    cin >> m.memberId;
    cin.ignore();

    cout << "Member Name: ";
    getline(cin, m.name);

    members.push_back(m);
    saveMembers();

    cout << "Member Added Successfully!\n";
}

void displayMembers() {
    if (members.empty()) {
        cout << "No Members Found!\n";
        return;
    }

    cout << left << setw(10) << "ID"
         << setw(30) << "Name" << endl;

    for (auto &m : members)
        m.display();
}

void issueBook() {
    int bookId, memberId;

    cout << "Book ID: ";
    cin >> bookId;

    cout << "Member ID: ";
    cin >> memberId;

    Book *b = findBook(bookId);
    Member *m = findMember(memberId);

    if (!b) {
        cout << "Book Not Found!\n";
        return;
    }

    if (!m) {
        cout << "Member Not Found!\n";
        return;
    }

    if (b->issued) {
        cout << "Book Already Issued!\n";
        return;
    }

    b->issued = true;
    saveBooks();

    cout << "Book Issued Successfully!\n";
}

void returnBook() {
    int bookId;

    cout << "Book ID: ";
    cin >> bookId;

    Book *b = findBook(bookId);

    if (!b) {
        cout << "Book Not Found!\n";
        return;
    }

    if (!b->issued) {
        cout << "Book Already Available!\n";
        return;
    }

    b->issued = false;
    saveBooks();

    cout << "Book Returned Successfully!\n";
}

void deleteBook() {
    int id;

    cout << "Book ID: ";
    cin >> id;

    for (auto it = books.begin(); it != books.end(); ++it) {
        if (it->bookId == id) {
            books.erase(it);
            saveBooks();
            cout << "Book Deleted Successfully!\n";
            return;
        }
    }

    cout << "Book Not Found!\n";
}

bool login() {
    string user, pass;

    cout << "\n===== ADMIN LOGIN =====\n";
    cout << "Username: ";
    cin >> user;

    cout << "Password: ";
    cin >> pass;

    return user == "ektabandal" && pass == "2366";
}

int main() {
    loadBooks();
    loadMembers();

    if (!login()) {
        cout << "Invalid Login!\n";
        return 0;
    }

    int choice;

    do {
        cout << "\n\n===== LIBRARY MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Search Book By Title\n";
        cout << "4. Search Book By Author\n";
        cout << "5. Add Member\n";
        cout << "6. Display Members\n";
        cout << "7. Issue Book\n";
        cout << "8. Return Book\n";
        cout << "9. Delete Book\n";
        cout << "10. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch(choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchByTitle(); break;
            case 4: searchByAuthor(); break;
            case 5: addMember(); break;
            case 6: displayMembers(); break;
            case 7: issueBook(); break;
            case 8: returnBook(); break;
            case 9: deleteBook(); break;
            case 10: cout << "Thank You!\n"; break;
            default: cout << "Invalid Choice!\n";
        }

    } while(choice != 10);

    return 0;
}
