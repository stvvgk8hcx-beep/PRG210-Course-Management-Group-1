#include "cart.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Cart dynamic-memory, copying, totals, and checkout support implemented by J.

// Default constructor initializes the cart with no courses and zero totals.
Cart::Cart()
{
    courses = nullptr;
    schedules = nullptr;
    courseCount = 0;
    subtotal = 0.0;
    totalCost = 0.0;
}

// Copy constructor performs a deep copy of the other cart, allocating new memory for courses and schedules.
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
// Assignment operator performs a deep copy of the other cart, properly handling self-assignment and memory management.
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

// Destructor releases the dynamically allocated memory for courses and schedules.
Cart::~Cart()
{
    delete[] courses;
    delete[] schedules;
}

// Add Course adds a new course to the cart, expanding the arrays and updating totals.
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

// Display Cart lists all courses in the cart along with the subtotal, tax, and total cost.
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

    cout << fixed << setprecision(2);
    cout << "\nSubtotal: $" << subtotal << endl;
    cout << "Tax (13%): $" << getTax() << endl;
    cout << "Total    : $" << totalCost << endl;
}

// Clear Cart removes all courses from the cart and resets totals.
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

// Private Helper updates the subtotal and total cost based on the current courses in the cart.
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