#ifndef HANGMAN_TIMER_H
#define HANGMAN_TIMER_H

#include <stdint.h>

void startTimerForWholeGame(void);

uint32_t stopTimerForWholeGame(void);

void startTimerForTrys(void);

uint32_t stopTimerForTrys();

uint32_t changeTimerValueToSeconds ( uint32_t value );

uint32_t changeTimerValueToSeconds ( uint32_t value );

uint32_t changeTimerValueToMilliseconds ( uint32_t value );

uint32_t averageAnswerTime( uint32_t sumOfTimesOfTries, uint32_t sumOfTries );

uint32_t promtTimeStatistics ( uint32_t timeOfWholeGame, uint32_t sumOfTimesOfTries, uint32_t sumOfTries );

#endif //HANGMAN_TIMER_H
