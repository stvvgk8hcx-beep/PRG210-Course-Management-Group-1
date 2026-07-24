#include "course.h" // its getting iostream and cstring from header!

Course::Course()
{
    courseNumber[0] = '\0';
    courseSection[0] = '\0';
    courseSchedule[0] = '\0';
    price = 0.0;

    courseName = new char[1];   // from Lab 8 dynamic, start as an empty string ""
    courseName[0] = '\0';
}

// Week 8 Overloaded constructor check page 23
Course::Course(const char* num, const char* sect, const char* name,
       const char* sched, double p)
{
    strcpy(courseNumber, num);
    strcpy(courseSection, sect);
    strcpy(courseSchedule, sched);

    courseName = new char[strlen(name) + 1]; // size is EXACTLY to the name (+1 for the \0) - more memory saved
    strcpy(courseName, name);

    // validate BEFORE we store the data because it will reject the bad data and try a safe one
    if (p > 0)
        price = p;
    else
        price = 0.0;     // The price cannot be a negative so it will just show 0 :)
}



// DESTRUCTOR
Course::~Course()
{
    delete[] courseName;   // must be delete[] because it was new char[]
    courseName = nullptr;
}

// COPY CONSTRUCTOR or deep copy
Course::Course(const Course& other)
{
    strcpy(courseNumber, other.courseNumber);
    strcpy(courseSection, other.courseSection);
    strcpy(courseSchedule, other.courseSchedule);
    price = other.price;

    courseName = new char[strlen(other.courseName) + 1]; // allocate its OWN memory
    strcpy(courseName, other.courseName);                // then copy the characters (deep, not shared)
}

// COPY-ASSIGNMENT - deep copy for existing objects
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
void Course::display() const

{
    cout << courseNumber << " " << courseSection << " " << courseName << " (" << courseSchedule << ") $" << price << endl;
}


// getter bodies - each just hands back one private member
// Added const to these bad boys too
const char* Course::getCourseNumber()  const { return courseNumber; }
const char* Course::getCourseSection() const { return courseSection; }
const char* Course::getCourseName()    const { return courseName; }
const char* Course::getSchedule()      const { return courseSchedule; }
double      Course::getPrice()         const { return price; }
