#ifndef INTERFACE_H // my guard :) week 7
#define INTERFACE_H

#pragma once

#include <iostream>
#include <limits>   // numeric_limits, to flush bad input the same way I did in main.cpp
using namespace std;

// same idea as  Lab 9 (PreferredStock : public Stock).
// AdminInterface and StudentInterface will both inherit from this so the shared stuff is written only one time
class Interface
{
public:

    virtual void run() = 0;

    // virtual destructor (Lab 8) so "delete interfacePointer" cleans up the real child object properly
    virtual ~Interface();

    // for the input validation + error messages
    int getValidChoice(int low, int high);  // same cin.fail loop from my main.cpp, reusable by both menus
    void errorMessage();                     // one spot for the wronginput message
};

#endif
