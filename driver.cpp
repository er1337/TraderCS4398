#include "processCSV.h"

int main()
{
   processCSV test;
   std::vector<Bar> data;
   test.setPath("csvAAPL.csv");
//   test.setIgnore(false); -- it works!
//   test.setDelimiter('\t');
   data = test.returnBarVector();

   std::cout << "Compare to line 1 on the CSV worksheet ...\n" << std::endl;

   std::cout << data[0].date << std::endl;   
   std::cout << data[0].open << std::endl;
   std::cout << data[0].high << std::endl;
   std::cout << data[0].low << std::endl;
   std::cout << data[0].close << std::endl;
   std::cout << data[0].volume << std::endl;
   
   std::cout << "Compare \"\" line 2 \"\" ...\n" << std::endl;

   std::cout << data[1].date << std::endl;
   std::cout << data[1].open << std::endl;
   std::cout << data[1].high << std::endl;
   std::cout << data[1].low << std::endl;
   std::cout << data[1].close << std::endl;
   std::cout << data[1].volume << std::endl;
   return 0;
}
