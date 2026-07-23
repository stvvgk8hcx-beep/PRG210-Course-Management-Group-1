#ifndef DEPARTMENT_H
#define DEPARTMENT_H

// COMMIT NOTES - Calvin
// I made this file right after I did course. reasoning is Department will hold many courses is

// Course = one thing, Department = many things.


#include "course.h" //access the course objects we need for departments to access to


class Department
{
    private:

        char departmentName[50]; // we need char array for the name

        Course* courses; // pointer to a dynamic array of course so will grow at runtime

        int courseCount; // stores an integer for the amount of classes they have in the department


    public:

        Department(); //default constructo week 8

        Department(const char* name); //overload constructor

        ~Department(); //deconstructor free the dynamic array different than course!  week 8 p19

        Department(const Department& other);            // copy constructor
        Department& operator=(const Department& other); // copy-assignment rule of threeeeeee

        void addCourse(Course c); // will grow this array by one and stores the course

        void listCourse();  // will print the courses in a list by reusing Course::display
        //see course.cpp line 31
    // comment even said "Department WILL need a destructor" - past me was right! go past me
        const char* getName();



        int getCourseCount(); // display the number of courses
        Course* getCourse(int index); // this will come
        // now returns Course as a pointer like the prof CVS

};

#endif
