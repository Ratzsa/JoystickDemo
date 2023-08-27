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
    volatile uint8_t horizontalDigits[4] = { 4, 3, 2, 1};
    volatile uint8_t verticalDigits[4] = { 1, 2, 3, 4};
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
        volatile int16_t analogHorizontal = analogRead(JOYSTICK_HORIZONTAL);
        volatile int16_t analogVertical = analogRead(JOYSTICK_VERTICAL);

        if(millis_get() - timeAtLastAnalogRead > TIME_BETWEEN_MOVES)
        {

            /* Use code to display a little dot that moves with the joystick. It is very adorable.
            max7219b_clr(analogCoordinates[0], analogCoordinates[1]);
            analogCoordinates[0] = (MAX_COLUMNS / 2) + 6 -setCoordinate(analogHorizontal);
            analogCoordinates[1] = MAX_ROWS - setCoordinate(analogVertical) - 2;
            max7219b_set(analogCoordinates[0], analogCoordinates[1]);
            max7219b_out();
            */


            offset = 0;

            for(uint8_t i = 0; i < 4; i++)
            {
                verticalDigits[3 - i] = getDigit(analogVertical);
                analogVertical = analogVertical / 10;
            }
            for(uint8_t i = 0; i < 4; i++)
            {
                horizontalDigits[3 - i] = getDigit(analogHorizontal);
                analogHorizontal = analogHorizontal / 10;
            }

            // For each horizontal number
            for(uint8_t i = 0; i < 4; i++)
            {
                // For each horizontal digit
                for(uint8_t j = 0; j < SMALL_LETTER_HEIGHT; j++)
                {
                    currentSmallLetter[j] = getSmallLetter(horizontalDigits[i], j);
                }
                setLetter(currentSmallLetter, 0, offset, SMALL_LETTER_HEIGHT, SMALL_LETTER_WIDTH);
                offset = offset + SMALL_LETTER_WIDTH + 1;
            }

            // For each vertical number
            for(uint8_t i = 0; i < 4; i++)
            {
                // For each vertical digit
                for(uint8_t j = 0; j < SMALL_LETTER_HEIGHT; j++)
                {
                    currentSmallLetter[j] = getSmallLetter(verticalDigits[i], j);
                }
                setLetter(currentSmallLetter, 0, offset, SMALL_LETTER_HEIGHT, SMALL_LETTER_WIDTH);
                offset = offset + SMALL_LETTER_WIDTH + 1;
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
    uint16_t valueReturn = num % 10;
    return valueReturn;
}
