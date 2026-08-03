#ifndef STUDENTINTERFACE_H
#define STUDENTINTERFACE_H


#include "cart.h" // Student needs a Cart object to store selected courses.
#include "interface.h" // StudentInterface inherits from Interface.

// StudentInterface class structure and declarations by J.
// This features the student interface, allowing a student to interact with their course cart and browse departments.
class StudentInterface : public Interface {
// Each StudentInterface object has a Cart object to managethe student's selected courses.
private:
    Cart studentCart;

    void showCartMenu();
    void browseDepartmentsMenu();
    void listDepartments();
    void showDepartmentCourses(int departmentIndex);
// This overrides the pure virtual function from the Interface class,providing the main loop for the student interface.
public:
    void run() override; 
};

#endif // STUDENTINTERFACE_H    