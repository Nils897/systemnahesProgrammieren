#include "devices/random.h"
#include "devices/uart.h"
#include "devices/timer.h"
#include "game/hangman.h"

#include <stdbool.h>

static void waitRelease( void );

static void randomNumberTest( void );

static void timerTest( void );

int main( void )
{
  uart_init();
  uart_writeString( "Hello World!\n" );
  gameStart();
}

static void waitRelease( void )
{
  bool start = false;
  while ( !start )
  {
  }
}

static void randomNumberTest( void )
{
  // Initialize the Module
  rng_init();

  while ( true )
  {
    uint8_t randomNumber = rng_getRandomValue_waiting();

    uart_writeNumber( randomNumber );
    uart_writeString( "\n" );
  }
}
