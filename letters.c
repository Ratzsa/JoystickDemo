#include <stdio.h>
#include <stdint.h>
#include "config.h"
#include "letters.h"


uint8_t getCapitalLetter(uint8_t setLetter, uint8_t rowNum)
{
    uint8_t U[] = {0B00000000,0B01000010,0B01000010,0B01000010,0B01000010,0B00100100,0B00011000,0B00000000};
    uint8_t D[] = {0B00000000,0B00111000,0B00100100,0B00100010,0B00100010,0B00100100,0B00111000,0B00000000};
    uint8_t L[] = {0B00000000,0B00100000,0B00100000,0B00100000,0B00100000,0B00100000,0B00111100,0B00000000};
    uint8_t R[] = {0B00000000,0B00111000,0B00100100,0B00100100,0B00111000,0B00100100,0B00100100,0B00000000};
    uint8_t N[] = {0B00000000,0B00100010,0B00110010,0B00101010,0B00100110,0B00100010,0B00000000,0B00000000};

    switch(setLetter)
    {
        case MOVE_UP:
        return U[rowNum];
        break;

        case MOVE_DOWN:
        return D[rowNum];
        break;

        case MOVE_LEFT:
        return L[rowNum];
        break;

        case MOVE_RIGHT:
        return R[rowNum];
        break;

        case MOVE_NEUTRAL:
        return N[rowNum];
        break;

        default:
        break;
    }

    return 1;
}

uint8_t getSmallLetter(uint8_t setLetter, uint8_t rowNum)
{
    uint8_t X[] = {0B000,0B101,0B010,0B101,0B000};
    uint8_t Y[] = {0B000,0B101,0B010,0B010,0B000};
    uint8_t One[] = {0B010,0B010,0B010,0B010,0B010};
    uint8_t Two[] = {0B111,0B001,0B111,0B100,0B111};
    uint8_t Three[] = {0B111,0B001,0B011,0B001,0B111};
    uint8_t Four[] = {0B101,0B101,0B111,0B001,0B001};
    uint8_t Five[] = {0B111,0B100,0B111,0B001,0B111};
    uint8_t Six[] = {0B111,0B100,0B111,0B101,0B111};
    uint8_t Seven[] = {0B111,0B001,0B001,0B001,0B001};
    uint8_t Eight[] = {0B111,0B101,0B111,0B101,0B111};
    uint8_t Nine[] = {0B111,0B101,0B111,0B001,0B111};
    uint8_t Zero[] = {0B111,0B101,0B101,0B101,0B111};
    uint8_t U[] = {0B101,0B101,0B101,0B101,0B111};
    uint8_t L[] = {0B100,0B100,0B100,0B100,0B111};
    uint8_t D[] = {0B110,0B101,0B101,0B101,0B110};
    uint8_t R[] = {0B110,0B101,0B110,0B101,0B101};
    uint8_t N[] = {0B000,0B111,0B000,0B111,0B000};

    switch(setLetter)
    {
        case 1:
        return One[rowNum];
        break;

        case 2:
        return Two[rowNum];
        break;

        case 3:
        return Three[rowNum];
        break;

        case 4:
        return Four[rowNum];
        break;

        case 5:
        return Five[rowNum];
        break;

        case 6:
        return Six[rowNum];
        break;

        case 7:
        return Seven[rowNum];
        break;

        case 8:
        return Eight[rowNum];
        break;

        case 9:
        return Nine[rowNum];
        break;

        case 0:
        return Zero[rowNum];
        break;

        case 11:
        return X[rowNum];
        break;

        case 12:
        return Y[rowNum];
        break;

        case 13:
        return U[rowNum];
        break;

        case 14:
        return D[rowNum];
        break;

        case 15:
        return L[rowNum];
        break;

        case 16:
        return R[rowNum];
        break;

        case 17:
        return N[rowNum];
        break;

        default:
        break;
    }

    return 1;
}

