//
// Created by infohoschie on 09.12.24.
//

#include "fibonacci.h"

unsigned int fibonacci( unsigned int count )
{
  // initialize first and second terms
  int t1 = 0, t2 = 1;

  // initialize the next term (3rd term)
  int nextTerm = t1 + t2;

  // print 3rd to nth terms
  for ( int i = 3; i <= count; ++i)
  {
    t1 = t2;
    t2 = nextTerm;
    nextTerm = t1 + t2;
  }

  return nextTerm;
}

void fibonacci_test( void )
{
  unsigned int result = 0;

  result = fibonacci( 0 );
  result = fibonacci( 1 );
  result = fibonacci( 2 );
  result = fibonacci( 5 );
}
