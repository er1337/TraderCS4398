//
// Created by Owner on 7/19/2016.
//

#ifndef TRADERCS4398_MENUS_H
#define TRADERCS4398_MENUS_H

#include <iostream>
#include <cstdlib>
using std::cout, using std::endl;

const char* TITLE = "Trading System";

void clear_screen() {
    #ifdef WINDOWS
        std::system("cls");
    #else
        // Assume POSIX
        std::system ("clear");
    #endif
}

void printMenuMain(){
    cout << TITLE << endl;
    cout << "Select an option." << endl;
    cout << "1. Set input file" << endl;
    cout << "2. Load account" << endl;
    cout << "3. Create new account" << endl;
}
void printMenuInputFile(){
    cout << TITLE << endl;
    cout << "Load input CSV file" << endl;
    cout << "Name of input file: " << endl;
}


#endif //TRADERCS4398_MENUS_H
