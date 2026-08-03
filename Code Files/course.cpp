#define _CRT_SECURE_NO_WARNINGS
#include "course.h"
#include <iomanip>
// its getting iostream and cstring from header!

Course::Course()
{
    courseNumber[0] = '\0';
    courseSection[0] = '\0';
    courseSchedule[0] = '\0';
    price = 0.0;

    courseName = new char[1];   // Lab 8: dynamic, start as an empty string ""
    courseName[0] = '\0';
}

// Week 8 Overloaded constructor check page 23
Course::Course(const char* num, const char* sect, const char* name,
       const char* sched, double p)
{
    // BUG FIX: strncpy caps the copy so a too-long value cant overflow these tight arrays week 3 said strcpy has no bounds check
    strncpy(courseNumber, num, 9);      courseNumber[9] = '\0';   // [10] -> copy at most 9 + the \0
    strncpy(courseSection, sect, 3);    courseSection[3] = '\0';  // [4]  -> 3 + \0
    strncpy(courseSchedule, sched, 3);  courseSchedule[3] = '\0'; // [4]  -> 3 + \0

    courseName = new char[strlen(name) + 1]; // Lab 8: size EXACTLY to the name (+1 for the \0) - this is the memory saving
    strcpy(courseName, name);

    // validate BEFORE we store the data because it will reject the bad data and try a safe one
    if (p > 0)
        price = p;
    else
        price = 0.0;     // The price cannot be a negative so it will just show 0 :)
}



// DESTRUCTOR - frees the memory courseName owns
Course::~Course()
{
    delete[] courseName;   // must be delete[] because it was new char[]
    courseName = nullptr;
}

// COPY CONSTRUCTOR - deep copy (runs on Course b(a); or passing by value)
Course::Course(const Course& other)
{
    strcpy(courseNumber, other.courseNumber);
    strcpy(courseSection, other.courseSection);
    strcpy(courseSchedule, other.courseSchedule);
    price = other.price;

    courseName = new char[strlen(other.courseName) + 1]; // allocate our OWN memory
    strcpy(courseName, other.courseName);                // then copy the characters (deep, not shared)
}

// COPY-ASSIGNMENT - deep copy for existing objects (runs on b = a;). 4 steps from my Lab 8 notes.
Course& Course::operator=(const Course& other)
{
    if (this == &other) return *this;   // 1) self-assignment guard

    strcpy(courseNumber, other.courseNumber);
    strcpy(courseSection, other.courseSection);
    strcpy(courseSchedule, other.courseSchedule);
    price = other.price;

    delete[] courseName;                                 // 2) free the old memory first (no leak)
    courseName = new char[strlen(other.courseName) + 1]; // 3) new memory + copy
    strcpy(courseName, other.courseName);

    return *this;                                        // 4) return *this (lets a = b = c chain)
}

// week 8 page 11 display will read the private and print them because the MEMBER functions can see the private data
void Course::display() const {
    cout << courseNumber << " " << courseSection << " " << courseName << " (" << courseSchedule << ") $" << fixed << setprecision(2) << price << endl;
}
// getter bodies - each just hands back one private member
// Added const to these bad boys too
const char* Course::getCourseNumber()  const { return courseNumber; }
const char* Course::getCourseSection() const { return courseSection; }
const char* Course::getCourseName()    const { return courseName; }
const char* Course::getSchedule()      const { return courseSchedule; }
double      Course::getPrice()         const { return price; }
