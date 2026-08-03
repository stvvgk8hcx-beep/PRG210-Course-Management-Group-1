#define _CRT_SECURE_NO_WARNINGS
// this if or testing#
#include "AdminInterface.h"
#include "department.h"
#include "CSVUtils.h"
#include <iostream>
#include <limits>
#include <string>

// Admin must read and modify the department array. The last one allows Admin to save to the CSV filename from main.cpp so that changes persist. -J
extern Department* StoreDepartments;
extern int TotalDepartments;
extern const char* csvFile;

// Production Admin Interface completed, validated, and integrated by J, providing the main loop and department management functionality.

// Displays the Admin Menu until the admin chooses Exit.
void AdminInterface::run() {
    int choice = 0;
    // using the same menu template as main
    do {
        cout << "\n-----------------------------------------------------------" << endl;
        cout << "|                       ADMIN MENU                        |" << endl;
        cout << "-----------------------------------------------------------" << endl;
        cout << "|                  1. List Departments                    |" << endl;
        cout << "|                  2. Add Department                      |" << endl;
        cout << "|                  3. Add Course to Department            |" << endl;
        cout << "|                  4. Save Changes to CSV                 |" << endl;
        cout << "|                  5. Exit                                |" << endl;
        cout << "-----------------------------------------------------------" << endl;
        cout << "Enter your choice [1, 2, 3, 4, 5]: ";

 // Reuse the input validation inherited from Interface.
        choice = getValidChoice(1, 5);
        if (choice == 1) {
            listDepartments();
        }
        else if (choice == 2) {
            addDepartment();
        }
        else if (choice == 3) {
            addCourseToDepartment();
        }
        else if (choice == 4) {
            saveToCSV(csvFile);
        }

    } while (choice != 5);
}

// Prints a numbered list of every stored department.
// Production department-listing implementation by J.
void AdminInterface::listDepartments() {
    cout << "\n========== DEPARTMENTS ==========" << endl;

    // Handle the situation where no departments have been added.
    if (TotalDepartments == 0) {
        cout << "No departments are currently available." << endl;
        return;
    }

    for (int i = 0; i < TotalDepartments; i++) {
        // Arrays begin at index 0, but the visible menu begins at 1.
        cout << i + 1 << ". "
             << StoreDepartments[i].getName() << endl;
    }
}

// Adds a new department by creating a larger dynamic array.
// Production department-adding implementation by J.
void AdminInterface::addDepartment() {
    string departmentName;

    cout << "\nEnter department name (e.g. Computer Science): "; // just adding example descriptions to this cpp
    getline(cin, departmentName);

    // The name cannot be empty or contain a comma because commas
    // are used to separate information inside the CSV file.
    //
    // Department stores its name in char[50], meaning it can hold
    // up to 49 visible characters plus the null terminator.
    while (departmentName.empty() ||
           departmentName.length() > 49 ||
           departmentName.find(',') != string::npos) {

        if (departmentName.empty()) {
            cout << "Department name cannot be empty. Try again: ";
        }
        else if (departmentName.find(',') != string::npos) {
            cout << "Department name cannot contain a comma. Try again: ";
        }
        else {
            cout << "Department name must be 49 characters or fewer. Try again: ";
        }

        getline(cin, departmentName);
    }

 // Dynamic arrays cannot grow automatically, which sucks, because--
 //-- now I have to manually set up a new Department array with space for one additional department.
    Department* biggerArray =
        new Department[TotalDepartments + 1];


    // Copy every existing department into the larger array.
    for (int i = 0; i < TotalDepartments; i++) {
        biggerArray[i] = StoreDepartments[i];
    }
    // Store the new department in the final empty position.
    biggerArray[TotalDepartments] =
        Department(departmentName.c_str());

    // Delete the old smaller array so it does not leak memory.
    delete[] StoreDepartments;

    // Make the global pointer use the new larger array.
    StoreDepartments = biggerArray;

    // We now record that one more department now exists.
    TotalDepartments++;

    cout << "Department added successfully." << endl;
}

// Collects the course information and adds the course to the department selected by the admin.
// Production course-adding implementation by J.
void AdminInterface::addCourseToDepartment() {
    // Show the available departments before asking for a number.
    listDepartments();

    // A course cannot be added if no departments exist.
    if (TotalDepartments == 0) {
        cout << "Add a department before adding a course." << endl;
        return;
    }

        cout << "Enter department number [0 to go back]: ";

    // Zero means go back. The highest valid number is the
    // total number of departments.
    int departmentNumber =
        getValidChoice(0, TotalDepartments);

    if (departmentNumber == 0) {
        return;
    }

      // The menu begins at 1, but the array begins at index 0.
    // Using a reference gives the selected department an easier name.
    Department& selectedDepartment =
        StoreDepartments[departmentNumber - 1];


    cout << "\nCurrent courses in "
         << selectedDepartment.getName()
         << ":" << endl;

    selectedDepartment.listCourse();

     // Variables used to collect the new course information.
    string courseNumber;
    string courseSection;
    string courseName;
    string schedule;
    double price = 0.0;


    cout << "\nEnter course number (e.g. PRG210): ";
    getline(cin, courseNumber);
 // Course stores its number in char[10], so it can hold nine visible characters and the null terminator.
    while (courseNumber.empty() ||
           courseNumber.length() > 9 ||
           courseNumber.find(',') != string::npos) {

        cout << "Course number must contain 1 to 9 characters "
             << "and cannot contain a comma. Try again: ";

        getline(cin, courseNumber);
    }

    cout << "Enter course section (e.g. NBB or NAA): ";
    getline(cin, courseSection);

    // Course stores its section in char[4], allowing three
    // visible characters and the null terminator.
    while (courseSection.empty() ||
           courseSection.length() > 3 ||
           courseSection.find(',') != string::npos) {

        cout << "Course section must contain 1 to 3 characters "
             << "and cannot contain a comma. Try again: ";

        getline(cin, courseSection);
    }

     cout << "Enter course name (e.g. Object Oriented Programming): ";
    getline(cin, courseName);

    while (courseName.empty() ||
           courseName.find(',') != string::npos) {

        cout << "Course name cannot be empty or contain a comma. "
             << "Try again: ";

        getline(cin, courseName);
    }

    cout << "Enter course schedule [M/W, T/R, or W/F]: ";
    getline(cin, schedule);

    // Only accept the three schedules listed in the assignment.
    while (schedule != "M/W" &&
           schedule != "T/R" &&
           schedule != "W/F") {

        cout << "Schedule must be M/W, T/R, or W/F. Try again: ";

        getline(cin, schedule);
    }

    cout << "Enter course price: ";
    cin >> price;

    // Reject letters, zero, and negative prices.
    while (cin.fail() || price <= 0.0) {
        cin.clear();

        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );

        cout << "Price must be a positive number. Try again: ";
        cin >> price;
    }

    // Clear the newline left behind by cin so the next getline
    // used by a menu or function works correctly.
    cin.ignore(
        numeric_limits<streamsize>::max(),
        '\n'
    );

     // Convert the strings into const char* values because that
    // is what the Course constructor expects.
    Course newCourse(
        courseNumber.c_str(),
        courseSection.c_str(),
        courseName.c_str(),
        schedule.c_str(),
        price
    );

    // Department::addCourse() handles resizing its own course array.
    selectedDepartment.addCourse(newCourse);

    cout << "Course added successfully." << endl;
}
