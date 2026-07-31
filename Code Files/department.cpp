#include "department.h"


Department::Department()
{
    departmentName[0] = '\0';
    courses = nullptr; // initalize your pointers :)
    courseCount = 0;

}

Department::Department(const char* name)

{
    strcpy(departmentName, name);
    courses = nullptr;
    courseCount = 0;
// Department starts with its name
// Overload Constructor from week 8

}
//now destructor to free that memory
Department::~Department()   // NOTE: was "Department::Department()" by mistake - the ~ makes it the destructor, not a 3rd constructor
{
    delete[] courses;
    courses = nullptr;

}

// rule of 3 - same method as Course, but now its for the whole course array
Department::Department(const Department& other)
{
    strcpy(departmentName, other.departmentName);
    courseCount = other.courseCount;
    if (courseCount > 0)
    {
        courses = new Course[courseCount];
        for (int i = 0; i < courseCount; i++)
            courses[i] = other.courses[i];   // Course's own operator= deep-copies each one
    }
    else
        courses = nullptr;
}

//  copy-assignment - same 4 steps as my Course operator=
Department& Department::operator=(const Department& other)
{
    if (this == &other) return *this;   // 1) self-assignment guard
    delete[] courses;                    // 2) free old array

    strcpy(departmentName, other.departmentName);
    courseCount = other.courseCount;
    if (courseCount > 0)                 // 3) new array + copy
    {
        courses = new Course[courseCount];
        for (int i = 0; i < courseCount; i++)
            courses[i] = other.courses[i];
    }
    else
        courses = nullptr;

    return *this;                        // 4) return *this
}

// look up proper array want it to grow when adding new and delete the previous
void Department::addCourse(Course c)   //
{
    Course* bigger = new Course[courseCount + 1]; //  make an array one bigger

    for (int i = 0; i < courseCount; i++)         // copy the old courses over (was "i > 0, i++" which never ran)
        bigger[i] = courses[i];

    bigger[courseCount] = c;                      // drop the new course on the end

    delete[] courses;                             //  free the old smaller array
    courses = bigger;                             // point at the new one
    courseCount++;                                // one more course now
}

// added this body prints each course by reusing Course::display (see course.cpp)
void Department::listCourse()
{
    if (courseCount == 0)
    {
        cout << "No courses in this department." << endl;
        return;
    }
    for (int i = 0; i < courseCount; i++)
    {
        cout << i + 1 << ". ";   // numbered list
        courses[i].display();
    }
}

// added these small getter bodies so other files can read the private data
const char* Department::getName()        { return departmentName; }
int         Department::getCourseCount() { return courseCount; }
Course*     Department::getCourse(int index) { return &courses[index]; } // pointer to the slot in the array
