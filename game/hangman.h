#ifndef HANGMAN_H
#define HANGMAN_H

#include <stdint.h>

/**
 * @brief Compares two char-Arrays (equal or  not)
 *
 * @param word char-Array which contains the word to guess
 *
 * @param lines: char-Array which contains the guesses of the user
 *
 * @param counter which holds the index where "\0" is in word
 *
 * @return uint_8 value which is 0 when not equal and 1 when equal
 */
uint8_t compareArrays(const char *word, const char *lines, uint8_t counter);


/**
 * @brief Winning-Screen if the user won the hangman game
 *
 * @param lines a char-Array which is the guessed word
 *
 * @param counter for calculating the total guesses the user made
 *
 * @param triesLeft for calculating the total guesses of the user
 */
void hangmanWin(const char *lines, uint8_t counter, uint8_t triesLeft);


/**
 * @brief Losing-Screen if the user lost the hangman game
 *
 * @param word is a char-Array which contains the word the user couldn't guess
 *
 * @param rightGuesses is a number which contains the amount of right guesses the user made
 */
void hangmanLose(const char *word, uint8_t rightGuesses);


/**
 * @brief Writes as many "_" as there are characters in word
 *
 * @param word: char-Array which contains the word to guess
 *
 * @param lines: char-Array which contains the user guesses so at first only "_"
 *
 * @param length: number which holds the length of word to iterate over word
 *
 * @param counter: number which gets the index of "\0" in the word/lines char-Array
 */
void makeLinesArray(const char *word, char *lines, uint8_t length, uint8_t *counter);


/**
 * @brief Prints the result of the user guess on the terminal
 *
 * @param found: number which contains if the guessed character is right (found = 1) or wrong (found = 0)
 *
 * @param triesLeft: number which contains the tries the user has left to guess to word correctly
 */
void printResult(uint8_t found, uint8_t *triesLeft);


/**
 * @brief Checks if the guess from the user is correct or incorrect
 *
 * @param word: Contains the word to guess
 *
 * @param lines: Contains the state of the user guessed word
 *
 * @param guess: Contains the guess of the user
 *
 * @param length: Contains the length of the word to guess
 *
 * @return found: gets assigned depending on the correction of the guess (found = 1 for right and found = 0 for wrong)
 */
uint8_t checkGuess(const char *word, char *lines, char guess, uint8_t length);


/**
 * @brief Gets the users next guess
 *
 * @return character which the user guessed
 */
char getGuess();


/**
 * @brief Holds the main-logic of the hangman game
 *
 * @param word: Contains the word to guess
 *
 * @param length: Contains the length of the word to guess
 */
void hangman (const char *word, uint8_t length);


/**
 * @brief
 */
void stopTimerForTrysAndAddSums(void);


/**
 * @brief Gets a random word of the word-list
 *
 * @param word: Gets assigned to the random word in this function
 *
 * @param length: Holds the length of the word
 */
void getRandomWord( char *word, uint8_t length );


/**
 * @brief Gets a word by a user via terminal input
 *
 * @param word: char-Array which holds the word
 *
 * @param length: number which contains the length of the word
 */
void getUserWord( char *word, uint8_t length);


/**
 * @brief Starts the main-function of the hangman game
 */
void gameStart (void);

/**
 * @brief Creates a Heading and clears the terminal before
 */
void hangmanHeading (void);

/**
 * @brief Creates a Footer with the names of the contributors
 */
void hangmanFooter(void);

#endif //HANGMAN_H
