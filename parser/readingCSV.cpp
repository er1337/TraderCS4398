#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

class processCSV
{
    public:
        float conv_float(const std::string& s){
           std::stringstream ss(s);
           float convert;
           ss >> convert;
           return convert;
        }
        float conv_int(const std::string& s){
           std::stringstream ss(s);
           int convert;
           ss >> convert;
           return convert;
        }
        std::string const& operator[](std::size_t index) const
        {
            return m_data[index];
        }
        std::size_t size() const
        {
            return m_data.size();
        }
        void readNextRow(std::istream& str)
        {
            std::string line;
            std::getline(str, line);

            std::stringstream lineStream(line);
            std::string cell;

            m_data.clear();
            while(std::getline(lineStream, cell, ','))
            {
                m_data.push_back(cell);
            }
        }
    private:
        std::vector<std::string> m_data;
};

std::istream& operator>>(std::istream& str, CSVRow& data)
{
    data.readNextRow(str);
    return str;
}  

typedef struct bar{
	std::string date;
	float open,
              high,
              low,
              close,
              adj_close;
         int volume;
} bar;

std::vector<bar> temp;
std::vector<std::vector<bar> > actual;

int main()
{
    std::ifstream file("BAC.csv"); // FIXME -- change this so that this is the
                                   // accepting value
    // FIXME -- insert assert here to check if file opens on success/fail? ?
    processCSV row;
 int counter = 0;
 bool ignore = true;
temp.push_back(bar());
    while(file >> row)
    {
      if(counter == 0 && ignore){
          ignore = false;
          continue;
       } 
       temp[counter].date = row[0]; //pushing date to temp struct vector
       temp[counter].open = row.conv_float(row[1]); // pushing open ""
       temp[counter].high = row.conv_float(row[2]); // pushing high ""
       temp[counter].low = row.conv_float(row[3]);  // pushing low ""
       temp[counter].close = row.conv_float(row[4]); // pushing close ""
       temp[counter].volume = row.conv_int(row[5]); // pushing volume ""
       temp[counter].adj_close = row.conv_float(row[6]); // pushing adj_close ""
       // the temp struct vector has been filled with the first row of
       // of data from the comma separated value file, now we need to
       // push the temp data onto the vector that will be manipulated 
       actual.push_back(temp);
    }
//FIXME --> testing access...
std::cout << std::endl;
std::cout << actual[0][0].date << std::endl;
std::cout << actual[1][0].date << std::endl;
std::cout << actual[1420][0].date << std::endl;
std::cout << actual[1635][0].date << std::endl;

std::cout << actual[0][0].open << std::endl;
}
