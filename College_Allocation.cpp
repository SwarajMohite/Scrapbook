#include <iostream>
#include <ctime>
#include <cstring>

using namespace std;

struct Student {
    string name;
    string category;
    float marks;
    string chosenCollege;
};

int main() {
    //: Display Date and Time
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

        // Collect Category and Evaluate Eligibility
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

        // Choose College and Confirm Seat
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

        // Day 6: Store and Display Student Details
        cout << "\nStudent Details:\n";
        cout << "Name: " << s1.name << endl;
        cout << "Category: " << s1.category << endl;
        cout << "10th Percentage: " << s1.marks << "%" << endl;
        cout << "Chosen College: " << s1.chosenCollege << endl;
    } else {
        cout << "Invalid username or password!" << endl;
    }

    return 0;
}