#pragma once

#include <Arduino.h>

//-------------------------------------------------------------------------------------------------

#ifndef ARDUINO_ARCH_RP2040
  #error Select a Raspberry Pi RP2040 board
#endif

//-------------------------------------------------------------------------------------------------
// CHARLEPLEXING 5
//-------------------------------------------------------------------------------------------------

bool charlieplexing5_can_add_program (const PIO pio,
                                      const uint32_t prgmOffset) ;

uint32_t charlieplexing5_add_program (const PIO pio,
                                      const uint32_t prgmOffset) ;

void charlieplexing5_program_init (const PIO pio,
                                   const uint32_t stateMachine,
                                   const uint32_t prgmOffset,
                                   const uint32_t basePin) ;

void charlieplexing5_set_output (const PIO pio,
                                 const uint32_t stateMachine,
                                 const uint32_t value) ;

void charlieplexing5_set_output_2 (const PIO pio,
                                   const uint32_t stateMachine,
                                   const uint32_t value) ;

//-------------------------------------------------------------------------------------------------
// CHARLEPLEXING 5
//-------------------------------------------------------------------------------------------------

bool charlieplexing6_can_add_program (const PIO pio,
                                      const uint32_t prgmOffset) ;

uint32_t charlieplexing6_add_program (const PIO pio,
                                      const uint32_t prgmOffset) ;

void charlieplexing6_program_init (const PIO pio,
                                   const uint32_t stateMachine,
                                   const uint32_t prgmOffset,
                                   const uint32_t basePin) ;

void charlieplexing6_set_output (const PIO pio,
                                 const uint32_t stateMachine,
                                 const uint32_t value) ;

//-------------------------------------------------------------------------------------------------
