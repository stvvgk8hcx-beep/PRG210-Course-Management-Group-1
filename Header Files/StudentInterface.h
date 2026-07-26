#ifndef STUDENTINTERFACE_H
#define STUDENTINTERFACE_H

#include "Interface.h"   // the base class (week 11 inheritance)
#include "Cart.h"

// StudentInterface : public Interface  <- inherits the run() + getValidChoice (lab9)
class StudentInterface : public Interface
{
private:
    Cart cart;   // each student gets their own cart

    // helpers so run() is still abel to be read
    void showCartMenu();
    void browseDepartments();

public:
    void run();  // my override of the base pure virtual run() see the main file
};

#endif
