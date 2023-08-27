#ifndef _CONFIG_SNAKE_GAME
#define _CONFIG_SNAKE_GAME

#define BIT_SET(a, b) ((a) |= (1ULL << (b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1ULL<<(b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b))))

// SET number of LED matrix displays in use. Wokwi simulation uses 2.
// This is used in max72xx.h
#define NUMBER_OF_SEGMENTS 4

// SET MAX_COLUMNS to number of segments times 8.
// 1 segment -> 8, 2 segments -> 16, 3 segments -> 24, 4 segments -> 32, 5 segments -> no, 6 segments -> stop, 7 segments -> what are you doing
#define MAX_COLUMNS 32
#define MAX_ROWS 8

#define MAX_SNAKE_LENGTH (MAX_COLUMNS * MAX_ROWS - 1)
#define SNAKE_ARRAY_SIZE (MAX_COLUMNS * MAX_ROWS)
#define ANALOG_HIGH 768
#define ANALOG_LOW 256

// Change for easier or harder difficulty
#define TIME_BETWEEN_MOVES 200
#define TIME_BETWEEN_MOVES_REDUCTION 15

#define JOYSTICK_BUTTON 2
#define JOYSTICK_VERTICAL 0
#define JOYSTICK_HORIZONTAL 1

#define MOVE_UP 0
#define MOVE_RIGHT 1
#define MOVE_DOWN 2
#define MOVE_LEFT 3
#define MOVE_NEUTRAL 4

#define HORIZONTAL_AXIS 0
#define VERTICAL_AXIS 1

// X and Y values for drawing GAME/WIN/END screens
#define DRAW_X 16
#define DRAW_Y 8

#define CAPITAL_LETTER_SIZE 8
#define SMALL_LETTER_HEIGHT 5
#define SMALL_LETTER_WIDTH 3

#endif