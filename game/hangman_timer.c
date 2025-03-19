#include <stdint.h>
#include "../devices/timer.h"
#include "../devices/uart.h"
#include "hangman_timer.h"

void startTimerForWholeGame() {
  timer_init_detailed( TIMER1, 4, TIMER_MODE_TIMER, TIMER_BIT_MODE_32, false );
  timer_start( TIMER1 );
}

uint32_t stopTimerForWholeGame() {
  timer_capture( TIMER1, CC1 );
  timer_stop( TIMER1 );
  uint32_t value = timer_captureCompareGet( TIMER1, CC1 );
  timer_clear( TIMER1 );
  return value;
}

void startTimerForTrys() {
  timer_init_detailed( TIMER0, 4, TIMER_MODE_TIMER, TIMER_BIT_MODE_32, true );
  timer_captureCompareSet( TIMER0, CC0, 5000000, true );
  timer_start( TIMER0 );
}

void stopTimerForTrys() {
  timer_stop( TIMER0 );
  timer_clear( TIMER0 );
}

uint32_t changeTimerValueToSeconds ( uint32_t value ) {
  uint32_t seconds = value / 1000000;
  return seconds;
}

uint32_t changeTimerValueToMilliseconds ( uint32_t value ) {
  uint32_t milliseconds = (value % 1000000) / 1000;
  return milliseconds;
}

uint32_t averageAnswerTime( uint32_t timeOfWholeGame, uint8_t counterOfInputs ) {
  uint32_t average = timeOfWholeGame / counterOfInputs;
  return average;
}

void promtTimeStatistics ( uint32_t timeOfWholeGame, uint8_t counterOfInputs) {
  uint32_t secondsOfWholeGame = changeTimerValueToSeconds ( timeOfWholeGame );
  uint32_t millisecondsOfWholeGame = changeTimerValueToMilliseconds ( timeOfWholeGame );
  uint32_t _averageAnswerTime = averageAnswerTime ( timeOfWholeGame, counterOfInputs );
  uint32_t secondsOfAverageAnswerTime = changeTimerValueToSeconds ( _averageAnswerTime );
  uint32_t millisecondsOfAverageAnswerTime = changeTimerValueToMilliseconds ( _averageAnswerTime );
  uart_writeString("\nStatistics:\n");
  uart_writeString("For the last game you needed ");
  uart_writeNumber32( secondsOfWholeGame );
  uart_writeString(",");
  uart_writeNumber32( millisecondsOfWholeGame );
  uart_writeString(" seconds.\n");
  uart_writeString("Your average time to answer a letter was ");
  uart_writeNumber32( secondsOfAverageAnswerTime );
  uart_writeString(",");
  uart_writeNumber32( millisecondsOfAverageAnswerTime );
  uart_writeString(" seconds.\n");
}