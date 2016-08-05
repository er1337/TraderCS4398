//
// Created by Owner on 7/19/2016.
//

#ifndef TRADERCS4398_MENUS_H
#define TRADERCS4398_MENUS_H

#include <fstream>
#include <iostream>
#include <cstdlib>
#include "enums.h"

using std::cout; using std::endl; using std::cin; using std::string;

//todo: implement back menu choices
class Menus{
private:
    const char* TITLE = "Trading System";

    //this aint right
    string infile = "not-set";
    char delimiter = ',';
    bool ignoreHeader = true;

    int strategyMenuChoice = 0;
    int movingAverageLength = 25;
    float strategyMenuCommission = 0;

    bool accountLoaded = false;
    bool fileLoaded = false;
    bool stratLoaded = false;

    //list of accounts loaded in

    menuAction_t currentSelectedAction = nothing;

public:
    // return csv related inputs as a group
    // you know in python, you can have a function return multiple variables at once. In c++, its weirder.
    void getCSVparameters(string& infileOutput, char& delimiterOutput, bool& ignoreHeaderOutput){
        infileOutput = infile;
        delimiterOutput = delimiter;
        ignoreHeaderOutput = ignoreHeader;
    }
    void getStrategyParameters(int &stratChoiceOut, int &movingAverageLengthOut, float &commissionOut) {
        stratChoiceOut = strategyMenuChoice;
        movingAverageLengthOut = movingAverageLength;
        commissionOut = strategyMenuCommission;
    }
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
void printHeader()
{
   cout << " $$$$$$\\ $$\\                      $$$$$$$$\\                    $$\\                 $$$$$$\\                     $$\\                                  " << endl
        << "$$  __$$\\$$ |                     \\__$$  __|                   $$ |               $$  __$$\\                    $$ |                                    " << endl 
        << "$$ /  $$ $$ |$$$$$$\\  $$$$$$\\        $$ |$$$$$$\\ $$$$$$\\  $$$$$$$ |$$$$$$\\        $$ /  \\__$$\\   $$\\ $$$$$$$\\$$$$$$\\   $$$$$$\\ $$$$$$\\$$$$\\  " << endl
        << "$$$$$$$$ $$ $$  __$$\\$$  __$$\\$$$$$$\\$$ $$  __$$\\\\____$$\\$$  __$$ $$  __$$\\       \\$$$$$$\\ $$ |  $$ $$  _____\\_$$  _| $$  __$$\\$$  _$$  _$$\\  " << endl
        << "$$  __$$ $$ $$ /  $$ $$ /  $$ \\______$$ $$ |  \\__$$$$$$$ $$ /  $$ $$$$$$$$ |       \\____$$\\$$ |  $$ \\$$$$$$\\   $$ |   $$$$$$$$ $$ / $$ / $$ |       " << endl
        << "$$ |  $$ $$ $$ |  $$ $$ |  $$ |      $$ $$ |    $$  __$$ $$ |  $$ $$   ____|      $$\\   $$ $$ |  $$ |\\____$$\\  $$ |$$\\$$   ____$$ | $$ | $$ |         " << endl
        << "$$ |  $$ $$ \\$$$$$$$ \\$$$$$$  |      $$ $$ |    \\$$$$$$$ \\$$$$$$$ \\$$$$$$$\\       \\$$$$$$  \\$$$$$$$ $$$$$$$  | \\$$$$  \\$$$$$$$\\$$ | $$ | $$ |  " << endl
        << "\\__|  \\__\\__|\\____$$ |\\______/       \\__\\__|     \\_______|\\_______|\\_______|       \\______/ \\____$$ \\_______/  \\____/ \\_______\\__| \\__| \\__| " << endl
        << "            $$\\   $$ |                                                                     $$\\   $$ |                                       " << endl 
        << "            \\$$$$$$  |                                                                     \\$$$$$$  |                                        " << endl
        << "             \\______/                                                                       \\______/                                         " << endl
        << endl;
}

    void printMenuInputFile(){
      //  cout << TITLE << endl;
        printHeader();
        cout << "Load input CSV file"   << endl;
        cout << "Name of input file"  << endl;
        cout << endl;
    }
    void printMenuStrategy(){
      //  cout << TITLE << endl;
        printHeader();
        cout << "Select strategy to use"         << endl;
        cout << "1. Price Cross Moving Average"  << endl;
        cout << "2. Double Moving Average Cross" << endl;
        cout << "3. ..."                         << endl;
        cout << "4. ..."                         << endl;
        cout << "5. ..."                         << endl;
        cout << "0. Back"                        << endl;
        cout << endl;
    }
    void printMenuStrategyParamters(){
   //     cout << TITLE << endl;
        printHeader();
        cout << "Configure Strategy Parameters"         << endl;
        cout << "1. Moving average Length (current="<<movingAverageLength<<")" << endl;
        cout << "2. Commission for orders (current=$"<<strategyMenuCommission<<")" << endl;
        cout << "3. ..."                                << endl;
        cout << "4. ..."                                << endl;
        cout << "0. Back"                               << endl;
        cout << endl;
    }
    void printMenuMain(){
      //  cout << TITLE << endl;
        printHeader();
        cout << "Select an option."     << endl;
        if(fileLoaded){
            cout << "1. Set input file (File successfully loaded)" << endl;
        }
        else{
            cout << "1. Set input file (Input file not specified OR file failed to load)" << endl; 
        }
        cout << "2. Load account"       << endl;
        cout << "3. Create new account" << endl;
        if(accountLoaded && fileLoaded)
            cout << "4. Setup strategy " << endl;
        if(stratLoaded)
            cout << "5. Start strategy" << endl;
        cout << "0. Exit"               << endl;
        cout << endl;
    }
    void printMenuLoadAccount(){
        // need to pass in account list loaded from file beforehand.
    //    cout << TITLE << endl;
        printHeader();
        cout << "Select an option."     << endl;
        cout << "1. Account 1, etc etc" << endl;
        cout << "0. Back"               << endl;
        cout << endl;
    }

    void exitProgram() { exit(0); } //probably not good

    menuAction_t runMenuMain(){
        MENUSTART:
        clear_screen();
        printMenuMain();
        int choice = getInput<int>();
        clear_screen();
        switch(choice){
            case 1:
                runSubmenuInputFile();
                break;
            case 2:
                //runSubmenuLoadAccount();
                printMenuLoadAccount();
                getInput<int>();
                accountLoaded = true;
                break;
            case 3:
                //runSubmenuCreateAccount();
                break;
            case 4:
                runSubmenuSelectStrategy();
                break;
            case 5:
                currentSelectedAction = runStrategy;
                break;
            case 0: exitProgram();
        }
        //after menus done, check if user has selected to start some action (only 1 so far)
        switch(currentSelectedAction){
            case runStrategy:
                return runStrategy;
            default:
                goto MENUSTART;
        }
    }

    void runSubmenuInputFile(){
        printMenuInputFile();
        infile = getInput<std::string>();
        // this is the point where I gave up making it all modular
        cout << "Change delimiter? (default=',') \nY/N: ";
        char choice = getInput<char>(); //call setDelimiter after

        switch (choice) {
            case 'y':
            case 'Y':
                cout << "Enter custom delimiter: \n";
                delimiter = getInput<char>();
        }

        cout << "Skip first header row? (default='Y') \nY/N: ";
        choice = getInput<char>();
        switch (choice) {
            case 'n':
            case 'N':
                ignoreHeader = false;
        }
        clear_screen();
        
        std::fstream fIn;
        fIn.open(infile);

        if (!fIn){
           fileLoaded = false;
           fIn.close();
           fIn.clear();
        }
        else{
           fileLoaded = true;
           fIn.close();
           fIn.clear();
        }
    }
    void runSubmenuSelectStrategy(){
        printMenuStrategy();
        int choice = getInput<int>();
        stratLoaded = true;
        switch (choice) {
            case '1':
                strategyMenuChoice = choice; //there's got to be a better way
                break;
            default:
                cout << "ay, yu chose a strat" << endl;
        }
        clear_screen();

        printMenuStrategyParamters();
        choice = getInput<int>();
        switch (choice){
            case 1:
                cout << "Change moving average length (default=25)";
                movingAverageLength = getInput<int>(1,9999); // todo: write another overloaded with only minvalue
                break;
            case 2:
                cout << "Change commission rate per order (default=$0)";
                strategyMenuCommission = getInput<float>(0,9999);
                break;
        }
        clear_screen();
        printMenuStrategyParamters();

    }
};
#endif //TRADERCS4398_MENUS_H
