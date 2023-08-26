#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>

#include "analogRead.h"
#include "config.h"
#include "max72xx.h"
#include "millis.h"
#include "uart.h"
#include "display.h"
#include "letters.h"

void initDemo();
uint8_t getDigit(uint16_t num);

int main()
{
    initDemo();
    clearScreen();
    uint8_t currentCapitalLetter[CAPITAL_LETTER_SIZE];
    uint8_t currentSmallLetter[SMALL_LETTER_HEIGHT];
    volatile millis_t timeAtLastDirectionChange = millis_get();
    volatile millis_t timeAtLastAnalogRead = millis_get();
    bool changedJoystickDirection = true;
    uint8_t analogCoordinates[2] = {3, 3};
    uint8_t horizontalDigits[4] = {0,0,0,0};
    uint8_t verticalDigits[4] = {0,0,0,0};
    uint8_t offset = 0;

    for(uint8_t i = 0; i < SMALL_LETTER_HEIGHT; i++)
    {
        currentSmallLetter[i] = getSmallLetter(17, i);
    }

    for(uint8_t i = 0; i < CAPITAL_LETTER_SIZE; i++)
    {
        currentCapitalLetter[i] = getCapitalLetter(11, i);
    }


    while(1)
    {
        int16_t horizontalMove = analogRead(JOYSTICK_HORIZONTAL);
        int16_t verticalMove = analogRead(JOYSTICK_VERTICAL);

        if(millis_get() - timeAtLastAnalogRead > TIME_BETWEEN_MOVES)
        {

            max7219b_clr(analogCoordinates[0], analogCoordinates[1]);
            analogCoordinates[0] = (MAX_COLUMNS / 2) + 6 -setCoordinate(horizontalMove);
            analogCoordinates[1] = MAX_ROWS - setCoordinate(verticalMove) - 2;
            max7219b_set(analogCoordinates[0], analogCoordinates[1]);
            max7219b_out();

            offset = 0;
            int16_t analogHorizontal = horizontalMove;
            int16_t analogVertical = verticalMove;
            // For each horizontal number
            for(uint8_t i = 0; i < 4; i++)
            {
                // For each horizontal digit
                for(uint8_t j = 0; j < 4; j++)
                {
                    currentSmallLetter[j] = getSmallLetter(horizontalDigits[j], j);
                    undoLetter(currentSmallLetter, 0, offset, SMALL_LETTER_HEIGHT, SMALL_LETTER_WIDTH);
                    offset = offset + SMALL_LETTER_WIDTH;
                }

                offset = 0;

                // For each vertical digit
                for(uint8_t j = 0; j < 4; j++)
                {
                    currentSmallLetter[j] = getSmallLetter(verticalDigits[j], j);
                    undoLetter(currentSmallLetter, 0, offset, SMALL_LETTER_HEIGHT, SMALL_LETTER_WIDTH);
                    offset = offset + SMALL_LETTER_WIDTH;
                }
            }


            for(uint8_t i; i < 4; i++)
            {
                verticalDigits[i] = getDigit(analogVertical);
                analogVertical = analogVertical / 10;
            }
            for(uint8_t i; i < 4; i++)
            {
                horizontalDigits[i] = getDigit(analogHorizontal);
                analogHorizontal = analogHorizontal / 10;
            }

            // For each horizontal number
            for(uint8_t i = 0; i < 4; i++)
            {
                // For each horizontal digit
                for(uint8_t j = 0; j < 4; j++)
                {
                    currentSmallLetter[j] = getSmallLetter(horizontalDigits[j], j);
                    setLetter(currentSmallLetter, 0, offset, SMALL_LETTER_HEIGHT, SMALL_LETTER_WIDTH);
                    offset = offset + SMALL_LETTER_WIDTH;
                }
                // For each vertical digit
                for(uint8_t j = 0; j < 4; j++)
                {
                    currentSmallLetter[j] = getSmallLetter(verticalDigits[j], j);
                    setLetter(currentSmallLetter, 0, offset, SMALL_LETTER_HEIGHT, SMALL_LETTER_WIDTH);
                    offset = offset + SMALL_LETTER_WIDTH;
                }
            }

            timeAtLastAnalogRead = millis_get();
            // max7219b_out();
        }
    }

    return 0;
}

void initDemo()
{
    // Set up joystick
    BIT_CLEAR(DDRD, JOYSTICK_BUTTON);
    BIT_SET(PIND, JOYSTICK_BUTTON);
    BIT_CLEAR(DDRC, JOYSTICK_VERTICAL);
    BIT_CLEAR(DDRC, JOYSTICK_HORIZONTAL);

    // Set up serial, display and millis
    init_serial();
	max7219_init();
    millis_init();
    sei();

    // Clear screen in preparation for demo
    clearScreen();
    _delay_ms(75);
}

uint8_t getDigit(uint16_t num)
{
    return num % 10;
}

/*
OLD CODE, USED TO DISPLAY A MARKER ON THE DISPLAY TO MESURE POSITION OF JOYSTICK
Put it in main to get it working.
        if(millis_get() - timeAtLastAnalogRead > TIME_BETWEEN_MOVES)
        {
            max7219b_clr(analogCoordinates[0], analogCoordinates[1]);
            analogCoordinates[0] = (MAX_COLUMNS / 2) + 6 -setCoordinate(horizontalMove);
            analogCoordinates[1] = MAX_ROWS - setCoordinate(verticalMove) - 2;
            max7219b_set(analogCoordinates[0], analogCoordinates[1]);
            max7219b_out();
        }
*/