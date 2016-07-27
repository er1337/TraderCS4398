//
// Created by Owner on 7/19/2016.
//

#ifndef TRADERCS4398_MENUS_H
#define TRADERCS4398_MENUS_H

#include <iostream>
#include <cstdlib>
using std::cout; using std::endl; using std::cin; using std::string;
class Menus{

private:
    const char* TITLE = "Trading System";
    string infile = "not-set";
    char delimiter = ',';
    //vector of accounts

public:
    string getInfile(){ return infile; }

    void clear_screen() {
        #ifdef WINDOWS
            std::system("cls");
        #else
            // Assume POSIX
            std::system ("clear");
        #endif
    }
    template <typename T>
    T getInput(){
        cout << "Enter: ";
        T in;
        cin >> in;
        return in;
    }
    template <typename T>
    T getInput(T minVal, T maxVal){
        cout << "Enter: ";
        T in;
        cin >> in;
        while(in < minVal || in > maxVal){
            cout << "bad input, etc \nEnter: ";
            cin >> in;
        }
        return in;
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
        cout << "3. ...";
        cout << endl;
    }
    void printMenuMain(){
        cout << TITLE << endl;
        cout << "Select an option."     << endl;
        cout << "1. Set input file"     << endl;
        cout << "2. Load account"       << endl;
        cout << "3. Create new account" << endl;
        cout << "4. Select strategy"    << endl;
        cout << "0. Back"               << endl;
        cout << endl;
    }
    void printMenuLoadAccount(){
        // need to pass in account list loaded from file beforehand.
        cout << TITLE << endl;
        cout << "Select an option."     << endl;
        cout << "1. Account 1, etc etc" << endl;
        cout << endl;
    }
    void runMenuMain(){
        printMenuMain();
        int choice = getInput<int>();
        clear_screen();
        switch(choice){
            case 1:
                runSubmenuInputFile();
                break;
            case 2:
                //runSubmenuLoadAccount();
                break;
            case 3:
                runSubmenuCreateAccount();
                break;
        }
    }
    void runSubmenuInputFile(){
        printMenuInputFile();
        infile = getInput<std::string>();
        // this is the point where I gave up making it all modular
        cout << "Change delimiter? (default=',') \nY/N: ";
        char choice = getInput<char>(); //call setDelimiter after

        switch (choice){
            case 'y':
            case 'Y':
                cout << "Enter custom delimiter: \n";
                delimiter = getInput<char>();

        cout << "Skip first header row? (default='Y') \nY/N: ";
        choice = getInput<char>(); //call setDelimiter after
        switch (choice){
            case 'n':
            case 'N':

                delimiter = getInput<char>();

        clear_screen();
        }
    }


};
#endif //TRADERCS4398_MENUS_H
