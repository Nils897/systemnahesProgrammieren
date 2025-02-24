//
// Created by Nils on 18.02.25.
//

#ifndef HANGMAN_H
#define HANGMAN_H

uint8_t compareArrays(const char *word, const char *lines, uint8_t counter);

void hangmanWin(const char *lines, uint8_t length);

void makeLinesArray(const char *word, char *lines, uint8_t length, uint8_t *counter);

void printResult(uint8_t found, uint8_t *triesLeft);

void checkGuess(const char *word, char *lines, char guess, uint8_t length, uint8_t *found);

char getGuess();

void hangman (const char *word, uint8_t length);

void getRandomWord( char *word, uint8_t length );

void getUserWord( char *word, uint8_t length);

void gameStart (void);

#endif //HANGMAN_H
