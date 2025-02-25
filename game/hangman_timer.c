#include "../devices/timer.h"
#include "../devices/uart.h"
#include "hangman.h"
#include "hangman_timer.h"
//
// Created by liger on 24.02.2025.
//
#include <stdint.h>

void startTimerForWholeGame() {
  timer_init_detailed( TIMER0, 4, TIMER_MODE_TIMER, TIMER_BIT_MODE_8 );
  timer_start( TIMER0 );
  uart_writeString( "Timer started" );
}

uint8_t stopTimerForWholeGame() {
  timer_stop( TIMER0 );
  timer_capture( TIMER0, CC0 );
  uint8_t value = timer_captureCompareGet ( TIMER0, CC0 );
  return value;
}

void startTimerForTrys() {

}