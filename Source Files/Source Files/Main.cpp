#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <limits>  // numeric_limits so a letter/huge number doesnt freak it out
#include "Department.h" // Department type for the globals
#include "CSVUtils.h" // for th loadFromCSV at startup
#include "Course.h"
#include "Interface.h"
#include "AdminInterface.h"
#include "StudentInterface.h"
using namespace std;

// the 3 globals the assignment wants. defined HERE, the other cpp files reach them with extern
Department* StoreDepartments = nullptr;
int TotalDepartments = 0;
const char* csvFile = "courses.csv";

int main() {

    loadFromCSV(csvFile);   // now read the saved data at the start (no file it just says so and keeps going on

    int options;


    cout << "-----------------------------------------------------------"     << endl
         << "Welcome! Please, select an option from the following menu: "     << endl
         << "-----------------------------------------------------------"     << endl
         << "|                        1. Student                       |"     << endl
         << "|                        2. Admin                         |"     << endl
         << "|                        3. Exit                          |"     << endl
         << "-----------------------------------------------------------"     << endl;

    cout << "Enter your choice [1, 2, 3]: ";
    cin >> options;

    while (cin.fail() || options < 1 || options > 3) { //so long as the options are less than 1 or greater than 3, we will keep asking // for a valid input
                                         //having issues where input of a high number (10000000000+) or letter causes it to freak out
        cin.clear();                                         // cin after a bad input
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // dump the junk before asking again

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
    cin.ignore(numeric_limits<streamsize>::max(), '\n');    // added - clear the newline so the menu getlines work

    // POLYMORPHISM (week 11) - one Interface pointer, point it at the child (admin or student i want
    Interface* ui = nullptr;
    if (options == 1) ui = new StudentInterface();   // 1 is student interface
    else if (options == 2) ui = new AdminInterface(); // 2 is admins
// it will exit otherwise

    if (ui != nullptr)
    {
        ui->run();    // virtual so the poly is able to pick the right instance and not the wrong one when its loading the information
        delete ui;   // clean up the child virtuallly
    }

    return 0;
}
