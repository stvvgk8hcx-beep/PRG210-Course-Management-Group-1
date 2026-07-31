#include "interface.h"

// the destructor is empty but it still has to exist because I declared it virtual in the header
Interface::~Interface()
{
}

// this is the same validation loop from my main.cpp
// just moved here so BOTH menus can reuse it instead of me copy-pasting it twice
int Interface::getValidChoice(int low, int high)
{
    int choice;
    cin >> choice;

    while (cin.fail() || choice < low || choice > high)
    {
        cin.clear();                                          // reset so cin works again
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // dump the leftover bad input
        errorMessage();
        cin >> choice;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');      // clear the trailing newline so getline works after
    return choice;
}

void Interface::errorMessage()
{
    cout << "That was not a valid option, please try again: ";
}
