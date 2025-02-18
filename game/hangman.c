#include "../devices/uart.h"
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
  uart_writeString( "Enter a word: " );
  uint8_t word = uart_readByte();
  uart_writeNumber(word);
}