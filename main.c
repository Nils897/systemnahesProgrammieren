//
// Created by infohoschie on 09.12.24.
//

#include "devices/random.h"
#include "devices/uart.h"
#include "devices/timer.h"

#include <stdbool.h>

static void waitRelease( void );

static void randomNumberTest( void );

static void timerTest( void );

int main( void )
{
  //waitRelease();

  uart_init();
  uart_writeString( "Hello World!\n" );
//  char myARRAY[]={ 'A','B','C' };
//  uart_writeString( myARRAY );

  // randomNumberTest();

  timerTest();
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

static void timerTest( void )
{
  //timer_init( TIMER0 );

  timer_init_detailed( TIMER0, 15, TIMER_MODE_TIMER, TIMER_BIT_MODE_32 );

  timer_captureCompareSet( TIMER0, CC0, 2000, true );

  timer_start( TIMER0 );

  while ( true )
  {
    timer_capture( TIMER0, CC1 );

    uint32_t captureValue = timer_captureCompareGet( TIMER0, CC1 );

    //uart_writeNumber( captureValue );
  }
}
