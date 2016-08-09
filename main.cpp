#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "Bar.h"
#include "smaCross.h"
#include "emaCross.h"
#include "doubleEmaCross.h"
#include "doubleSmaCross.h"
#include "Menus.h"
#include "processCSV.h"
#include "StrategyRunner.h"

using namespace std;

const int MAX_OPTIONS = 5,
          EXIT_PROG = -999,
          STRAT_NOT_SEL = 0,
          SIMPLE_MOVING_AVG = 1,
          DOUBLE_MOVING_AVG = 2,
          DOUBLE_EXP_MOVING_AVG = 3,
          EXP_MOVING_AVG = 4;

void printHeader();
void printMainMenu(const bool, const string, const bool, Account, const int);
void clear_console();

int main() {
    #ifdef WINDOWS
        std::system("title Trader");
    #endif

    float initialBal;

    bool isAccountDetailsSet = false,
         isFileLoaded = false,
         isStratLoaded = false,
         ignoreFirstRow = true,
         changeParameter = true;
   
    string inputFile = "file has not been loaded yet!",
           accountName;
  
    char delimiter = ',',
         query,
         exitQuery,
         garbageQuery;
  
    int choice,
        stratQuery,
        movingAvgLength = 25,
        commission = 0,
        currentStrat = 0; // 0 = no valid strategy chosen

    unsigned fastLen = 1, 
             slowLen = 2;             
  
    vector<Bar> series;
    Stock s;
    processCSV parser;
    ifstream fIn;
    map<string, Stock> m = {{"STOCK", s}};
    Account account ("not-set", 0, m);
    vector<signal_t> orderSignals;

    do{
         clear_console();
         printHeader();
         printMainMenu(isFileLoaded, inputFile, isAccountDetailsSet, account, currentStrat);
         cin >> choice;
         clear_console();

         switch(choice){
            case 1: //option 1
                  printHeader();
                  cout << "~CSV Parser~" << endl
                       << "Please specify the name of the input file: ";
                  cin >> inputFile;
                  fIn.open(inputFile);
                  
                  while (!fIn){
                     cout << "Unable to open " << inputFile << endl
                          << "Please check the filename, and try again: ";
                     cin >> inputFile;
                                 
                     fIn.open(inputFile);
                  }
 
                  parser.setPath(inputFile);

                  cout << "\nDefault delimiter == '" << delimiter << "': do you want to change the delimiter?" << endl
                       << "Enter 'y' or 'n': ";
                  cin >> query;

                  switch(query){
                     case 'y':
                     case 'Y':
                             cout << "\nPlease enter a new delimiter character: ";
                             cin >> delimiter;
                             parser.setDelimiter(delimiter);
                             break;
                     case 'n':
                     case 'N':
                             break;
                  }
               
                  cout << "Default behavior is to skip the first row in the CSV file. Shall we change this behavior?" << endl
                       << "Enter 'y' or 'n': ";
                  cin >> query;

                  switch(query){
                     case 'y':
                     case 'Y':
                             ignoreFirstRow = false;
                             parser.setIgnoreHeader(ignoreFirstRow);
                             cout << "The parser will now read the entire file" << endl;
                             break;
                     case 'n':
                     case 'N':
                             break; 
                  }
                  
                  series = parser.returnBarVector();
                  isFileLoaded = true;
                  fIn.close();
                  fIn.clear();
                  break;
            case 2: // Set account details (name & balance)
                  printHeader();

                  cout << "~Specify Account Details~" << endl
                       << "Please specify a name for the account: ";
                  cin >> accountName;
                                 
                  cout << "Please set an initial balance for '" << accountName <<"': ";
                  cin >> initialBal;

                  account.setName(accountName);
                  account.setBalance(initialBal);
                  account.set_initBalance(initialBal);
                  
                  isAccountDetailsSet = true;
                  break;
            case 3: // Setup Strategy
                  printHeader(); 
                  cout << "~Strategy Selection~" << endl
                       << "Select a strategy below:" << endl
                       << "1. Simple Moving Average Cross" << endl
                       << "2. Double Moving Average Cross" << endl
                       << "3. Double Exponential Moving Average Cross" << endl
                       << "4. Exponential Moving Average Cross" << endl;
                  cout << "Enter option (#1-4): ";
                  cin >> stratQuery;
                  switch(stratQuery){
                     case 1:
                           orderSignals = strat::smaCross(series, movingAvgLength);
                           currentStrat = SIMPLE_MOVING_AVG;
                           break;
                     case 2:
                           orderSignals = strat::doubleSmaCross(series, fastLen, slowLen);
                           currentStrat = DOUBLE_MOVING_AVG;
                           break;
                     case 3:
                           orderSignals = strat::doubleEmaCross(series, fastLen, slowLen);
                           currentStrat = DOUBLE_EXP_MOVING_AVG;
                           break;
                     case 4:
                           orderSignals = strat::emaCross(series, movingAvgLength);
                           currentStrat = EXP_MOVING_AVG;
                           break;
                  }
                  isStratLoaded = true;
                  changeParameter = true;
                  clear_console();
                  printHeader(); 
                  while (changeParameter){
                     cout << "\n~Configure Strategy Parameters~" << endl
                          << "1. Moving Average Length (current = "<< movingAvgLength << ") -- applicable to SMA- & EMA-cross" << endl
                          << "2. Order Commission (current = $" << commission << ")" << endl
                          << "3. Adjust Slow Moving Average Length (current = \'" << slowLen << "\') -- applicable to double SMA- & EMA-cross" << endl
                          << "4. Adjust Fast Moving Average Length (current = \'" << fastLen << "\') -- applicable to double SMA- & EMA-cross" << endl
                          << "5. Return to Main Menu (accept current parameters)" << endl;
                     cout << "Enter option (#1-5): "; 
                    
                     cin >> stratQuery;
                     switch(stratQuery){
                        case 1:
                              cout << "\nEnter a new value for the moving average length: ";
                              cin >> movingAvgLength;
                              cout << "Moving Average Length has been changed to " << movingAvgLength << endl;
                              currentStrat == SIMPLE_MOVING_AVG ? orderSignals = strat::smaCross(series, movingAvgLength) :
                                 orderSignals = strat::emaCross(series, movingAvgLength);
                              break;
                        case 2:
                              cout << "\nEnter new value for order commission: ";
                              cin >> commission;
                              cout << "Order commission has been changed to $" << commission << endl;
                              break;
                        case 3:
                              cout << "\nEnter new value for slow moving average length: ";
                              cin >> slowLen;
                              cout << "Slow moving average has been changed to " << slowLen << endl;
                              currentStrat == DOUBLE_MOVING_AVG ? orderSignals = strat::doubleSmaCross(series, fastLen, slowLen) :
                                 orderSignals = strat::doubleEmaCross(series, fastLen, slowLen);
                              break;
                        case 4:
                               cout << "\nEnter new value for fast moving average length: ";
                               cin >> fastLen;
                               cout << "Fast moving average has been changed to " << fastLen << endl;
                               currentStrat == DOUBLE_MOVING_AVG ? orderSignals = strat::doubleSmaCross(series, fastLen, slowLen) :
                                  orderSignals = strat::doubleEmaCross(series, fastLen, slowLen);
                              break;
                        case 5:
                        default:
                              changeParameter = false;
                              break;
                     }

                     if (changeParameter){
                        cout << "Do you want to change another parameter ('y' or 'n') ? : ";
                        cin >> query;
                        switch(query){
                           case 'Y':
                           case 'y':
                                   changeParameter = true;
                                   break;
                           case 'N':
                           case 'n':
                                   changeParameter = false;
                                   break;
                        }
                     }      
                  }
                  break;
            case 4: // Start Strategy
                  printHeader();
                  if (isAccountDetailsSet && isFileLoaded && isStratLoaded){
                      cout << "Analyzing " << account.getName() << " using the selected strategy ..." << endl;

                      StrategyRunner sr(&account, series, orderSignals, commission);
                      sr.runStrategy();

                      cout << "\nThe financial instrument has been successfully processed via the selected algorithmic trade strategy!" << endl
                           << "Do you want to return to the main menu? (yes == 'y', no (will exit program) == 'n'): ";
                      cin >> exitQuery;
                 
                      switch (exitQuery){
                         case 'n':
                         case 'N':
                                 cout << "Goodbye!" << endl;
                                 choice = EXIT_PROG;
                                 break;
                         default:
                                 break;
                      }
                  }
                  else{
                      cout << "~~ERROR~~" << endl
                           << "Unable to analyze financial instrument, there exists deficiencies that require attention." << endl
                           << "The following need to be addressed before a trade strategy can be executed: " << endl;
                      if (!isFileLoaded){
                         cout << "\t-A CSV file has not been loaded. Please return to the main menu and specify an input/CSV file" << endl;
                      }

                      if (!isAccountDetailsSet){
                         cout << "\t-Account details have not been specified. Please return to the main menu" << endl; 
                      }
                      
                      if (!isStratLoaded){
                         cout << "\t-A strategy has not been loaded. Please return to the main menu and load a strategy" << endl;
                      }

                      cout << "Please fix the aforementioned deficiencies before attempting to execute a strategy." << endl
                           << "Press any character on your keyboard and press enter/return to go back to the main menu..." << endl;
                      cin >> garbageQuery;
                  }
                  break;
            case MAX_OPTIONS:
                  printHeader();
                  cout << "Are you sure you want to exit?" << endl
                       << "Enter 'y' or 'n': ";
                  cin >> exitQuery;
                 
                  switch (exitQuery){
                     case 'y':
                     case 'Y':
                             cout << "Goodbye!" << endl;
                             choice = EXIT_PROG;
                             break;
                     default:
                             break;
                  }
                  break;  
         } // end switch statement
   }while (choice != EXIT_PROG);
   return 0;
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

void printMainMenu(const bool status, const string file, const bool details, Account acc, const int strat)
{
   cout << "~Main Menu~" << endl
        << "Please select an option below:" << endl
        << "1. Specify Input File (";
   status ? 
     cout << "Successfully loaded: " << file << ")" << endl : 
     cout << "ERROR: " << file << ")" << endl;
   cout << "2. Set Account Details ";
   details ? 
     cout << "(\'" << acc.getName() << "\' has a balance of $" << acc.getBalance() << ")" << endl : 
     cout << "(ERROR: account set up has not been completed!)" << endl;
   cout << "3. Setup Strategy ";
   if (strat == STRAT_NOT_SEL){
      cout << "(ERROR: strategy has not been selected)" << endl;
   }
   else if (strat == SIMPLE_MOVING_AVG){
      cout << "(Strategy: \'Simple Moving Average\')" << endl;
   }
   else if (strat == DOUBLE_MOVING_AVG){
      cout << "(Strategy: \'Double Moving Average\')" << endl;
   }
   else if (strat == DOUBLE_EXP_MOVING_AVG){
      cout << "(Strategy: \'Double Exponential Moving Average\')" << endl;
   }
   else if (strat == EXP_MOVING_AVG){
      cout << "(Strategy: \'Exponential Moving Average\')" << endl;
   }
   else{
     cout << "(ERROR: strategy has not been selected)" << endl;
   }
   cout << "4. Start Strategy" << endl
        << "5. Exit Algo-Trade System" << endl
        << "Enter (#1-" << MAX_OPTIONS << "): ";
}

void clear_console()
{
   #ifdef WINDOWS
     std::system("cls");
   #else
     std::system("clear");
   #endif
}
