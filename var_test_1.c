/**
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Thomas Vogt
 **/

#include "var_test_1.h"

#include <stdint.h>

int varA;
int varB = 5;
int varArray[10] =
{
  0,
  1,
  2,
  3,
  4,
  5,
  6,
  7,
  8,
  9
};

const int constA = 1337;

static int varStatA;
static int varStatB = 50;

const int constArray[10] =
{
  10,
  11,
  12,
  13,
  14,
  15,
  16,
  17,
  18,
  19
};

static const int constStatA = 0xdead;

static int varStatArray[10];

void var_test_1( void )
{
  static int statArray[100] = { 0 };

  //int varArray[100] = { 0 }; /* memset ?!? */
}

void var_test_2( void )
{
  static int statArray[100] = { 0 };
}
