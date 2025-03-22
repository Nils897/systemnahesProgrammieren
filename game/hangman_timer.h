#ifndef HANGMAN_TIMER_H
#define HANGMAN_TIMER_H

#include <stdint.h>

/**
 * @brief starts timer which is counting the time of the whole game
 */
void startTimerForWholeGame(void);


/**
 * @brief stops timer which is counting the time of the whole game
 *
 * @return value of the timer
 */
uint32_t stopTimerForWholeGame(void);


/**
 * @brief starts timer which is counting the time which the player has for his try
 */
void startTimerForTrys(void);


/**
 * @brief stops timer which is counting the time which the player has for his try
 *
 * @return vlaue of the timer
 */
void stopTimerForTrys(void);


/**
 * @brief change the timer value from mega-seconds to seconds
 *
 * @param value of the timer
 *
 * @return value in seconds
 */
uint32_t changeTimerValueToSeconds ( uint32_t value );

/**
 * @brief change the timer value from mega-seconds to milliseconds
 *
 * @param value of the timer
 *
 * @return value in milliseconds (only value after comma)
 */
uint32_t changeTimerValueToMilliseconds ( uint32_t value );


/**
 * @brief calculate the average answer time of the player
 *
 * @param timeOfWholeGame value of the timer for the whole game
 *
 * @param counterOfInputs count of inputs from the player
 *
 * @return value of average answer time
 */
uint32_t averageAnswerTime( uint32_t timeOfWholeGame, uint8_t counterOfInputs );


/**
 * @brief promt the timer statistics on the screen
 *
 * @param timeOfWholeGame value of the timer for the whole game
 *
 * @param counterOfInputs count of inputs from the player
 */
void promtTimeStatistics ( uint32_t timeOfWholeGame, uint8_t counterOfInputs );

#endif //HANGMAN_TIMER_H
