/*

#ifndef TRADERCS4398_CSVTOVECTOR_H
#define TRADERCS4398_CSVTOVECTOR_H

#include "Bar.h"
#include <vector>
#include "libcsv_parser++-1.0.0/include/csv_parser/csv_parser.hpp"

vector<Bar> csvToVector(char* csvFile){
    csvFile = "BAC.csv";    //remove later
    //initial parameters depend on input csv format
    csv_parser parser;
    parser.set_skip_lines(1);       // skip the first header line
    parser.set_enclosed_char('', ENCLOSURE_NONE);
    unsigned int row_count = 1u;
    if (parser.init(csvFile)) {
        while(parser.has_more_rows())
        {
            unsigned int i = 0;

            */
/* Get the record *//*

            csv_row row = parser.get_row();

            */
/* Print out each column in the row *//*

            for (i = 0; i < row.size(); i++)
            {
                printf("COLUMN %02d : %s\n", i + 1U, row[i].c_str());
            }

            printf("====================================================================\n");
            printf("END OF ROW %02d\n", row_count);
            printf("====================================================================\n");

            row_count++;
        }

        vector<Bar> series;

        return series;

    }
    else return nullptr;
}

#endif //TRADERCS4398_CSVTOVECTOR_H
*/
