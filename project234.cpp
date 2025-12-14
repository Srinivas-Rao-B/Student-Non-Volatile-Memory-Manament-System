#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Person {
public:
    string name, usn, branch, college_name, password;
    int age, current_semester;
    float prev_sem_total_marks, cgpa, fees_paid, fees_due;

    void enterDetails() {
        cin.ignore();
        cout << "Name: "; getline(cin, name);
        cout << "Age: "; cin >> age;
        cout << "USN: "; cin.ignore(); getline(cin, usn);
        cout << "Branch: "; getline(cin, branch);
        cout << "Semester: "; cin >> current_semester;
        cout << "College: "; cin.ignore(); getline(cin, college_name);
        cout << "Prev Marks: "; cin >> prev_sem_total_marks;
        cout << "CGPA: "; cin >> cgpa;
        cout << "Fees Paid: "; cin >> fees_paid;
        cout << "Fees Due: "; cin >> fees_due;
        cout << "Password: "; cin.ignore(); getline(cin, password);
    }

    void saveDetails(fstream& file) {
        file << name << "\n" << age << "\n" << usn << "\n" << branch << "\n" 
             << current_semester << "\n" << college_name << "\n" << prev_sem_total_marks << "\n" 
             << cgpa << "\n" << fees_paid << "\n" << fees_due << "\n" << password << "\n";
    }

    void loadDetails(fstream& file) {
        getline(file, name);
        file >> age; file.ignore();
        getline(file, usn); getline(file, branch);
        file >> current_semester; file.ignore();
        getline(file, college_name);
        file >> prev_sem_total_marks >> cgpa >> fees_paid >> fees_due;
        file.ignore(); getline(file, password);
    }

    bool authenticate(string entered_password) {
        return entered_password == password;
    }

    void displayDetails() {
        cout << "Name: " << name << "\nAge: " << age << "\nUSN: " << usn 
             << "\nBranch: " << branch << "\nSemester: " << current_semester 
             << "\nCollege: " << college_name << "\nPrev Marks: " << prev_sem_total_marks 
             << "\nCGPA: " << cgpa << "\nFees Paid: " << fees_paid 
             << "\nFees Due: " << fees_due << "\n";
    }
};

int main() {
    Person persons[10];
    int person_count = 0;
    fstream file("persons_data.txt", fstream::in | fstream::out | fstream::app);

    if (file.is_open()) {
        while (file.peek() != EOF && person_count < 10) {
            persons[person_count].loadDetails(file);
            person_count++;
        }
    }
    file.close();

    int choice, new_persons;
    string usn_input, password_input;

    cout << "Enter 1 to add new persons, 0 to skip: "; cin >> choice;
    if (choice == 1) {
        cout << "How many? "; cin >> new_persons;
        file.open("persons_data.txt", fstream::out | fstream::app);
        for (int i = 0; i < new_persons && person_count < 10; i++) {
            persons[person_count].enterDetails();
            persons[person_count].saveDetails(file);
            person_count++;
        }
        file.close();
    }

    do {
        cout << "\nEnter 1 to get info, 0 to exit: "; cin >> choice;
        if (choice == 1) {
            cout << "Enter USN: "; cin.ignore(); getline(cin, usn_input);
            bool found = false;
            for (int i = 0; i < person_count; i++) {
                if (persons[i].usn == usn_input) {
                    cout << "Enter Password: "; getline(cin, password_input);
                    if (persons[i].authenticate(password_input)) {
                        persons[i].displayDetails();
                    } else {
                        cout << "Incorrect Password!\n";
                    }
                    found = true;
                    break;
                }
            }
            if (!found) cout << "USN not found!\n";
        }
    } while (choice != 0);

    return 0;
}

