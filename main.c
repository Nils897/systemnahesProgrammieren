#include "devices/uart.h"
#include "game/hangman.h"


int main( void )
{
  uart_init();
  gameStart();

  return 0;
}
