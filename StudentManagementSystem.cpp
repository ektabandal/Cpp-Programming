#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <sstream>

using namespace std;

class Student {
public:
    int rollNo;
    string name;
    int age;
    string course;
    float gpa;
    float attendance;

    void input() {
        cout << "\nEnter Roll Number: ";
        cin >> rollNo;
        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;
        cin.ignore();

        cout << "Enter Course: ";
        getline(cin, course);

        cout << "Enter GPA: ";
        cin >> gpa;

        cout << "Enter Attendance (%): ";
        cin >> attendance;
    }

    void display() const {
        cout << left
             << setw(10) << rollNo
             << setw(25) << name
             << setw(8) << age
             << setw(20) << course
             << setw(10) << gpa
             << setw(10) << attendance
             << endl;
    }
};

vector<Student> students;

// Save Data
void saveToFile() {
    ofstream file("students.txt");

    for (const auto &s : students) {
        file << s.rollNo << "|"
             << s.name << "|"
             << s.age << "|"
             << s.course << "|"
             << s.gpa << "|"
             << s.attendance << endl;
    }

    file.close();
}

// Load Data
void loadFromFile() {
    students.clear();

    ifstream file("students.txt");

    if (!file)
        return;

    string line;

    while (getline(file, line)) {
        try {
            Student s;

            stringstream ss(line);
            string temp;

            getline(ss, temp, '|');
            s.rollNo = stoi(temp);

            getline(ss, s.name, '|');

            getline(ss, temp, '|');
            s.age = stoi(temp);

            getline(ss, s.course, '|');

            getline(ss, temp, '|');
            s.gpa = stof(temp);

            getline(ss, temp);
            s.attendance = stof(temp);

            students.push_back(s);
        }
        catch (...) {
            cout << "Invalid record skipped.\n";
        }
    }

    file.close();
}

// Add Student
void addStudent() {
    Student s;
    s.input();

    for (auto &st : students) {
        if (st.rollNo == s.rollNo) {
            cout << "\nRoll Number already exists!\n";
            return;
        }
    }

    students.push_back(s);
    saveToFile();

    cout << "\nStudent Added Successfully!\n";
}

// Display Students
void displayStudents() {
    if (students.empty()) {
        cout << "\nNo Records Found!\n";
        return;
    }

    cout << "\n====================================================================================\n";

    cout << left
         << setw(10) << "RollNo"
         << setw(25) << "Name"
         << setw(8) << "Age"
         << setw(20) << "Course"
         << setw(10) << "GPA"
         << setw(10) << "Attend%" << endl;

    cout << "====================================================================================\n";

    for (const auto &s : students)
        s.display();
}

// Search Student
void searchStudent() {
    int roll;

    cout << "\nEnter Roll Number: ";
    cin >> roll;

    for (const auto &s : students) {
        if (s.rollNo == roll) {

            cout << "\nStudent Found:\n";

            cout << left
                 << setw(10) << "RollNo"
                 << setw(25) << "Name"
                 << setw(8) << "Age"
                 << setw(20) << "Course"
                 << setw(10) << "GPA"
                 << setw(10) << "Attend%" << endl;

            s.display();
            return;
        }
    }

    cout << "\nStudent Not Found!\n";
}

// Update Student
void updateStudent() {
    int roll;

    cout << "\nEnter Roll Number to Update: ";
    cin >> roll;
    cin.ignore();

    for (auto &s : students) {

        if (s.rollNo == roll) {

            cout << "\nEnter New Name: ";
            getline(cin, s.name);

            cout << "Enter New Age: ";
            cin >> s.age;
            cin.ignore();

            cout << "Enter New Course: ";
            getline(cin, s.course);

            cout << "Enter New GPA: ";
            cin >> s.gpa;

            cout << "Enter New Attendance: ";
            cin >> s.attendance;

            saveToFile();

            cout << "\nStudent Updated Successfully!\n";
            return;
        }
    }

    cout << "\nStudent Not Found!\n";
}

// Delete Student
void deleteStudent() {
    int roll;

    cout << "\nEnter Roll Number to Delete: ";
    cin >> roll;

    for (auto it = students.begin(); it != students.end(); ++it) {

        if (it->rollNo == roll) {

            students.erase(it);

            saveToFile();

            cout << "\nStudent Deleted Successfully!\n";
            return;
        }
    }

    cout << "\nStudent Not Found!\n";
}

// Sort by Roll Number
void sortByRollNo() {

    sort(students.begin(), students.end(),
         [](Student a, Student b) {
             return a.rollNo < b.rollNo;
         });

    cout << "\nSorted by Roll Number.\n";
    displayStudents();
}

// Sort by Name
void sortByName() {

    sort(students.begin(), students.end(),
         [](Student a, Student b) {
             return a.name < b.name;
         });

    cout << "\nSorted by Name.\n";
    displayStudents();
}

// Generate Report
void generateReport() {

    int roll;

    cout << "\nEnter Roll Number: ";
    cin >> roll;

    for (const auto &s : students) {

        if (s.rollNo == roll) {

            cout << "\n========== STUDENT REPORT ==========\n";

            cout << "Roll Number : " << s.rollNo << endl;
            cout << "Name        : " << s.name << endl;
            cout << "Age         : " << s.age << endl;
            cout << "Course      : " << s.course << endl;
            cout << "GPA         : " << s.gpa << endl;
            cout << "Attendance  : " << s.attendance << "%" << endl;

            if (s.gpa >= 9)
                cout << "Grade       : A+\n";
            else if (s.gpa >= 8)
                cout << "Grade       : A\n";
            else if (s.gpa >= 7)
                cout << "Grade       : B\n";
            else if (s.gpa >= 6)
                cout << "Grade       : C\n";
            else
                cout << "Grade       : D\n";

            return;
        }
    }

    cout << "\nStudent Not Found!\n";
}

// Admin Login
bool login() {

    string username, password;

    cout << "\n=========== ADMIN LOGIN ===========\n";

    cout << "Username: ";
    cin >> username;

    cout << "Password: ";
    cin >> password;

    if (username == "ektabandal" && password == "2366") {
        cout << "\nLogin Successful!\n";
        return true;
    }

    cout << "\nInvalid Username or Password!\n";
    return false;
}

// Main
int main() {

    loadFromFile();

    if (!login())
        return 0;

    int choice;

    do {

        cout << "\n\n========== STUDENT MANAGEMENT SYSTEM ==========\n";

        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Sort By Roll Number\n";
        cout << "7. Sort By Name\n";
        cout << "8. Generate Student Report\n";
        cout << "9. Exit\n";

        cout << "===============================================\n";

        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            addStudent();
            break;

        case 2:
            displayStudents();
            break;

        case 3:
            searchStudent();
            break;

        case 4:
            updateStudent();
            break;

        case 5:
            deleteStudent();
            break;

        case 6:
            sortByRollNo();
            break;

        case 7:
            sortByName();
            break;

        case 8:
            generateReport();
            break;

        case 9:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 9);

    return 0;
}