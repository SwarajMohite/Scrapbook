#include <iostream>
#include <ctime>
#include <cstring>
#include <fstream>

using namespace std;

struct Student {
    string name;
    string category;
    float marks;
    string chosenCollege;
};

void saveStudentDetails(const Student& s) {
    ofstream outFile("StudentDetails.txt", ios::app);
    if (outFile.is_open()) {
        outFile << s.name << "\n" << s.category << "\n" << s.marks << "\n" << s.chosenCollege << "\n";
        outFile.close();
        cout << "\nStudent details saved to 'StudentDetails.txt' successfully!" << endl;
    } else {
        cout << "Error opening file!" << endl;
    }
}

void searchStudentByName(const string& name) {
    ifstream inFile("StudentDetails.txt");
    string line;
    bool found = false;

    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            if (line == name) {
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

void deleteStudentRecord(const string& name) {
    ifstream inFile("StudentDetails.txt");
    ofstream tempFile("temp.txt");
    string line;
    bool found = false;

    if (inFile.is_open() && tempFile.is_open()) {
        while (getline(inFile, line)) {
            if (line == name) {
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

void updateStudentDetails(const string& name) {
    ifstream inFile("StudentDetails.txt");
    ofstream tempFile("temp.txt");
    string line;
    bool found = false;
    Student s;

    if (inFile.is_open() && tempFile.is_open()) {
        while (getline(inFile, line)) {
            if (line == name) {
                found = true;
                cout << "\nStudent Found: " << endl;
                s.name = line;
                getline(inFile, s.category);
                getline(inFile, line);
                s.marks = stof(line);
                getline(inFile, s.chosenCollege);

                cout << "Current Details:\n";
                cout << "Name: " << s.name << endl;
                cout << "Category: " << s.category << endl;
                cout << "10th Percentage: " << s.marks << "%" << endl;
                cout << "Chosen College: " << s.chosenCollege << endl;

                cout << "\nEnter new 10th Percentage: ";
                cin >> s.marks;
                cout << "Enter new Chosen College: ";
                cin.ignore(); // Clear the input buffer
                getline(cin, s.chosenCollege);

                tempFile << s.name << "\n" << s.category << "\n" << s.marks << "\n" << s.chosenCollege << "\n";
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
        cout << "Enter your name: ";
        cin.ignore(); // To clear the newline character from the input buffer
        getline(cin, s1.name);

        do {
            cout << "Enter your 10th percentage: ";
            cin >> s1.marks;

            if (s1.marks < 0 || s1.marks > 100) {
                cout << "Invalid marks! Please enter a percentage between 0 and 100." << endl;
            }
        } while (s1.marks < 0 || s1.marks > 100);

        //  Collect Category and Evaluate Eligibility
        do {
            cout << "Enter your category (Open/Reserved/Minor): ";
            cin >> s1.category;

            if (s1.category != "Open" && s1.category != "Reserved" && s1.category != "Minor") {
                cout << "Invalid category! Please enter 'Open', 'Reserved', or 'Minor'." << endl;
            }
        } while (s1.category != "Open" && s1.category != "Reserved" && s1.category != "Minor");

        //  Recommend Colleges Based on Marks and Category
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

        //Choose College and Confirm Seat
        int choice;
        do {
            cout << "\nEnter the number corresponding to the college you want to choose: ";
            cin >> choice;

            if (choice < 1 || choice > count) {
                cout << "Invalid choice! Please choose a valid college number." << endl;
            }
        } while (choice < 1 || choice > count);

        s1.chosenCollege = colleges[choice - 1];
        cout << "\nCongrats! Your seat at " << s1.chosenCollege << " is confirmed." << endl;

        // Store and Display Student Details
        cout << "\nStudent Details:\n";
        cout << "Name: " << s1.name << endl;
        cout << "Category: " << s1.category << endl;
        cout << "10th Percentage: " << s1.marks << "%" << endl;
        cout << "Chosen College: " << s1.chosenCollege << endl;

        // Save Student Details to File
        saveStudentDetails(s1);

        // Menu
        int dayMenuChoice;
        do {
            cout << "\n--- Additional Options ---" << endl;
            cout << "1. Search Student Details by Name" << endl;
            cout << "2. Delete Student Record" << endl;
            cout << "3. Update Student Details" << endl;
            cout << "4. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> dayMenuChoice;

            string searchName;
            switch (dayMenuChoice) {
                case 1:
                    cout << "\nEnter the name of the student to search: ";
                    cin.ignore();
                    getline(cin, searchName);
                    searchStudentByName(searchName);
                    break;
                
                case 2:
                    cout << "\nEnter the name of the student to delete: ";
                    cin.ignore();
                    getline(cin, searchName);
                    deleteStudentRecord(searchName);
                    break;

                case 3:
                    cout << "\nEnter the name of the student to update: ";
                    cin.ignore();
                    getline(cin, searchName);
                    updateStudentDetails(searchName);
                    break;

                case 4:
                    cout << "\nExiting the program. Thank you!" << endl;
                    break;

                default:
                    cout << "\nInvalid choice! Please select a valid option." << endl;
            }
        } while (dayMenuChoice != 4);
    } else {
        cout << "Login failed! Invalid username or password." << endl;
    }

    return 0;
}