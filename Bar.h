//
// Created by Owner on 7/19/2016.
//

#ifndef TRADERCS4398_BAR_H
#define TRADERCS4398_BAR_H

#include <string>

typedef struct Bar{
    std::string date;
    float open, high, low, close;
    unsigned int volume;
} Bar;

// cout << bar
//std::ostream &operator<<(std::ostream &str, const Bar &bar) {
//    str << bar.date << "\tO:" << bar.open << "\tH:" << bar.high << "\tL:"
//        << bar.low << "\tC:" << bar.close << "\tV:" << bar.volume;
//}
#endif //TRADERCS4398_BAR_H
