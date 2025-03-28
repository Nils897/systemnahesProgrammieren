#include <stdint.h>

#include "timer.h"
#include "nvic.h"
#include "uart.h"
#include "register_access.h"

void Interrupt8_Handler(void);

void Interrupt8_Handler(void)
{
  register_write( TIMER0_BASE_ADDRESS | TIMER_COMPARE_0, 0 );
  register_write( Interrupt_ICPR, Interrupt_ID8 );

  timerForTrysEnds = '1';
}

/*void timer_init( Timer const timer )
{
  // Init Timer with an interval of ~4sek
  timer_init_detailed( timer, 15, TIMER_MODE_TIMER, TIMER_BIT_MODE_32 );
  timer_captureCompareSet( timer, CC0, 500, true );
  timer_start( timer );
}*/

void timer_init_detailed( Timer const timer, uint8_t const prescaler, TimerMode const mode, TimerBitMode const bitMode, bool interrupt )
{
  const uint32_t timerBase = TimerBase[ timer ];
  // Instance[0] of the Timer uses Peripheral ID: 8

  // Prescaler
  register_write(timerBase | TIMER_PRESCALER , prescaler );

  // BitMode
  register_write(timerBase | TIMER_BITMODE , (uint32_t)bitMode );

if ( interrupt == true )
{
  // Enable Interrupt
  register_write((TIMER0_BASE_ADDRESS | TIMER_INTENSET), INT_COMPARE0 ); // Interrupt on Compare[0]

  // Enable User-Interrupt from Cortex-M0
  // ID8 ist der Timer0
  register_write( Interrupt_Set_Enable, Interrupt_ID8 );
}
}

void timer_captureCompareSet( Timer timer, TimerCaptureCompare captureCompare, uint32_t value, bool shortcutClear )
{
  const uint32_t timerBase = TimerBase[ timer ];
  const uint32_t ccAddress = timerBase | TimerCCOffset[ captureCompare ];

  register_write( ccAddress, value );

  // Enable Shortcut between CC[0] and CLEAR
  uint32_t oldValue = register_read( timerBase | TIMER_SHORTS );
  oldValue &= ~( 1 << captureCompare );
  register_write(
    timerBase | TIMER_SHORTS,
    oldValue | ( shortcutClear ? 1 : 0 ) << captureCompare );
}

uint32_t timer_captureCompareGet( Timer timer, TimerCaptureCompare captureCompare )
{
  const uint32_t timerBase = TimerBase[ timer ];
  const uint32_t ccAddress = timerBase | TimerCCOffset[ captureCompare ];

  return register_read( ccAddress );
}

void timer_start( Timer timer )
{
  const uint32_t timerBase = TimerBase[ timer ];

  register_write( timerBase | TIMER_START, TIMER_TASK_START );
}

void timer_stop( Timer timer )
{
  const uint32_t timerBase = TimerBase[ timer ];

  register_write( timerBase | TIMER_STOP, TIMER_TASK_START );
}

void timer_count( Timer timer )
{
  const uint32_t timerBase = TimerBase[ timer ];

  register_write( timerBase | TIMER_COUNT, TIMER_TASK_START );
}

void timer_clear( Timer timer )
{
  const uint32_t timerBase = TimerBase[ timer ];

  register_write( timerBase | TIMER_CLEAR, TIMER_TASK_START );
}

void timer_capture( Timer timer, TimerCaptureCompare capture )
{
  const uint32_t timerBase = TimerBase[ timer ];
  const uint32_t timerCaptureTaskOffset = timerBase | TimerCaptureTaskOffset[ capture ];

  register_write( timerCaptureTaskOffset , TIMER_TASK_START );
}

void timer_clearCompareEvent( Timer timer )
{
  const uint32_t timerBase = TimerBase[ timer ];

  register_write(timerBase | TIMER_COMPARE_0, TIMER_EVENT_CLEAR);
}
