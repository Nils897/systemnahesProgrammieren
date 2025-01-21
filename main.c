//
// Created by infohoschie on 09.12.24.
//

#include "devices/random.h"

int main( void )
{
  // Initialize the Module
  rng_init();
  // Do other stuff, until 1st Random Number is generated...
  // Get the Random Value immediately.
  uint8_t randomNumber = rng_getRandomValue_immediately();
  // do something:
  if(randomNumber > 100) {
    // kill_cortex_m();
  }
}
