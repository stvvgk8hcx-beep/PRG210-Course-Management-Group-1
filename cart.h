// Will follow up on friday class with a more detailed-- 
// --explanation of the cart.h file and its functions. I want Bushra to review :) -J
#ifndef CART_H
#define CART_H
#include "course.h"
#include <string>


class Cart {
private:

    Course* courses; //Dynamic array of courses in the cart
    std::string* schedules; // Matching schedule for each course
    int courseCount; // Number of courses currently in the cart
    double subtotal; // Total before tax
    double totalCost; // Total after tax
    void updateTotals(); // Recalculate subtotal and totalCost

public:
    Cart();
    // Rule of threeeee
    Cart(const Cart& other);
    Cart& operator=(const Cart& other);
    ~Cart();

    // Cart operations
    void addCourse(const Course& course);
    void listCourses();
    void clearCart();

    // Cart info 
    bool isEmpty() const;
    int getCourseCount() const;
    double getSubtotal() const;
    double getTax() const;
    double getTotalCost() const;
};

#endif // CART_H

// Will go over to make sure I haven't made codeslop lmao -J