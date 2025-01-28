# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
# If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

cmake_minimum_required( VERSION 3.22 )

project( arm_cortex_m0_start LANGUAGES ASM C )

# Define all Files:
add_executable( testApp )

target_sources(
  testApp
  PRIVATE
    entry.S
    entry_c.h
    entry_c.c
    main.c
    var_test_1.h
    var_test_1.c
    var_test_2.h
    var_test_2.c
    fibonacci.h
    fibonacci.c
    faculty.h
    faculty.c
    devices/register_access.h
    devices/register_access.c
    devices/random.h
    devices/random.c
    devices/uart.h
    devices/uart.c
    devices/nvic.h
    devices/timer.h
    devices/timer.c )

target_link_libraries( testApp PRIVATE gcc )

target_link_options(
  testApp
  PRIVATE
    -Wl,-Map=testApp.map
    -T ${CMAKE_SOURCE_DIR}/linker_script.lds )
set_target_properties(
  testApp
  PROPERTIES LINK_DEPENDS ${CMAKE_SOURCE_DIR}/linker_script.lds )


#####################################################################
# Post Build Commands:
# - extract binary


# To copy out the binary:
#arm-none-eabi-objcopy -O binary base.elf output.bin

add_custom_command(
  TARGET testApp
  POST_BUILD
  COMMAND "${OBJ_COPY}"
  ARGS -O binary $<TARGET_FILE:testApp> $<TARGET_FILE_BASE_NAME:testApp>.bin )

set_target_properties(
  testApp
  PROPERTIES ADDITIONAL_CLEAN_FILES $<TARGET_FILE_BASE_NAME:testApp>.bin )
