#ifndef HANGMAN_TIMER_H
#define HANGMAN_TIMER_H

#include <stdint.h>

/**
 * @brief
 */
void startTimerForWholeGame(void);


/**
 * @brief
 *
 * @return
 */
uint32_t stopTimerForWholeGame(void);


/**
 * @brief
 */
void startTimerForTrys(void);


/**
 * @brief
 *
 * @return
 */
uint32_t stopTimerForTrys(void);


/**
 * @brief
 *
 * @param
 *
 * @return
 */
uint32_t changeTimerValueToSeconds ( uint32_t value );


/**
 * @brief
 *
 * @param
 *
 * @return
 */
uint32_t changeTimerValueToSeconds ( uint32_t value );


/**
 * @brief
 *
 * @param
 *
 * @return
 */
uint32_t changeTimerValueToMilliseconds ( uint32_t value );


/**
 * @brief
 *
 * @params
 *
 * @return
 */
uint32_t averageAnswerTime( uint32_t sumOfTimesOfTries, uint32_t sumOfTries );


/**
 * @brief
 *
 * @params
 *
 * @return
 */
uint32_t promtTimeStatistics ( uint32_t timeOfWholeGame, uint32_t sumOfTimesOfTries, uint32_t sumOfTries );

#endif //HANGMAN_TIMER_H
