#define _CRT_SECURE_NO_WARNINGS
// this if or testing#
#include "AdminInterface.h"
#include "department.h"
#include "CSVUtils.h"
#include <string>

// These global values are created in main.cpp.
extern const char* csvFile;

void AdminInterface::run() // want to have it where it will reloop the menu until it gets a proper answer
{

int choice = 0; {
    // using the same menu template as main
    cout << "\n-----------------------------------------------------------"<< endl
         << "|                       ADMIN MENU                        |" << endl
         << "-----------------------------------------------------------" << endl
         << "|                  1. List Departments                    |" << endl
         << "|                  2. Add Department                      |" << endl
         << "|                  3. Add Course to Department            |" << endl
         << "|                  4. Save Changes to CSV                 |" << endl
         << "|                  5. Exit                                |" << endl
         << "-----------------------------------------------------------" << endl
         << "Enter your choice [1, 2, 3, 4, 5]: ";

         choice = getValidChoice(1, 5);

         if (choice == 1) listDepartments();
         else if (choice == 2) addDepartment();
         else if (choice == 3) addCourseToDepartment();
         else if (choice == 4) saveToCSV(csvFile); // file location or figure this out
// no need for extra for 5 since it will end at 5 so

    } while (choice != 5);

    
}
