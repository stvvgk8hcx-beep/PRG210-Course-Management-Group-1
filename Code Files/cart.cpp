// ok ok ok ok

#include "cart.h"
#include <iostream>
#include <string>

using namespace std;

// Default constructor hello
Cart::Cart()
{
    courses = nullptr;
    schedules = nullptr;
    courseCount = 0;
    subtotal = 0.0;
    totalCost = 0.0;
}

// Copy constructor
Cart::Cart(const Cart& other)
{
    courseCount = other.courseCount;
    subtotal = other.subtotal;
    totalCost = other.totalCost;

    if (courseCount > 0)
    {
        courses = new Course[courseCount];
        schedules = new string[courseCount];
        for (int i = 0; i < courseCount; ++i) {
            courses[i] = other.courses[i];
            schedules[i] = other.schedules[i];
        }
    }
    else
    {
        courses = nullptr;
        schedules = nullptr;
    }
}
// Assignment operator
Cart& Cart::operator=(const Cart& other)
{
    if (this != &other)
    {
        delete[] courses;
        delete[] schedules;

        courseCount = other.courseCount;
        subtotal = other.subtotal;
        totalCost = other.totalCost;

        if (courseCount > 0)
        {
            courses = new Course[courseCount];
            schedules = new string[courseCount];
            for (int i = 0; i < courseCount; ++i) {
                courses[i] = other.courses[i];
                schedules[i] = other.schedules[i];
            }
        }
        else
        {
            courses = nullptr;
            schedules = nullptr;
        }
    }
    return *this;
}

// Destructor
Cart::~Cart()
{
    delete[] courses;
    delete[] schedules;
}

// Add Course
void Cart::addCourse(const Course& course)
{
    Course* tempCourses = new Course[courseCount + 1];
    string* tempSchedules = new string[courseCount + 1];

    for (int i = 0; i < courseCount; ++i) {
        tempCourses[i] = courses[i];
        tempSchedules[i] = schedules[i];
    }

    tempCourses[courseCount] = course;
    tempSchedules[courseCount] = course.getSchedule();

    delete[] courses;
    delete[] schedules;

    courses = tempCourses;
    schedules = tempSchedules;
    ++courseCount;

    updateTotals();
}

// Display Cart
void Cart::listCourses()
{
    if (isEmpty())
    {
        cout <<"\nYour cart is empty.\n";
        return;
    }
    cout << "\n========== CART ==========\n";
    for (int i = 0; i < courseCount; i++)
    {
        cout <<"\nCourse " << i + 1 << endl;
        courses[i].display();
    }

    cout << "\nSubtotal: $" << subtotal << endl;
    cout << "Tax (13%): $" << getTax() << endl;
    cout << "Total    : $" << totalCost << endl;
}

// Clear Cart
void Cart::clearCart()
{
    delete[] courses;
    delete[] schedules;
    courses = nullptr;
    schedules = nullptr;
    courseCount = 0;
    subtotal = 0.0;
    totalCost = 0.0;
}

// Private Helper
void Cart::updateTotals()
{
    subtotal = 0.0;
    for (int i = 0; i < courseCount; ++i) {
        subtotal += courses[i].getPrice();
    }
    totalCost = subtotal * 1.13; // 13% tax
}

// Getters
bool Cart::isEmpty() const
{
    return courseCount == 0;
}

int Cart::getCourseCount() const
{
    return courseCount;
}
double Cart::getSubtotal() const
{
    return subtotal;
}
double Cart::getTax()const
{
    return totalCost - subtotal;
}
double Cart::getTotalCost() const
{
    return totalCost;
}