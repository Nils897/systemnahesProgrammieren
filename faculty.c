//
// Created by infohoschie on 09.12.24.
//

#include "faculty.h"

unsigned int faculty( unsigned int n )
{
  if ( n <= 1 )
  {
    return 1;
  }

  return n * faculty( n - 1 );
}

void faculty_test( void )
{
  unsigned int result = 0;

  result = faculty( 0 );
  result = faculty( 1 );
  result = faculty( 4 );
  result = faculty( 10 );
}
