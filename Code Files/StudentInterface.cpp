#include "StudentInterface.h"
#include "department.h"
#include <iomanip>

// This function runs the main loop for the student interface, 
// allowing the student to choose between browsing departments 
// or viewing their cart.

// For future reference for me and no one else, extern means these variables
// already exist somewhere else. We're telling the compiler that these variables exist elsewhere, 
// giving StudentInterface permission to use.

extern Department* StoreDepartments;
extern int TotalDepartments;

// Student main-menu implementation by J.

// Main loop for the student interface, allowing the student to choose between browsing departments or viewing their cart.
void StudentInterface::run() {
    int choice = 0;
    // Keep displaying the menu until the student chooses to exit.
    do {
         cout << "\n-----------------------------------------------------------" << endl;
        cout << "|                      STUDENT MENU                       |" << endl;
        cout << "-----------------------------------------------------------" << endl;
        cout << "|                  1. Show Cart                           |" << endl;
        cout << "|                  2. Browse Departments                  |" << endl;
        cout << "|                  3. Exit                                |" << endl;
        cout << "-----------------------------------------------------------" << endl;
        cout << "Enter your choice [1, 2, 3]: ";
        
        // This validaation function is inherited from the Interface class, ensuring that the input is within the valid range.
        choice = getValidChoice(1, 3);

        if (choice == 1) {
            showCartMenu();
        } else if (choice == 2) {
            browseDepartmentsMenu();
        }
    } while (choice != 3);
}

// Student cart-menu and checkout implementation by J.
// Display the courses in the cart and handles checkout.
void StudentInterface::showCartMenu() {
   int choice = 0;

   do {
        cout << "\n-----------------------------------------------------------" << endl;
        cout << "|                        CART MENU                        |" << endl;
        cout << "-----------------------------------------------------------" << endl;
        cout << "|                  1. List Courses                        |" << endl;
        cout << "|                  2. Checkout                            |" << endl;
        cout << "|                  3. Return to Student Menu              |" << endl;
        cout << "-----------------------------------------------------------" << endl;
        cout << "Enter your choice [1, 2, 3]: ";

        choice = getValidChoice(1, 3);

        if (choice == 1) {
            studentCart.listCourses();
        } 
        else if (choice == 2) {
            // The student cannot check out with an empty cart.
            if (studentCart.isEmpty()) {
                cout << "\nNo courses in the cart to checkout." << endl;
            } 
            else {
                // fixed and setprecision(2) display money with two decimals.
                cout << fixed << setprecision(2);
                cout << "\nYour total is $"
                     << studentCart.getTotalCost() << endl;
                cout << "Thank you for your purchase!" << endl;

                // Checkout removes every purchased course from the cart.
                studentCart.clearCart();

                // A successful checkout returns the student to the menu.
                return;    
            }
        }
    } while (choice != 3);
}
   
// Student department-listing implementation by J.
// Prints every available department as a numbered list.
void StudentInterface::listDepartments() {
cout << "\n========== DEPARTMENTS ==========" << endl;
// Handle the possibility that the admin has not added anything yet.
if (TotalDepartments == 0) {
    cout << "No departments are currently available." << endl;
    return;
}

for (int i = 0; i < TotalDepartments; i++) {
    // The array begins at index 0, but the menu should begin at 1.
    cout << i + 1 << ". " << StoreDepartments[i].getName() << endl;
}

} // End of listDepartments function.

// Student department-browsing menu implementation by J.
// Lets the student choose which department they want to browse.
void StudentInterface::browseDepartmentsMenu(){
    int choice = 0;
    do {
        listDepartments();
        cout << "\n-----------------------------------------------------------" << endl;
        cout << "|              1. List Department Courses                |" << endl;
        cout << "|              2. Go Back to Student Menu                |" << endl;
        cout << "-----------------------------------------------------------" << endl;
        cout << "Enter your choice [1, 2]: ";

        choice = getValidChoice(1, 2);

        if (choice == 1) {
            // Don't ask for a department number if none exists.
            if (TotalDepartments == 0) {
                cout << "\nThere are no departments to select." << endl;
                continue;
            }

            cout << "Enter the department number [0 to go back]: ";

            // Zero is allowed becuase the instructions specify to use it to go back.
            int departmentNumber = 
                getValidChoice(0, TotalDepartments);
            
                if (departmentNumber != 0) {
                    showDepartmentCourses(departmentNumber - 1);
                }
        }
    } while (choice != 2);
}

// Student course-selection and cart integration by J.
// Displays one's department's courses and allows the student to select a course to add to studentCart.
void StudentInterface::showDepartmentCourses(int departmentIndex) {
Department& selectedDepartment =
        StoreDepartments[departmentIndex];

    int choice = 0;

    do {
        cout << "\n========== " << selectedDepartment.getName() << " COURSES ==========" << endl;
        // Department already has a function that prints its courses. 
        selectedDepartment.listCourse();

cout << "\n-----------------------------------------------------------" << endl;
        cout << "|                  1. Add Course to Cart                  |" << endl;
        cout << "|                  2. Go Back                             |" << endl;
        cout << "-----------------------------------------------------------" << endl;
        cout << "Enter your choice [1, 2]: ";

        choice = getValidChoice(1, 2);
        if (choice == 1) {
            int courseCount = selectedDepartment.getCourseCount();
            // Do not ask for a course number if none exists.
            if (courseCount == 0) {
                cout << "\nThere are no courses to select." << endl;
                continue; 
            }
            cout << "Enter the course number to buy [0 to go back]: ";

            int courseNumber = getValidChoice (0, courseCount);

            if (courseNumber != 0) {
                // Conver the visible course number into an array index.
                Course* selectedCourse = selectedDepartment.getCourse(courseNumber - 1);

                // Dereference the pointer so addCourse receives the actual Course object.
                studentCart.addCourse(*selectedCourse);
                cout << "\nCourse added to cart!" << endl; 
            }
        }
} while (choice != 2);
}
