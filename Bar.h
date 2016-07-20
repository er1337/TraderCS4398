//
// Created by Owner on 7/19/2016.
//

#ifndef TRADERCS4398_BAR_H
#define TRADERCS4398_BAR_H

typedef struct Bar{
    char* date[20];
    float open, high, low, close;
    int volume;
} Bar;

#endif //TRADERCS4398_BAR_H
