#define _CRT_SECURE_NO_WARNINGS

#include "AdminInterface.h"
#include "department.h"
#include "course.h"
#include "CSVUtils.h"

#include <iostream>
#include <limits>
#include <string>

using namespace std;

// extern lets this file use the same variables instead of making new copies.
extern Department* StoreDepartments;
extern int TotalDepartments;
extern const char* csvFile;


// Main admin menu.
// It keeps showing until the admin chooses option 5.
void AdminInterface::run()
{
    int choice = 0;

    do
    {
        cout << "\n-----------------------------------------------------------" << endl
             << "|                       ADMIN MENU                        |" << endl
             << "-----------------------------------------------------------" << endl
             << "|                 1. List Departments                    |" << endl
             << "|                 2. Add Department                      |" << endl
             << "|                 3. Add Course to Department            |" << endl
             << "|                 4. Save Changes to CSV                 |" << endl
             << "|                 5. Exit                                |" << endl
             << "-----------------------------------------------------------" << endl
             << "Enter your choice [1, 2, 3, 4, 5]: ";

        choice = getValidChoice(1, 5);

        if (choice == 1)
        {
            listDepartments();
        }
        else if (choice == 2)
        {
            addDepartment();
        }
        else if (choice == 3)
        {
            addCourseToDepartment();
        }
        else if (choice == 4)
        {
            saveToCSV(csvFile);
        }

    } while (choice != 5);
}


// Displays all departments already stored in the dynamic array.
void AdminInterface::listDepartments()
{
    if (TotalDepartments == 0)
    {
        cout << "\nNo departments are currently available." << endl;
        return;
    }

    cout << "\nDepartments" << endl;
    cout << "------------------------------" << endl;

    for (int i = 0; i < TotalDepartments; i++)
    {
        cout << i + 1 << ". "
             << StoreDepartments[i].getName()
             << endl;
    }
}


// Adds one new department by making the department array one space bigger.
void AdminInterface::addDepartment()
{
    string departmentName;

    do
    {
        cout << "\nEnter department name: ";
        getline(cin, departmentName);

        if (departmentName.empty())
        {
            cout << "Department name cannot be empty. Please try again."
                 << endl;
        }

    } while (departmentName.empty());

    // Make a new array with room for one more department.
    Department* biggerDepartments =
        new Department[TotalDepartments + 1];

    // Copy the old departments into the bigger array.
    for (int i = 0; i < TotalDepartments; i++)
    {
        biggerDepartments[i] = StoreDepartments[i];
    }

    // Store the new department at the end.
    biggerDepartments[TotalDepartments] =
        Department(departmentName.c_str());

    // The old smaller array is no longer needed.
    delete[] StoreDepartments;
    StoreDepartments = biggerDepartments;
    TotalDepartments++;

    cout << "Department added successfully." << endl;
}


// Lets the admin select a department and then enter a new course.
void AdminInterface::addCourseToDepartment()
{
    if (TotalDepartments == 0)
    {
        cout << "\nNo departments are available."
             << " Add a department first." << endl;
        return;
    }

    cout << "\nSelect a Department" << endl;
    cout << "------------------------------" << endl;

    for (int i = 0; i < TotalDepartments; i++)
    {
        cout << i + 1 << ". "
             << StoreDepartments[i].getName()
             << endl;
    }

    cout << "\nEnter department number [0 to go back]: ";

    int departmentChoice =
        getValidChoice(0, TotalDepartments);

    if (departmentChoice == 0)
    {
        return;
    }

    int departmentIndex = departmentChoice - 1;

    cout << "\nCourses currently in "
         << StoreDepartments[departmentIndex].getName()
         << ":" << endl;

    StoreDepartments[departmentIndex].listCourse();

    string courseNumber;
    string courseSection;
    string courseName;
    string courseSchedule;
    double coursePrice = 0.0;

    do
    {
        cout << "\nEnter course number: ";
        getline(cin, courseNumber);

        if (courseNumber.empty())
        {
            cout << "Course number cannot be empty. Please try again."
                 << endl;
        }

    } while (courseNumber.empty());

    do
    {
        cout << "Enter course section: ";
        getline(cin, courseSection);

        if (courseSection.empty())
        {
            cout << "Course section cannot be empty. Please try again."
                 << endl;
        }

    } while (courseSection.empty());

    do
    {
        cout << "Enter course name: ";
        getline(cin, courseName);

        if (courseName.empty())
        {
            cout << "Course name cannot be empty. Please try again."
                 << endl;
        }

    } while (courseName.empty());

    do
    {
        cout << "Enter course schedule [M/W, T/R, W/F]: ";
        getline(cin, courseSchedule);

        if (courseSchedule != "M/W" &&
            courseSchedule != "T/R" &&
            courseSchedule != "W/F")
        {
            cout << "Invalid schedule. Please enter M/W, T/R, or W/F."
                 << endl;
        }

    } while (courseSchedule != "M/W" &&
             courseSchedule != "T/R" &&
             courseSchedule != "W/F");

    cout << "Enter course price: ";
    cin >> coursePrice;

    while (cin.fail() || coursePrice <= 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Invalid price. Enter a positive number: ";
        cin >> coursePrice;
    }

    // Clear the newline left by cin before another getline is used later.
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Course newCourse(
        courseNumber.c_str(),
        courseSection.c_str(),
        courseName.c_str(),
        courseSchedule.c_str(),
        coursePrice
    );

    StoreDepartments[departmentIndex].addCourse(newCourse);

    cout << "Course added successfully." << endl;
}
