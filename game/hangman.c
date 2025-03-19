#include <stdint.h>
#include "../devices/uart.h"
#include "../devices/random.h"
#include "drawings.h"
#include "hangman_timer.h"
#include "../devices/timer.h"

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

const char* EASY_WORDS[] = {
  "apple",
  "house",
  "chair",
  "cloud",
  "bread",
  "water",
  "train",
  "mouse",
  "happy",
  "table",
  "plant",
  "light",
  "shirt",
  "music",
  "smile",
  "river",
  "pencil",
  "beach",
  "pillow",
  "window"
};

const char* MEDIUM_WORDS[] = {
  "giraffe",
  "blanket",
  "painter",
  "battery",
  "monster",
  "diamond",
  "whisper",
  "chimney",
  "fortune",
  "lantern",
  "journey",
  "tunnel",
  "pudding",
  "curtain",
  "goblin",
  "captain",
  "silence",
  "zeppelin",
  "twinkle",
  "firefly"
};

const char* HARD_WORDS[] = {
  "labyrinth",
  "blueprint",
  "nightmare",
  "encyclopedia",
  "marshmallow",
  "wristwatch",
  "microscope",
  "phenomenon",
  "psychology",
  "tournament",
  "handkerchief",
  "moonlight",
  "lightning",
  "blacksmith",
  "wilderness",
  "hologram",
  "adventure",
  "chocolate",
  "volunteer",
  "quicksilver"
};

char timerForTrysEnds;

uint8_t compareArrays(const char *word, const char *lines, uint8_t counter);

void hangmanWin(const char *lines, uint8_t counter, uint8_t triesLeft);

void hangmanLose(const char *word, uint8_t rightGuesses, uint8_t counter);

void makeLinesArray(const char *word, char *lines, uint8_t length, uint8_t *counter);

void printResult( uint8_t found, uint8_t *triesLeft );

uint8_t checkGuess( const char *word, char *lines, char guess, uint8_t length );

char getGuess();

void hangman (const char *word, uint8_t length);

void getRandomWord(char *word, uint8_t length, char decision);

void getUserWord(char *word, uint8_t length);

void hangmanEnd();

void hangmanHeading();

void hangmanFooter();

void displayInstruction();

void gameStart (void)
{
  hangmanHeading();
  char choice = 0;
  char word [ 20 ];
  uart_writeString("Welcome to Hangman!\nWhich mode do you like?\n(1) Random word\n(2) Own word\n(3) Instructions \nYour choice: ");
  while (choice != '1' && choice != '2' && choice != '3')
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
    uart_writeString("\n\nSelect difficulty for the word:\n(1) Easy\n(2) Medium\n(3) Hard\n Your choice: ");
    char decision = 0;
    while (decision != '1' && decision != '2' && decision !='3')
    {
      if (decision != 0)
      {
        uart_writeString("\nInvalid choice!\n");
        uart_writeString("Your choice: ");
      }
      decision = uart_readByte();
    }
    getRandomWord(word, sizeof(word), decision);
    startTimerForWholeGame();
    startTimerForTrys();
    hangman(word, sizeof(word));
  }
  else if (choice == '2')
  {
    getUserWord(word, sizeof(word));
    startTimerForWholeGame();
    startTimerForTrys();
    hangman(word, sizeof(word));
  }
  else if (choice == '3')
  {
    displayInstruction();
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
    hangmanHeading();
    uint8_t found = checkGuess(word, lines, guess, length);
    if (found == 1)
    {
      rightGuesses++;
    }
    printResult(found, &triesLeft);
    drawHangman(triesLeft);
    if (triesLeft == 0)
    {
      hangmanLose(word, rightGuesses, counter);
      break;
    }
    userWon = compareArrays(word, lines, counter);
  }
  if (triesLeft != 0)
  {
    hangmanWin(lines, counter, triesLeft);
  }
}

void getUserWord( char *word, uint8_t length)
{
  uart_readLine(word, length);
  uart_clearScreen();
  hangmanHeading();
}

void getRandomWord( char *word, const uint8_t length, const char decision)
{
  rng_init();
  if (decision == '1')
  {
    const uint8_t randIndex = rng_getRandomValue_waiting() % 20;
    uint8_t i = 0;
    while (EASY_WORDS[randIndex][i] != '\0' && i < length - 1)
    {
      word[i] = EASY_WORDS[randIndex][i];
      i++;
    }
    word[i] = '\0';
  }
  else if (decision == '2')
  {
    const uint8_t randIndex = rng_getRandomValue_waiting() % 20;
    uint8_t i = 0;
    while (MEDIUM_WORDS[randIndex][i] != '\0' && i < length - 1)
    {
      word[i] = MEDIUM_WORDS[randIndex][i];
      i++;
    }
    word[i] = '\0';
  }
  else if (decision == '3')
  {
    const uint8_t randIndex = rng_getRandomValue_waiting() % 20;
    uint8_t i = 0;
    while (HARD_WORDS[randIndex][i] != '\0' && i < length - 1)
    {
      word[i] = HARD_WORDS[randIndex][i];
      i++;
    }
    word[i] = '\0';
  }
  uart_writeString("\nDebug: Word: ");
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

void hangmanLose(const char *word, uint8_t rightGuesses, uint8_t counter)
{
  uart_writeString("You lost! Your word was: ");
  uart_writeString(word);
  uart_writeString("\n");
  uint32_t valueOfTimerForWholeGame = stopTimerForWholeGame();
  stopTimerForTrys();
  promtTimeStatistics( valueOfTimerForWholeGame, counter);
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
  stopTimerForTrys();
  promtTimeStatistics( valueOfTimerForWholeGame, counter);
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
  timerForTrysEnds = 0;
  while (guess == 0 && timerForTrysEnds == 0)
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
    uart_clearScreen();
    gameStart();
  }
  else if (choice == '2')
  {
    uart_writeString("\nGoodbye!\n");
    uart_writeString("('STR + A' and then 'X' will terminate qemu)\n\n");
    hangmanFooter();
  }
}

void hangmanHeading()
{
  uart_clearScreen();
  uart_writeGreenString("*---------------------------------------------------------------------------------*\n");
  uart_writeGreenString("*---------------------------------- Hangman Game ---------------------------------*\n");
  uart_writeGreenString("*---------------------------------------------------------------------------------*\n\n");
}

void hangmanFooter()
{
  uart_writeGreenString("\n*---------------------------------------------------------------------------------*\n");
  uart_writeGreenString  ("*--- Created by Janne Nußbaum, Justin Lotwin, Linus Gerlach and Nils Fleschhut ---*\n");
  uart_writeGreenString  ("*---------------------------------------------------------------------------------*\n\n");
}

void displayInstruction()
{
  uart_writeString("\n\nThe game \"Hangman\" works as follows:\n\n");
  uart_writeString("1. Choose whether you want to guess a pre-generated word or come up\nwith your own word that someone else has to guess.\nIf you choose the first option, you can select a difficulty level.\nThis only affects the words to be guessed.\n\n");
  uart_writeString("2. Now, dashes representing each letter of the word will be displayed.\nTry to guess the word by entering letters. But be careful you only have\n5 seconds for each input; otherwise, it will be counted as a mistake.\n\n");
  uart_writeString("3. If you guess a letter correctly, it will replace the corresponding dash.\nIf your input is incorrect, it counts as a mistake, and a part of the\nhangman figure will be drawn.\n\n");
  uart_writeString("4. If you guess the word correctly, you win.\nIf the hangman drawing is completed, you lose.\n\n");
}