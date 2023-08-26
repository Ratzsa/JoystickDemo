#include <stdio.h>
#include <stdint.h>
#include "config.h"

void clearScreen()
{
    for(int x = 0; x < MAX_COLUMNS; x++)
    {
        for(int y = 0; y < MAX_ROWS; y++)
        {
            max7219b_clr(x, y);
            max7219b_out();
        }
    }
}

void undoLetter(uint8_t *letter, uint8_t startX, uint8_t offset, uint8_t letterHeight, uint8_t letterWidth)
{
    for(uint8_t row = 0; row < letterHeight; row++)
    {
        uint8_t todo = letter[row];
        for(uint8_t col = 0; col < letterWidth; col++)
        {
            if(BIT_CHECK(todo, col))
            {
                int8_t column = (letterWidth - col) - startX;
                // if((column + offset) < 0)
                // {
                //     column = MAX_COLUMNS + column;
                // }
                max7219b_clr((column + offset), row);
            }
        }
    }
}

void setLetter(uint8_t *letter, uint8_t startX, uint8_t offset, uint8_t letterHeight, uint8_t letterWidth)
{
    for(uint8_t row = 0; row < letterHeight; row++)
    {
        uint8_t todo = letter[row];
        for(uint8_t col = 0; col < letterWidth; col++)
        {
            if(BIT_CHECK(todo, col))
            {
                int8_t column = (letterWidth - col) - startX;
                // if((column + offset) < 0)
                // {
                //     column = MAX_COLUMNS + column;
                // }
                max7219b_set((column + offset), row);
            }
        }
    }
    max7219b_out();
}

uint8_t setCoordinate(int16_t axisValue)
{
    if(axisValue > 952) return 0;
    else if(axisValue > 812) return 1;
    else if(axisValue > 662) return 2;
    else if(axisValue > 372) return 3;
    else if(axisValue > 222) return 4;
    else if(axisValue > 72) return 5;
    else return 6;
}