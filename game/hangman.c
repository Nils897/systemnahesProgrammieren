#include <stdint.h>
#include "../devices/uart.h"
#include "../devices/random.h"
#include "drawings.h"
#include "hangman_timer.h"

const char* WORDS[] = {
  "lampe",
  "giraffe",
  "blitz",
  "kaugummi",
  "schaufel",
  "puzzle",
  "wolke",
  "banane",
  "zeppelin",
  "taucher",
  "schnur",
  "ofen",
  "karussell",
  "raupe",
  "uhr",
  "tornado",
  "quark",
  "fenster",
  "schnecke",
  "zauberer"
};

uint32_t sumOfTimesOfTrys = 0;
uint32_t sumOfTrys = 0;

uint8_t compareArrays(const char *word, const char *lines, uint8_t counter);

void hangmanWin(const char *lines, uint8_t counter, uint8_t triesLeft);

void hangmanLose(const char *word, uint8_t rightGuesses);

void makeLinesArray(const char *word, char *lines, uint8_t length, uint8_t *counter);

void printResult( uint8_t found, uint8_t *triesLeft );

uint8_t checkGuess( const char *word, char *lines, char guess, uint8_t length );

char getGuess();

void hangman (const char *word, uint8_t length);

void stopTimerForTrysAndAddSums(void);

void getRandomWord( char *word, uint8_t length );

void getUserWord( char *word, uint8_t length);

void hangmanEnd();

void hangmanHeading();

void hangmanFooter();

void gameStart (void)
{
  hangmanHeading();
  char choice = 0;
  char word [ 20 ];
  uart_writeString("Welcome to Hangman!\nWhich mode do you like?\n(1) Random word or (2) own word\nYour choice: ");
  while (choice != '1' && choice != '2')
  {
    if (choice != 0)
    {
      uart_writeString("\nInvalid choice!\n");
      uart_writeString("Your choice: ");
    }
    choice = uart_readByte();

  }
  if (choice == '1')
  {
    getRandomWord(word, sizeof(word));
    startTimerForWholeGame();
    startTimerForTrys();
    hangman(word, sizeof(word));
  }
  else if (choice == '2')
  {
    getUserWord(word, sizeof(word));
    startTimerForWholeGame();
    hangman(word, sizeof(word));
  }
}

void hangman (const char *word, const uint8_t length)
{
  char lines[length];
  uint8_t counter = 0;
  uint8_t triesLeft = 11;
  uint8_t userWon = 0;
  uint8_t rightGuesses = 0;
  makeLinesArray(word, lines, length, &counter);
  while (userWon == 0)
  {
    uart_writeString("\nWord to guess:   ");
    for (uint8_t i = 0; i < length; i++)
    {
      if (lines[i] == '\0')
      {
        break;
      }
      uart_writeByte(lines[i]);
      uart_writeString(" ");
    }
    uart_writeString("\n");
    hangmanFooter();
    char guess = getGuess();
    stopTimerForTrysAndAddSums();
    hangmanHeading();
    startTimerForTrys();
    uint8_t found = checkGuess(word, lines, guess, length);
    if (found == 1)
    {
      rightGuesses++;
    }
    printResult(found, &triesLeft);
    drawHangman(triesLeft);
    if (triesLeft == 0)
    {
      hangmanLose(word, rightGuesses);
      break;
    }
    userWon = compareArrays(word, lines, counter);
  }
  if (triesLeft != 0)
  {
    hangmanWin(lines, counter, triesLeft);
  }
}

void stopTimerForTrysAndAddSums() {
  uint32_t timeOfTry = stopTimerForTrys();
  sumOfTimesOfTrys += timeOfTry;
  sumOfTrys ++;
}

void getUserWord( char *word, uint8_t length)
{
  uart_readLine(word, length);
  uart_clearScreen();
  hangmanHeading();
}

void getRandomWord( char *word, const uint8_t length )
{
  rng_init();
  const uint8_t randIndex = rng_getRandomValue_waiting() % 20;
  uint8_t i = 0;
  while (WORDS[randIndex][i] != '\0' && i < length - 1)
  {
    word[i] = WORDS[randIndex][i];
    i++;
  }
  word[i] = '\0';
  uart_writeString("\nWord: ");
  uart_writeString(word);
}

uint8_t compareArrays(const char *word, const char *lines, uint8_t counter)
{
  for (uint8_t i = 0; i < counter; i++)
  {
    if (word[i] != lines[i])
    {
      return 0;
    }
  }
  return 1;
}
void hangmanLose(const char *word, uint8_t rightGuesses)
{
  uart_writeString("You lost! Your word was: ");
  uart_writeString(word);
  uart_writeString("\n");
  uint32_t valueOfTimerForWholeGame = stopTimerForWholeGame();
  stopTimerForTrysAndAddSums();
  promtTimeStatistics( valueOfTimerForWholeGame, sumOfTimesOfTrys, sumOfTrys );
  uint8_t wrongGuesses = 11;
  uint8_t tries = rightGuesses + wrongGuesses;
  uart_writeString("You did need: ");
  uart_writeNumber(tries);
  uart_writeString(" Guesses with ");
  uart_writeNumber(wrongGuesses);
  uart_writeString(" wrong guesses\n");
  hangmanEnd();
}

void hangmanWin(const char *lines, uint8_t counter, uint8_t triesLeft)
{
  uart_writeString("The word is: ");
  uart_writeString(lines);
  uart_writeString("\n");
  uart_writeString("You won!\n");
  uint32_t valueOfTimerForWholeGame = stopTimerForWholeGame();
  stopTimerForTrysAndAddSums();
  promtTimeStatistics( valueOfTimerForWholeGame, sumOfTimesOfTrys, sumOfTrys );
  uint8_t wrongGuesses = 11 - triesLeft;
  uint8_t tries = counter + wrongGuesses;
  uart_writeString("You did need: ");
  uart_writeNumber(tries);
  uart_writeString(" Guesses with ");
  uart_writeNumber(wrongGuesses);
  uart_writeString(" wrong guesses\n");
  hangmanEnd();
}

void makeLinesArray(const char *word, char *lines, uint8_t length, uint8_t *counter)
{
  for (uint8_t i = 0; i < length; i++)
  {
    if (word[i] == '\0')
    {
      *counter = i;
      lines[i] = '\0';
      break;
    }
    lines[i] = '_';
  }
}

void printResult( const uint8_t found, uint8_t *triesLeft)
{
  if (!found)
  {
    (*triesLeft)--;
    uart_writeString("\nIncorrect guess.\n(Use lower case characters | ss instead of ß | ue for ü | ae for ä | oe for ö)\nTries left: ");
    uart_writeNumber(*triesLeft);
    uart_writeString("\n");
  }
  else
  {
    uart_writeString("\nCorrect guess. Tries left: ");
    uart_writeNumber(*triesLeft);
    uart_writeString("\n");
  }
}

uint8_t checkGuess(const char *word, char *lines, const char guess, const uint8_t length)
{
  for (uint8_t i = 0; i < length; i++)
  {
    if (guess == lines[i])
    {
      return 0;
    }
  }
  uint8_t found = 0;
  for (uint8_t i = 0; i < length; i++)
  {
    if (word[i] == guess)
    {
      lines[i] = guess;
      found = 1;
    }
    if (i == length - 1 && found == 1)
    {
      return 1;
    }
  }
  return 0;
}

char getGuess()
{
  char guess = 0;
  while (guess == 0)
  {
    guess = uart_readByte();
  }
  return guess;
}

void hangmanEnd(void)
{
  uart_writeString("\n\n");
  uart_writeString("(1) Play again or (2) Exit\nYour choice: ");
  char choice = 0;
  while (choice == 0 && choice != '1' && choice != '2')
  {
    choice = uart_readByte();
  }
  if (choice == '1')
  {
    uart_clearScreen();
    gameStart();
  }
  else if (choice == '2')
  {
    uart_writeString("\nGoodbye!\n");
    uart_writeString("('STR + A' and then 'X' will terminate qemu)\n\n");
  }
}

void hangmanHeading()
{
  uart_clearScreen();
  uart_writeRedString("*---------------------------------------------------------------------------------*\n");
  uart_writeRedString("*---------------------------------- Hangman Game ---------------------------------*\n");
  uart_writeRedString("*---------------------------------------------------------------------------------*\n\n");
}

void hangmanFooter()
{
  uart_writeRedString("\n*---------------------------------------------------------------------------------*\n");
  uart_writeRedString  ("*--- Created by Janne Nußbaum, Justin Lotwin, Linus Gerlach and Nils Fleschhut ---*\n");
  uart_writeRedString  ("*---------------------------------------------------------------------------------*\n\n");
}