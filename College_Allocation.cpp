#include <iostream>
#include <ctime>
#include <cstring>

using namespace std;

int main() {
    time_t now = time(0);
    char* dt = ctime(&now);
    cout << "Welcome to the Admission Portal!" << endl;
    cout << "\nCurrent date and time: " << dt;

  
    string username, password, entered_username, entered_password;
    username = "admin";
    password = "password";

    cout << "\nEnter username: ";
    cin >> entered_username;

    cout << "Enter password: ";
    cin >> entered_password;

    if (entered_username == username && entered_password == password) {
        cout << "Login successful!" << endl;

       
        string name;
        cout << "Enter your name: ";
        cin.ignore(); // To clear the newline character from the input buffer
        getline(cin, name);

        float marks;
        cout << "Enter your 10th percentage: ";
        cin >> marks;

        
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
    } else {
        cout << "Invalid username or password!" << endl;
    }

    return 0;
}