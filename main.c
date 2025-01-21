//
// Created by infohoschie on 09.12.24.
//

#include "devices/random.h"

#include <stdbool.h>

static void waitRelease( void )
{
  bool start = false;
  while ( !start )
  {
  }
}

static void doRandomNumber( uint8_t randomNumber )
{
  (void)randomNumber;
}

int main( void )
{
  //waitRelease();

  // Initialize the Module
  rng_init();

  while ( true )
  {
    uint8_t randomNumber = rng_getRandomValue_waiting();

    doRandomNumber( randomNumber );
  }
}
