/**
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Thomas Vogt
 * Sven Reis
 **/

.section .vectors, "ax"
.align 2
.globl __Vectors

__Vectors:
.long __StackTop       /*     Top of Stack */
.long Reset_Handler    /*     Reset Handler */

.ascii "HELLO WORLD"

.section .text
.align 2

.syntax unified

.global Reset_Handler
.type Reset_Handler, %function

Reset_Handler:
  NOP

  MOVS R0,#1
start_loop:
  CMP R0,#0
  BNE start_loop

  // 1! == 1
  MOVS R2,#1
  BL faculty

  // 0! == 1
  MOVS R2,#0
  BL faculty

  // 5! == 120
  MOVS R2,#5
  BL faculty

endless_loop:
  NOP
  b endless_loop

faculty:
  MOVS R0,#1  // result

  MOVS R1,#0  // counter a
  loop_start:
    ADDS R1,#1
    MULS R0,R1
    CMP R1,R2
    BLT loop_start
  loop_end:

  BX LR // return
