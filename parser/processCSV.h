/*
 
   FILE: processCSV.cpp
   
   Darren Rambaud
   July 25, 2016
 
   The header file for processCSV class.
   
   CONSTANTS
     None

   

   
 */

#ifndef PROCESS_CSV_H
#define PROCESS_CSV_H

#include <iostream>
#include <string>
#include <vector>

typedef struct bar{ 
   std::string date; 
   float open, 
         high, 
         low, 
         close; 
   unsigned int volume; 
} bar;

class processCSV{
   private:
      std::vector<std::string> p_data;
//      char delimiter = ','; // FIXME - gives a warning when compiling ..
   public:
//      void setDelimiter(char delimiter);
      std::string const& operator[](std::size_t index) const;
      std::size_t size() const;
      void readNextRow(std::istream& str);
      float conv_float(const std::string& s);
      int conv_int(const std::string& s);
      std::vector<bar> returnBarVector(const std::string& path);
};

//std::istream& operator>>(std::istream str, processCSV& data);

#endif
