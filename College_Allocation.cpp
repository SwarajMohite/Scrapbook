#include <iostream>
#include <ctime>
#include <cstring>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Student {
    string name;
    string category;
    float marks;
    string gender;
    int age;
    string college;
};

vector<Student> studentDatabase;

void saveStudentDetails(const Student& s) {
    ofstream outFile("StudentDetails.txt", ios::app);
    if (outFile.is_open()) {
        outFile << s.name << "\n" << s.category << "\n" << s.marks << "\n" << s.college << "\n";
        outFile.close();
        cout << "\nStudent details saved to 'StudentDetails.txt' successfully!" << endl;
    } else {
        cout << "Error opening file!" << endl;
    }
}

void searchStudentByName(const string& searchName) {
    ifstream inFile("StudentDetails.txt");
    string line;
    bool found = false;

    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            if (line == searchName) {
                found = true;
                cout << "\nStudent Found: " << endl;
                cout << "Name: " << line << endl;
                getline(inFile, line);
                cout << "Category: " << line << endl;
                getline(inFile, line);
                cout << "10th Percentage: " << line << "%" << endl;
                getline(inFile, line);
                cout << "Chosen College: " << line << endl;
                break;
            }
        }
        inFile.close();
        if (!found) {
            cout << "\nStudent not found!" << endl;
        }
    } else {
        cout << "Error opening file!" << endl;
    }
}

void deleteStudentRecord(const string& searchName) {
    ifstream inFile("StudentDetails.txt");
    ofstream tempFile("temp.txt");
    string line;
    bool found = false;

    if (inFile.is_open() && tempFile.is_open()) {
        while (getline(inFile, line)) {
            if (line == searchName) {
                found = true;
                // Skip the next 3 lines (category, marks, chosenCollege)
                for (int i = 0; i < 3; i++) getline(inFile, line);
            } else {
                tempFile << line << "\n";
            }
        }
        inFile.close();
        tempFile.close();

        remove("StudentDetails.txt");
        rename("temp.txt", "StudentDetails.txt");

        if (found) {
            cout << "\nStudent record deleted successfully!" << endl;
        } else {
            cout << "\nStudent not found!" << endl;
        }
    } else {
        cout << "Error opening file!" << endl;
    }
}

void updateStudentDetails(const string& searchName) {
    ifstream inFile("StudentDetails.txt");
    ofstream tempFile("temp.txt");
    string line;
    bool found = false;
    Student s;

    if (inFile.is_open() && tempFile.is_open()) {
        while (getline(inFile, line)) {
            if (line == searchName) {
                found = true;
                cout << "\nStudent Found: " << endl;
                s.name = line;
                getline(inFile, s.category);
                getline(inFile, line);
                s.marks = stof(line);
                getline(inFile, s.college);

                cout << "Current Details:\n";
                cout << "Name: " << s.name << endl;
                cout << "Category: " << s.category << endl;
                cout << "10th Percentage: " << s.marks << "%" << endl;
                cout << "Chosen College: " << s.college << endl;

                cout << "\nEnter new 10th Percentage: ";
                cin >> s.marks;
                cout << "Enter new Chosen College: ";
                cin.ignore(); // Clear the input buffer
                getline(cin, s.college);

                tempFile << s.name << "\n" << s.category << "\n" << s.marks << "\n" << s.college << "\n";
            } else {
                tempFile << line << "\n";
            }
        }
        inFile.close();
        tempFile.close();

        remove("StudentDetails.txt");
        rename("temp.txt", "StudentDetails.txt");

        if (found) {
            cout << "\nStudent details updated successfully!" << endl;
        } else {
            cout << "\nStudent not found!" << endl;
        }
    } else {
        cout << "Error opening file!" << endl;
    }
}

void viewAllStudents() {
    cout << "\nDisplaying all student records:\n";
    for (const auto& student : studentDatabase) {
        cout << "\nStudent Name: " << student.name << endl;
        cout << "Category: " << student.category << endl;
        cout << "Marks: " << student.marks << endl;
        cout << "Gender: " << student.gender << endl;
        cout << "Age: " << student.age << endl;
        cout << "Chosen College: " << student.college << endl;
    }
}

void viewStatistics() {
    int totalStudents = studentDatabase.size();
    int maleCount = 0, femaleCount = 0, otherCount = 0;
    float totalMarks = 0.0;

    for (const auto& student : studentDatabase) {
        totalMarks += student.marks;
        if (student.gender == "Male") maleCount++;
        else if (student.gender == "Female") femaleCount++;
        else otherCount++;
    }

    float averageMarks = totalMarks / totalStudents;

    cout << "\nStatistics:\n";
    cout << "Total Students: " << totalStudents << endl;
    cout << "Average Marks: " << averageMarks << "%" << endl;
    cout << "Male Students: " << maleCount << endl;
    cout << "Female Students: " << femaleCount << endl;
    cout << "Other Students: " << otherCount << endl;
}

void listStudentsByCategory(const string& category) {
    cout << "\nListing students in category: " << category << endl;
    for (const auto& student : studentDatabase) {
        if (student.category == category) {
            cout << "\nStudent Name: " << student.name << endl;
            cout << "Marks: " << student.marks << "%" << endl;
            cout << "Chosen College: " << student.college << endl;
        }
    }
}

int main() {
    // Display Date and Time
    time_t now = time(0);
    char* dt = ctime(&now);
    cout << "Welcome to the Admission Portal!" << endl;
    cout << "Current date and time: " << dt;

    // Login System
    string username, password, entered_username, entered_password;
    username = "admin";
    password = "password";

    cout << "\nEnter username: ";
    cin >> entered_username;

    cout << "Enter password: ";
    cin >> entered_password;

    if (entered_username == username && entered_password == password) {
        cout << "Login successful!" << endl;

        // Collect and Evaluate Marks
        Student s1;
        cout << "Enter name of Student: ";
        cin.ignore(); // To clear the newline character from the input buffer
        getline(cin, s1.name);

        do {
            cout << "Enter your 10th percentage: ";
            cin >> s1.marks;

            if (s1.marks < 0 || s1.marks > 100) {
                cout << "Invalid marks! Please enter a percentage between 0 and 100." << endl;
            }
        } while (s1.marks < 0 || s1.marks > 100);

        // Collect Category and Evaluate Eligibility
        do {
            cout << "Enter your category (Open/Reserved/Minor): ";
            cin >> s1.category;

            if (s1.category != "Open" && s1.category != "Reserved" && s1.category != "Minor") {
                cout << "Invalid category! Please enter 'Open', 'Reserved', or 'Minor'." << endl;
            }
        } while (s1.category != "Open" && s1.category != "Reserved" && s1.category != "Minor");

        // Recommend Colleges Based on Marks and Category
        string colleges[5];
        int count = 0;

        if (s1.marks >= 95) {
            colleges[count++] = "MIT";
            colleges[count++] = "Stanford";
        } else if (s1.marks >= 90) {
            colleges[count++] = "Harvard";
            colleges[count++] = "Caltech";
        } else if (s1.marks >= 85) {
            colleges[count++] = "University of Oxford";
            colleges[count++] = "University of Cambridge";
        } else {
            cout << "Based on your marks, we recommend improving your score for better options." << endl;
            return 0;
        }

        cout << "\nBased on your marks and category, you may consider these colleges:\n";
        for (int i = 0; i < count; ++i) {
            cout << i + 1 << ". " << colleges[i] << endl;
        }

        // Choose College and Confirm Seat
        int choice;
        do {
            cout << "\nEnter the number corresponding to the college you want to choose: ";
            cin >> choice;

            if (choice < 1 || choice > count) {
                cout << "Invalid choice! Please choose a valid college number." << endl;
            }
        } while (choice < 1 || choice > count);

        s1.college = colleges[choice - 1];
        cout << "\nYou have chosen " << s1.college << ". Your seat is confirmed!" << endl;

        // Additional Details
        cout << "Enter your gender (Male/Female/Other): ";
        cin >> s1.gender;

        cout << "Enter your age: ";
        cin >> s1.age;

        // Save details and add to the database
        studentDatabase.push_back(s1);
        saveStudentDetails(s1);

        // Display Menu for Further Actions
        int option;
        do {
            cout << "\nMenu:\n";
            cout << "1. Search Student by Name\n";
            cout << "2. Delete Student Record\n";
            cout << "3. Update Student Details\n";
            cout << "4. View All Students\n";
            cout << "5. View Statistics\n";
            cout << "6. List Students by Category\n";
            cout << "7. Exit\n";
            cout << "Enter your choice: ";
            cin >> option;

            switch (option) {
                case 1: {
                    string searchName;
                    cout << "Enter the name of the student to search: ";
                    cin.ignore();
                    getline(cin, searchName);
                    searchStudentByName(searchName);
                    break;
                }
                case 2: {
                    string searchName;
                    cout << "Enter the name of the student to delete: ";
                    cin.ignore();
                    getline(cin, searchName);
                    deleteStudentRecord(searchName);
                    break;
                }
                case 3: {
                    string searchName;
                    cout << "Enter the name of the student to update: ";
                    cin.ignore();
                    getline(cin, searchName);
                    updateStudentDetails(searchName);
                    break;
                }
                case 4:
                    viewAllStudents();
                    break;
                case 5:
                    viewStatistics();
                    break;
                case 6: {
                    string category;
                    cout << "Enter the category to list students (Open/Reserved/Minor): ";
                    cin >> category;
                    listStudentsByCategory(category);
                    break;
                }
                case 7:
                    cout << "Exiting the program. Goodbye!" << endl;
                    break;
                default:
                    cout << "Invalid choice! Please select a valid option." << endl;
            }
        } while (option != 7);

    } else {
        cout << "Login failed! Invalid username or password." << endl;
    }

    return 0;
}