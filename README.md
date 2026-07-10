# PRG210-Course-Management-Group-1
This will be our repository for our Group Project please reach out if you have issues or trouble using this.
This is currently public so names will be covered for now. Please give usernames.

C***** P******
N***** A*****
N********* S****
J*** W******

Project-PRG210

Project Title: Course Management System

Introduction

In this project you are going to implement a basic Course Management System. The purpose of this software is to streamline the operations of a Course. This system involves two distinct interfaces: one for admins and one for students, each interface is tailored to meet their specific needs. The student interface allows students to browse departments, add courses to their cart, and proceed to checkout. The admin interface, on the other hand, provides tools for adding departments, course number and courses, and setting schedule and prices, and saving modifications to a CSV file. The system involves object-oriented programming principles, including inheritance and polymorphism, to create a modular and maintainable codebase. —

Section 1: User Interfaces

In a real application, there are different links for login for employees and students. However, for simplicity, you will show an initial menu that will allow user to choose the role.

Initial Menu

Options:
Student [1]
Admin [2]
Exit [3]
Prompt: Enter your choice [1, 2, 3]:
Validation: Only accept valid inputs (1, 2, or 3). If invalid, print the same prompt again.
Admin Interface

This interface handles the management part of the Course and presents the user with appropriate actions

Main Menu

Options:
List Departments [1]
Add Department [2]
Add Course to Department [3]
Save Changes to CSV [4]
Exit [5]
Prompt: Enter your choice [1, 2, 3, 4, 5]:
Validation: Only accept valid inputs (1, 2, 3, 4 or 5). If invalid, print the same prompt again.
1. List Departments

Displays: Numbered list of all available department names.
Show the Main Menu again
2. Add Department

Prompt: Enter department name:
Validation: Ensure the department name is not empty. If invalid, print the same prompt again.
Action: Adds the new department to the list of departments.
Message: Prints “Department added successfully.”
Return: Returns to the main menu.
3. Add Course to Department

Displays: Numbered list of all available department names.
Prompt: Enter department number [0 to go back]:
Validation: Only accept valid department numbers. If invalid, print the same prompt again.
Displays: Numbered list of all available courses in the selected department.
Action: Prompt for course details.
Prompt: Enter course number:
Validation: Ensure the course number is not empty. If invalid, print the same prompt again.
Prompt: Enter course name:
Validation: Ensure the course name is not empty. If invalid, print the same prompt again.
Prompt: Enter course schedule:
Validation: Only accept one of ‘M/W’, ‘T/R’, ‘W/F’ for schedule. If invalid, print the same prompt again.
Prompt: Enter course price:
Validation: Only accept valid positive numbers for price. If invalid, print the same prompt again.
Action: Adds the course to the selected department.
Message: Prints “Course added successfully.”
Return: Returns to the main menu.
4. Save Changes to CSV

Action: Writes all modifications (departments and courses) to the CSV file.
Message: Prints “Changes saved successfully.”
Return: Returns to the main menu.
5. Exit Program

Exits the program.
Student Interface

Main Menu

Options:
Show Cart [1]
Browse Departments [2]
Exit [3]
Prompt: Enter your choice [1, 2, 3]:
Validation: Only accept valid inputs (1, 2, or 3). If invalid, print the same prompt again.
1. Show Cart Menu

Options:
List Courses [1]
Checkout [2]
Return to Main Menu [3]
Prompt: Enter your choice [1, 2, 3]:
Validation: Only accept valid inputs (1, 2, or 3). If invalid, print the same prompt again.
1. List Courses:
Prints all courses in the cart with course number, name, schedule, and price.
Displays the same menu again.
2. Checkout:
If the cart is not empty, prints “Thank you for your purchase,” clears the shopping cart, and returns to the main menu.
If the cart is empty, prints “No courses in the cart” and displays the same menu again.
3. Return to Main Menu:
Returns to the main menu.
2. Browse Departments

Displays: Numbered list of all available department names.
Options:
List Courses of a Department [1]
Go Back to Main Menu [2]
Prompt: Enter your choice [1, 2]:
Validation: Only accept valid inputs (1 or 2). If invalid, print the same prompt again.
1. List Courses of a Department:
Prompts: Enter department number [0 to go back]:
Validation: Only accept valid department numbers. If invalid, print the same prompt again.
If the entered department number is correct, lists all numbered courses in the department with price per unit course.
Displays the following menu:
Add to Cart a Course [1]
Go Back to Browse Departments Menu [2]
Prompt: Enter your choice [1, 2]:
Validation: Only accept valid inputs (1 or 2). If invalid, print the same prompt again.
1. Add to Cart a Course:
Prompts: Enter course number to buy [0 to go back]:
Validation: Only accept valid course numbers. If invalid, print the same prompt again.
If the course number is correct, adds course schedule and price to the shopping cart, prints “Course added to cart,” and goes back to the courses menu.
2. Go Back to Browse Departments Menu:
Returns to the Browse departments menu.
2. Go Back to Main Menu:
Returns to the main menu.
3. Exit Program

Exits the program.

Section 2: Implementation Requirements

Here are implementation requirements for this project:

Classes

Your project must have the classes given below. All data members of all the classes must be private. I have listed only necessary data members, you can use more data members if you feel necessary.

Class: Course Class that will save information of each course, it should have:
Necessary private data members
Constructor to initialize the data members
Necessary public functions
Class: Department Class that will save all courses of one department, it should have:
Character array for department name
Dynamically allocated array of class courses to save courses in this department
Total number of courses in the department
Constructor and other necessary public member functions.
Destructor to clear the courses array
Class: Cart This class will have courses selected by Student for buying, it should have:
Dynamically allocated array of Course class, and a corresponding string array to save schedule of each course selected by the Student
Total count of courses in the cart and total cost of the cart along with 13% tax.
Necessary functions
Destructor to clear the memory
Interface Classes Since there are two types of user interfaces in this project (one for Admin and other for Student) with some commonalities and some differences. You must implement interface classes through inheritance. You should have one base Interface class (with common function declarations) and two derived AdminInterface and StudentInterface. Input validation and error message methods can also go in the base class since they are common.
main.cpp

This is the file that will have the main function. To make the implementation simpler you can declare following three global variables in this file and can access them in other cpp files using extern keyword

Department * StoreDepartments = nullptr;
int TotalDepartments = 0;
const char * csvFile = “Your/Path/To/CSVFile.cs”;
The main function should also:

Read the csv file if it exists at start and should load data in the StoreDepartments array (see the format of this csv file outlined below)
Have a pointer of Interface class and be initialized with the appropriate derived class object based on the selected role (Admin or Student) (it will be the polymorphism here)
Other Implementation Requirements

Here are additional implementation considerations:

Admin can add courses in an existing department in any order (for example first in first department, then in second department and then again in first department) make sure that you properly implement code to update the Courses array in each department.
All classes must be implemented in their corresponding .h and .cpp files
You can store data in csv file in the following format:
<Total Departments>
<Department 1 Name>, <Total Courses In Department 1>
<Course 1.1 name>, <Schedule>, <Price>
<Course 1.2 name>, <Schedule>, <Price>
...
<Department 2 Name>, <Total Courses In Department 2> 
<Course 2.1 name><Schedule>, <Price>
<Course 2.2 name><Schedule>, <Price>
If user enters a wrong input show a helpful error message
Thoroughly comment your code
You Must use only the concepts taught in the class (stl lists or vectors should NOT be used for Courses and Departments)
LLM based code will be graded zero
Submission Details

This is a group project, a group consists of two students.
The project must be done on GitHub CodeSpaces and regular commits should be made on GitHub. One of you should add your partner as collaborator.
You must plan and work on this project every week. A bulk commit in the last week raises suspicion!
In week 13, I will conduct interviews. Each group will have 10 minutes to present their project, demonstrate its functionality, and answer questions about their code. Remember, a programmer can explain their code clearly and fluently!
Rubric

Maximum marks without inheritance: 70%
Maximum marks without polymorphism: 90%
Maximum marks for implementing only one of two interfaces: 50%
100% marks depend on project interview
