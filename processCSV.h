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

#include "Bar.h"
#include <iostream>
#include <string>
#include <vector>

class processCSV{
   private:
      std::vector<std::string> p_data;
      std::string path;
      char delimiter;
      bool ignore;
   public:
      processCSV();
      void setIgnore(bool ignore);
      void setPath(std::string path);
      void setDelimiter(char delimiter);
      std::string const& operator[](std::size_t index) const;
      std::size_t size() const;
      void readNextRow(std::istream& str);
      float conv_float(const std::string& s);
      int conv_int(const std::string& s);
      std::vector<Bar> returnBarVector();
};

//std::istream& operator>>(std::istream str, processCSV& data);

#endif
