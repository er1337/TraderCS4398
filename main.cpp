#include <iostream>
#include <vector>
#include "Bar.h"
#include "smaCross.h"
#include "Menus.h"
#include "processCSV.h"
#include "StrategyRunner.h"
#include <fstream>
#include <cstdlib>

using namespace std;

const int MAX_OPTIONS = 6,
          EXIT_PROG = -999;

void printHeader();
void printMainMenu(bool, string);
void clear_console();

int main() {
    #ifdef WINDOWS
        std::system("title Trader");
    #endif

/* FIXME -- fixing the menu system, need to make it more readable
    Menus menusystem;
    menuAction_t menuAction = menusystem.runMenuMain();

    string infile;
    char delimiter;
    bool ignoreHeader;
    menusystem.getCSVparameters(infile, delimiter, ignoreHeader);

    processCSV parser;
    parser.setPath(infile);
    parser.setDelimiter(delimiter);
    parser.setIgnoreHeader(ignoreHeader);
    vector<Bar> series;
    series = parser.returnBarVector();

    int strategychoice;
    float commission;
    int movingavglength;
    menusystem.getStrategyParameters(strategychoice, movingavglength, commission);

    switch (menuAction){
        case runStrategy:
            cout << "running strategy...\n";
            //dont cram all this in here
            Stock s;
            map<string, Stock> m = {{"STOK", s}};
            Account a ("JP Morgan", 1000, m);
            vector<signal_t> orderSignals = strat::smaCross(series, movingavglength);

            StrategyRunner sr(&a, series, orderSignals, commission);
            sr.runStrategy();
//            cout << "\n\n\n===============================" <<endl;
//            cout << "Initial Balance: "<< a.getInitBalance() <<endl;
//            cout << "Final Balance: "<< a.getBalance() <<endl;
//            cout << "Profit %: "<< int((a.getBalance() / a.getInitBalance())*100) <<endl;
//            cin.get();
            break;
    }
*/


    bool isAccountLoaded = false,
         isFileLoaded = false,
         isStratLoaded = false,
         ignoreFirstRow = true,
         changeParameter = true;
   
    string inputFile = "file has not been loaded yet!";
  
    char delimiter = ',',
         query,
         exitQuery,
         garbageQuery;
  
    int choice,
        stratQuery,
        movingAvgLength = 25,
        commission = 0;
  
    vector<Bar> series;
    Stock s;
    processCSV parser;
    ifstream fIn;

    do{
         clear_console();
         printHeader();
         printMainMenu(isFileLoaded, inputFile);
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
            case 2: // Load Account here
                  isAccountLoaded = true;
                  break;
            case 3: // Create Account here
                  cout << "NEED TO FIX THIS" << endl;
                  break;
            case 4: // Setup Strategy
                  printHeader(); 
                  cout << "~Strategy Selection~" << endl
                       << "Select a strategy below:" << endl
                       << "1. Price Cross Moving Average" << endl
                       << "2. Double Moving Average Cross" << endl
                       << "INSERT MORE STRATS HERE ..." << endl;
                  cout << "Enter option (#1-2): ";
                  cin >> stratQuery; //FIXME not being used ...
                
               // FIXME switch statement determining strategy???
                  isStratLoaded = true;
                  changeParameter = true;
                  clear_console();
                  printHeader(); 
                  while (changeParameter){
                     cout << "\n~Configure Strategy Parameters~" << endl
                          << "1. Moving Average Length (current = "<< movingAvgLength << ")" << endl
                          << "2. Order Commission (current = $" << commission << ")" << endl
                          << "3. Return to Main Menu (accept current parameters)" << endl;
                     cout << "Enter option (#1-3): "; 
                    
                     cin >> stratQuery;
                     switch(stratQuery){
                        case 1:
                              cout << "\nEnter a new value for the moving average length: ";
                              cin >> movingAvgLength;
                              cout << "Moving Average Length has been changed to " << movingAvgLength << endl;
                              break;
                        case 2:
                              cout << "\nEnter new value for order commission: ";
                              cin >> commission;
                              cout << "Order commission has been changed to $" << commission << endl;
                              break;
                        case 3:
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
            case 5: // Start Strategy
                  printHeader();
                  if (isAccountLoaded && isFileLoaded && isStratLoaded){
                      cout << "Analyzing financial instrument using the selected strategy ..." << endl;
                      map<string, Stock> m = {{"STOCK", s}};
                      Account a ("JP Morgan", 1000, m);
                      vector<signal_t> orderSignals = strat::smaCross(series, movingAvgLength);

                      StrategyRunner sr(&a, series, orderSignals, commission);
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

                      if (!isAccountLoaded){
                         cout << "\t-An account has not been loaded. Please return to the main menu and load an account" << endl; 
                      }
                      
                      if (!isStratLoaded){
                         cout << "\t-A strategy has not been loaded. Please return to the main menu and load a strategy" << endl;
                      }

                      cout << "Please fix the aforementioned deficiencies before attempting to execute a strategy." << endl
                           << "Press any character on your keyboard and press enter/return to go back to the main menu..." << endl;
                      cin >> garbageQuery;
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
      }
   }while(choice != EXIT_PROG);
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

void printMainMenu(bool status, string file)
{
   cout << "~Main Menu~" << endl
        << "Please select an option below:" << endl
        << "1. Specify Input File (";
   if (status){
      cout << "Successfully loaded: " << file << ")" << endl;
   }
   else{
      cout << "ERROR: " << file << ")" << endl;
   }
   cout << "2. Load Account" << endl
        << "3. Create Account" << endl
        << "4. Setup Strategy" << endl
        << "5. Start Strategy" << endl
        << "6. Exit Algo-Trade System" << endl
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
