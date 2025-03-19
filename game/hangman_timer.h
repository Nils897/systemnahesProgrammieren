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
void stopTimerForTrys(void);


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
uint32_t averageAnswerTime( uint32_t timeOfWholeGame, uint8_t counterOfInputs );


/**
 * @brief
 *
 * @params
 */
void promtTimeStatistics ( uint32_t timeOfWholeGame, uint8_t counterOfInputs );

#endif //HANGMAN_TIMER_H
