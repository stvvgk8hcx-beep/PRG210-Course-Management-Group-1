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
Department::~Department()   // fixed was missing ~ makes it the DESTRUCTOR
{
    delete[] courses;
    courses = nullptr;

}
// look up proper array want it to grow when adding new and delete the previous
void Department::addCourse(Course c)   // the loop and return were unfinished/broken before
{
    Course* bigger = new Course[courseCount + 1]; // make an array one bigger

    for (int i = 0; i < courseCount; i++)         // copy the old courses over (was "i > 0, i++" which never ran)
        bigger[i] = courses[i];

    bigger[courseCount] = c;                      // drop the new course on the end

    delete[] courses;                             // free the old smaller array
    courses = bigger;                             // point at the new one
    courseCount++;                                // one more course now
}

// added this body - prints each course by reusing Course::display!
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

// added these getter bodies so other files can read the private data
const char* Department::getName()        { return departmentName; }
int         Department::getCourseCount() { return courseCount; }
Course*     Department::getCourse(int index) { return &courses[index]; } // pointer to the slot in the array
