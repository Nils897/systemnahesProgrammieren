#ifndef DRAWINGS_H
#define DRAWINGS_H
#include <stdint.h>

/**
 * @brief Contains the drawing for each individual state of the hangman depending on the tries left by the user
 *
 * @param triesLeft is an uint8_t number which contains the tries left of the user
 */
void drawHangman(uint8_t triesLeft);

#endif