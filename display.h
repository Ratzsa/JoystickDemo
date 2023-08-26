#ifndef __DISPLAY_FUNCTIONS__
#define __DISPLAY_FUNCTIONS__

void clearScreen();
void undoLetter(uint8_t *letter, uint8_t startX, uint8_t offset, uint8_t letterHeight, uint8_t letterWidth);
void setLetter(uint8_t *letter, uint8_t startX, uint8_t offset, uint8_t letterHeight, uint8_t letterWidth);
uint8_t setCoordinate(int16_t axisValue);

#endif