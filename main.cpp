// header files
#include "department.h"      // Currantly when you run the program and select 1,2,3
// header files
#include "CSVUtils.h" //added file

#include "course.h"
#include <iostream>
#include <limits>   // prof rec gives numeric_limits so no more bad inputs :)
using namespace std;

Department* StoreDepartments = nullptr;
int TotalDepartments = 0;
const char* csvFile = "courses.csv";   // added path to csv file ask prof about its location when demonstrating

int main() {

    int options;


    cout << "-----------------------------------------------------------"     << endl;
    cout << "Welcome! Please, select an option from the following menu: "     << endl;
    cout << "-----------------------------------------------------------"     << endl;
    cout << "|                        1. Student                       |"       << endl; // fixed was 2.Student
    cout << "|                        2. Admin                         |"      << endl;
    cout << "|                        3. Exit                          |"       << endl;
    cout << "-----------------------------------------------------------"     << endl;

    cout << "Enter your choice [1, 2, 3]: ";
    cin >> options;

    // is NOW cin.fail() so a LETTER entered value or a HUGE number doesn't make the program freak out like me on a dancefloor
    // now it will "cin.fail()" when its not a valid int input is true and is inside the loop

    while (cin.fail() || options < 1 || options > 3) { //so long as the options are less than 1 or greater than 3, we keep asking - Calvin

        cin.clear();                                          // reset/recycle the fail flag so cin works again
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // remove the leftover bad input

        cout << "-----------------------------------------------------------" << endl;
        cout << "Please enter a valid responce from the menu: "               << endl  // ask prof why no semicolon here
             << "-----------------------------------------------------------" << endl
             << "|                       1. Student                        |" << endl
             << "|                       2. Admin                          |" << endl
             << "|                       3. Exit                           |" << endl
             << "-----------------------------------------------------------" << endl;
        cout << "Enter your choice [1, 2, 3]: ";
        cin >> options;
    }

    // this is where an Interface pointer will point at too
    // AdminInterface + StudentInterface !

    return 0;
}

