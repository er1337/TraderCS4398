/*

  FILE: processCSV.cpp
   
   Darren Rambaud
   July 25, 2016

   The implementation file for processCSV.cpp. The following lines of code
   process a Comma Separated Value (CSV) file.
 
   INVARIANT for processCSV class:
   (1) Values (strings, floats, integers) are imported/parsed from a CSV file
       into a 1D vector of struct objects
   (2) The initial header line of the CSV file can be ignored.

*/

#include "processCSV.h"
#include <iterator>
#include <fstream>
#include <sstream>

// processCSV: when instantiated, processCSV will automatically declare the
//             private variables. These values will be referred to as the
//             default values
// 
// returns nothing
processCSV::processCSV() : path("not-set"), delimiter(','), ignore(true)
{
}
 
// setIgnoreHeader: this is a setter, when invoked it is able to change the
//                  value of bool ignore
// ignore: is a boolean value
// 
// returns nothing
void processCSV::setIgnoreHeader(bool ignore)
{
   this->ignore = ignore;
}

// setPath: this is a setter, when invoke it is able to change the value of
//          of string path
// 
// path: is a string value
//
// returns nothing
void processCSV::setPath(std::string path)
{
   this->path = path;
}

// setDelimiter: this is a setter which is able to modifies the class's
//               delimiter. The default value is the comma (',')
//
// delimiter: is a char value
//
// returns nothing
void processCSV::setDelimiter(char delimiter)
{
   this->delimiter = delimiter;
}

// operator[]: this function overrides the [] operator for this class
//             which returns the index of the data contained within
//             the vector
//  
// returns the data contained within p_data[index]
std::string const& processCSV::operator[](std::size_t index) const
{
   return p_data[index];
}

// size: returns the size of the vector
// 
// returns size_t p_data.size()
std::size_t processCSV::size() const
{
   return p_data.size();
}
   
// readNextRow: reads in each line of the CSV file using getline and push_backs
//              each cell into the vector
//
// returns nothing
void processCSV::readNextRow(std::istream& str)
{
   std::string row;
   std::getline(str, row);

   std::stringstream lineStream(row);
   std::string cell;

   p_data.clear();
           
   while(std::getline(lineStream, cell, this->delimiter)){
      p_data.push_back(cell);
   }
}

// conv_float: converts the string values into float representation using
//             stringstream
// 
// returns convert (a float)
float processCSV::conv_float(const std::string& s)
{
   std::stringstream ss(s);
   float convert;
        
   ss >> convert;
   return convert;
}
   
// conv_int: converts the string value passed into the function to an int using
//           stringstream
//
// s: a string
//
// returns convert (an int)
int processCSV::conv_int(const std::string& s)
{
   std::stringstream ss(s);
   int convert;
 
   ss >> convert;
   return convert;
}

// operator>>: overloads the functionality of >> operator such that 
//             the passed in data invokes readNextRow and returns the
//             str after processing with readNextRow
//
// str: istream&
// data: processCSV object
std::istream& operator>>(std::istream& str, processCSV& data)
{
   data.readNextRow(str);
   return str;
}  

// returnBarVector: when invoked, the function begins the processing of a CSV
//                  file using the given parameters defined in the processCSV
//                  class (bool, char, string). A valid path must be set before
//                  processing begins.
// 
// returns actual (a vector object)
std::vector<Bar> processCSV::returnBarVector()
{ //previously (const std::string& path)

   Bar temp;
   std::vector<Bar> actual;

   std::ifstream file(path);
   if (!file){
      std::cerr << "ERROR: Unable to open file " << path << std::endl;
      std::exit(-1);
   }

   processCSV row;
   int counter = 0;
   
    while(file >> row){
       if (counter == 0 && ignore){// ignoring the header line of the .csv file
          ignore = false;
          continue;
       }

       temp.date = row[0]; //pushing data to temp struct
       temp.open = row.conv_float(row[1]);
       temp.high = row.conv_float(row[2]);
       temp.low = row.conv_float(row[3]); 
       temp.close = row.conv_float(row[4]);
       temp.volume = row.conv_int(row[5]);

       actual.push_back(temp);
    }
    
    return actual;
}
