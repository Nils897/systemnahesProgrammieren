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

endless_loop:
  NOP
  b endless_loop

  MOVS R0,#1
  SUBS R1,#-1
  SUBS R1,#1
  b endless_loop
