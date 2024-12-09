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
.thumb

.global Reset_Handler
.type Reset_Handler, %function

Reset_Handler:
  NOP

  MOVS R0,#1
start_loop:
  CMP R0,#0
  BNE start_loop

  // 1
  MOVS R0,#1
  BL fibonacci

  // 7
  MOVS R0,#5
  BL fibonacci

endless_loop:
  NOP
  b endless_loop

# R0: count
fibonacci:
  MOVS R1, #1
  MOVS R2, #1
  LDR R5, =__RAM_BASE
  STMIA R5!, { R1, R2 }

  PUSH { LR }
  BL fibonacci_rec
  POP { PC }

# R0: count
# R1: f_x
# R2: f_x+1
fibonacci_rec:
  PUSH {LR}
  CMP R0, #0
  BNE fib_cont  // if count == 0 => return
  POP {PC}

  fib_cont:
  PUSH {R3}

  SUBS R0, #1  // --count
  ADDS R3,R1,R2  // R3 = R1 + R2
  MOV R1,R2     // R1 = R2
  MOV R2,R3     // R2 = R3
  STMIA R5!, { R3 }
  BL fibonacci_rec // Fibonacci_rec( count, R1, R2 )

  POP {R3,PC}  // return
