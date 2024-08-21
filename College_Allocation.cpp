#include <iostream>
#include <ctime>
#include <cstring>

using namespace std;

int main() {
    //  Display Date and Time
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

        // collect and Evaluate Marks
        string name;
        cout << "Enter your name: ";
        cin.ignore(); // To clear the newline character from the input buffer
        getline(cin, name);

        float marks;
        cout << "Enter your last year percentage: ";
        cin >> marks;

        //  Collect Category and Evaluate Eligibility
        string category;
        cout << "Enter your category (Open/Reserved/Minor): ";
        cin >> category;

        if (marks >= 90) {
            cout << "Congrats " << name << "! You are eligible for top colleges." << endl;
        } else if (marks >= 75 && marks < 90) {
            cout << "You are eligible for mid-tier colleges." << endl;
        } else {
            cout << "Keep trying " << name << ", you can improve your score!" << endl;
        }

        //  Recommend Colleges Based on Marks and Category
        string colleges[5];
        int count = 0;

        if (marks >= 95) {
            colleges[count++] = "MIT";
            colleges[count++] = "Stanford";
        } else if (marks >= 90) {
            colleges[count++] = "Harvard";
            colleges[count++] = "Caltech";
        } else if (marks >= 85) {
            colleges[count++] = "University of Oxford";
            colleges[count++] = "University of Cambridge";
        }

        cout << "\nBased on your marks and category, you may consider these colleges:\n";
        for (int i = 0; i < count; ++i) {
            cout << i + 1 << ". " << colleges[i] << endl;
        }
    } else {
        cout << "Invalid username or password!" << endl;
    }

    return 0;
}