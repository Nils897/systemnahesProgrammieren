#include "../devices/uart.h"
#include "../devices/random.h"

#include <stdlib.h>
//
// Created by Nils on 18.02.25.
//
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

uint8_t compareArrays(const char *word, const char *lines, uint8_t length)
{
  uart_writeString("comparing");
  for (uint8_t i = 0; i < length; i++)
  {
    if (word[i] != lines[i])  // Wenn ein Zeichen unterschiedlich ist
    {
      return 0;  // Rückgabe 0 bedeutet, die Arrays sind nicht gleich
    }
  }
  return 1;  // Rückgabe 1 bedeutet, die Arrays sind gleich
}

void hangman (const char *word, const uint8_t length)
{
  char lines[length];
  for (uint8_t i = 0; i < length; i++)
  {
    if (word[i] == '\0')
    {
      lines[i] = '\0';
      break;
    }
    lines[i] = '_';
  }
  uint8_t userWon = 0;
  while (userWon == 0)
  {
    uart_writeString("\nWord to guess:   ");
    for (uint8_t i = 0; i < length; i++)
    {
      if (lines[i] == '\0')
      {
        break;
      }
      uart_writeByte(lines[i]);  // Gibt das Zeichen (Strich oder später Buchstabe) aus
      uart_writeString(" ");
    }
    uart_writeString("\n");
    char guess = 0;
    while (guess == 0)
    {
      guess = uart_readByte();
    }
    uint8_t found = 0;
    for (uint8_t i = 0; i < length; i++)
    {
      if (word[i] == guess)
      {
        lines[i] = guess;  // Buchstabe ersetzen
        found = 1;
      }
    }
    if (!found)
    {
      uart_writeString("\nIncorrect guess.\n");
    }
    userWon = compareArrays(word, lines, length);
  }
  uart_writeString("You won!\n");
}

void getUserWord( char *word, uint8_t length)
{

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
  word[i] = '\0';  // Nullterminierung sicherstellen
  uart_writeString("\nWord: ");
  uart_writeString(word);
}

void gameStart (void)
{
  uint8_t choice = 0;
  //do
  //{
    char word [ 20 ];
    uart_writeString("Welcome to Hangman!\nWhich mode do you like?\n(1) Random word or (2) own word\nYour choice: ");
    while (choice == 0)
    {
      choice = uart_readByte();
    }
    if (choice == 49) // ASCII 1 = 49
    {
      getRandomWord(word, sizeof(word));
      hangman(word, sizeof(word));
    }
    else if (choice == 50) // ASCII 2 = 50
    {

      getUserWord(word, sizeof(word));
      hangman(word, sizeof(word));
    }
    else
    {
      uart_writeString("Invalid choice!\n");
    }
 // } while (choice != 1 && choice != 2);
}

