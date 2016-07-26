//
// Created by Owner on 7/19/2016.
//

#ifndef TRADERCS4398_MENUS_H
#define TRADERCS4398_MENUS_H

#include <iostream>
#include <cstdlib>
using std::cout; using std::endl; using std::cin;

const char* TITLE = "Trading System";

void clear_screen() {
    #ifdef WINDOWS
        std::system("cls");
    #else
        // Assume POSIX
        std::system ("clear");
    #endif
}
/**
template <typename T>
T getInput(){
    cout << "Enter: ";
    T in;
    cin << T;
    return T;
}
template <typename T>
T getInput(T minVal, T maxVal){
    cout << "Enter: ";
    T in;
    cin << T;
    while(T < minVal || T > maxVal){
        cout << "bad input, etc \nEnter: ";
        cin << T;
    }
    return T;
}
 **/

void printMenuMain(){
    cout << TITLE << endl;
    cout << "Select an option."     << endl;
    cout << "1. Set input file"     << endl;
    cout << "2. Load account"       << endl;
    cout << "3. Create new account" << endl;
    cout << "0. Back"               << endl;
    cout << endl;
}
void printMenuInputFile(){
    cout << TITLE << endl;
    cout << "Load input CSV file"   << endl;
    cout << "Name of input file: "  << endl;
    cout << endl;
}
void printMenuStrategy(){
    cout << TITLE << endl;
    cout << "Select strategy to use"         << endl;
    cout << "1. Price Cross Moving Average"  << endl;
    cout << "2. Double Moving Average Cross" << endl;
    cout << "...";
    cout << endl;
}


#endif //TRADERCS4398_MENUS_H
