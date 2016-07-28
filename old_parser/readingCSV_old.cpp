#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "../Bar.h"

class processCSV {
public:
    void setDelimiter(char delimiter) { this->delimiter = delimiter; }

    float conv_float(const std::string &s) {
        //std::stringstream ss(s);
        //float convert;
        //ss >> convert;
        //return convert;
        return stof(s);
    }

    float conv_int(const std::string &s) {
        std::stringstream ss(s);
        int convert;
        ss >> convert;
        return convert;
    }

    std::string const &operator[](std::size_t index) const {
        return m_data[index];
    }

    std::size_t size() const {
        return m_data.size();
    }

    void readNextRow(std::istream &str) {
        std::string line;
        std::getline(str, line);

        std::stringstream lineStream(line);
        std::string cell;

        m_data.clear();
        while (std::getline(lineStream, cell, ',')) {
            m_data.push_back(cell);
        }
    }

private:
    std::vector<std::string> m_data;
    char delimiter = ',';
};

std::istream &operator>>(std::istream &str, processCSV &data) {
    data.readNextRow(str);
    return str;
}

#include "typeinfo"
int main() {
    Bar temp;
    std::vector<Bar> actual;

    std::ifstream file("../csvMSFT.csv"); // FIXME -- change this so that this is the
                                    // accepting value
    // FIXME -- insert assert here to check if file opens on success/fail? ?
    processCSV row;
    int counter = 0;
    bool ignoreHeader = true;
    //temp.push_back(Bar);
    while (file >> row) {
        if (counter == 0 && ignoreHeader) {
            ignoreHeader = false;
            continue;
        }
        temp.date   = row[0]; //write date string to char[] in Bar
        temp.open   = row.conv_float(row[1]);
        temp.high   = row.conv_float(row[2]);
        temp.low    = row.conv_float(row[3]);
        temp.close  = row.conv_float(row[4]);
        temp.volume = row.conv_int(row[5]);
        actual.push_back(temp);  //push this Bar into vector<Bar>

    }

    std::cout << std::endl;

}
