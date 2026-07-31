#ifndef ADMININTERFACE_H //guard etc
#define ADMININTERFACE_H

#include "interface.h"   //AdminInterface IS-A Interface

// AdminInterface : public Interface  <- same inheritance in lab 9
// this is the admin menu. it gets run() + getValidChoice() from the base and just adds its own stuff
class AdminInterface : public Interface
{
public:

    void run(); 

private:

    // little helper functions so run() isnt one giant mess and instead for later here are some planned menu options
    void listDepartments();
    void addDepartment();
    void addCourseToDepartment();
};

#endif
