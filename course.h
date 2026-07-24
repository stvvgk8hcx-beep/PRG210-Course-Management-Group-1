#ifndef COURSE_H // my gaurd :) week 7
#define COURSE_H

#pragma once // so if two files both #include "Course.h", the compiler only processes it once instead of complaining that Course was defined twice.

#include <iostream>
#include <cstring> // week 3 strcpt to copy into character char arrays

using namespace std; // instead of std::string

class Course
{

private:

// data members are private

// department must use a character array for the names so char not int
    char courseNumber[10]; // PRG210 = 6 + \0, 10 leaves room
    char courseSection[4]; // NAA or NBB which is 4 NBB\0
    char* courseName;      //  sized to exactly strlen(name)+1 instead of a fixed [50] -> saves memory.
    char courseSchedule[4]; // M,/,W,\0 // one of M/W (Mon/Wed), T/R (Tue/Thu), W/F (Wed/Fri)
    double price; //should not be a negative number


public:

    Course();
// will use overload constructors rather than name above just diff parameter
// courseNumber = num

    Course(const char* num, const char* sect, const char* name,
       const char* sched, double p);

    // rule of three (Lab 8) -  because courseName owns heap memory (new[])
    ~Course();                                // destructor: free courseName
    Course(const Course& other);              // copy constructor: deep copy (Stock b(a);)
    Course& operator=(const Course& other);   // copy-assignment

    void display() const;

    // getters so the professor's CSVUtils.cpp can READ each private value when it saves
    // added const to the getters so that they can be called on const Course objects (like in the Cart class)
    const char* getCourseNumber() const;
    const char* getCourseSection() const;
    const char* getCourseName() const;
    const char* getSchedule() const;
    double getPrice() const;

};

#endif

