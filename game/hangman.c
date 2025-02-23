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

void hangman( void )
{
  uart_writeString( "Hangman started!\n" );
  uart_writeString( "Enter a word: ");
  uint8_t letter = uart_readByte();
  uart_writeByte(letter);
}

void spiel (char *word)
{

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
}

void gameStart (void)
{
  uint8_t choice = 0;
  do
  {
    char word [ 20 ];
    uart_writeString("Welcome to Hangman!\nWhich mode do you like?\n(1) Random word or (2) own word");
    choice = uart_readByte();
    if (choice == 1)
    {
      getUserWord(word, sizeof(word));
      spiel(word);
    }
    else if (choice == 2)
    {
      getRandomWord(word, sizeof(word));
      spiel(word);
    }
    else
    {
      uart_writeString("Invalid choice!\n");
    }
  } while (choice != 1 && choice != 2);
}

