//-------------------------------------------------------------------------------------------------

#include <RP2040_PIO_Charlieplexing.h>
#include <pio-charlieplexing5.h>
#include <pio-charlieplexing6.h>

//-------------------------------------------------------------------------------------------------
// CHARLEPLEXING 5
//-------------------------------------------------------------------------------------------------

bool charlieplexing5_can_add_program (const PIO pio,
                                      const uint32_t prgmOffset) {
  return pio_can_add_program_at_offset (pio, & charlieplexing5_program, prgmOffset) ;
}

//-------------------------------------------------------------------------------------------------

uint32_t charlieplexing5_add_program (const PIO pio, const uint32_t prgmOffset) {
  pio_add_program_at_offset (pio, & charlieplexing5_program, prgmOffset) ;
  return prgmOffset + charlieplexing5_program.length ;
}

//-------------------------------------------------------------------------------------------------

void charlieplexing5_program_init (const PIO pio,
                                   const uint32_t stateMachine,
                                   const uint32_t prgmOffset,
                                   const uint32_t basePin) {
  pio_gpio_init (pio, basePin) ;
  pio_gpio_init (pio, basePin + 1) ;
  pio_gpio_init (pio, basePin + 2) ;
  pio_sm_config c = charlieplexing5_program_get_default_config (prgmOffset) ;
  sm_config_set_out_pins (&c, basePin, 3) ;
  pio_sm_init (pio, stateMachine, prgmOffset, &c) ;
  charlieplexing5_set_output (pio, stateMachine, 0) ; // All leds are OFF
}

//-------------------------------------------------------------------------------------------------

void charlieplexing5_set_output (const PIO pio,
                                 const uint32_t stateMachine,
                                 const uint32_t value) {
  uint32_t configuration = 0x05 | (0x05 << 6) | (0x3 << 12)  | (0x3 << 18) | (0x6 << 24) ;
  if ((value & 1) != 0) {
    configuration |= 1 << 3 ;
  }
  if ((value & 2) != 0) {
    configuration |= 4 << 9 ;
  }
  if ((value & 4) != 0) {
    configuration |= 1 << 15 ;
  }
  if ((value & 8) != 0) {
    configuration |= 2 << 21 ;
  }
  if ((value & 16) != 0) {
    configuration |= 2 << 27 ;
  }
  pio_sm_put_blocking (pio, stateMachine, configuration) ;
}

//-------------------------------------------------------------------------------------------------

void charlieplexing5_set_output_2 (const PIO pio,
                                   const uint32_t stateMachine,
                                   const uint32_t value) {
  uint32_t configuration = 0x05 | (0x05 << 6) | (0x3 << 12)  | (0x3 << 18) | (0x6 << 24) | (3 << 30) ;
  if ((value & 1) != 0) {
    configuration |= 1 << 3 ;
  }
  if ((value & 2) != 0) {
    configuration |= 4 << 9 ;
  }
  if ((value & 4) != 0) {
    configuration |= 1 << 15 ;
  }
  if ((value & 8) != 0) {
    configuration |= 2 << 21 ;
  }
  if ((value & 16) != 0) {
    configuration |= 2 << 27 ;
  }
  pio_sm_put_blocking (pio, stateMachine, configuration) ;
}

//-------------------------------------------------------------------------------------------------
// CHARLEPLEXING 6
//-------------------------------------------------------------------------------------------------

bool charlieplexing6_can_add_program (const PIO pio,
                                      const uint32_t prgmOffset) {
  return pio_can_add_program_at_offset (pio, & charlieplexing6_program, prgmOffset) ;
}

//-------------------------------------------------------------------------------------------------

uint32_t charlieplexing6_add_program (const PIO pio, const uint32_t prgmOffset) {
  pio_add_program_at_offset (pio, & charlieplexing6_program, prgmOffset) ;
  return prgmOffset + charlieplexing6_program.length ;
}

//-------------------------------------------------------------------------------------------------

void charlieplexing6_program_init (const PIO pio,
                                   const uint32_t stateMachine,
                                   const uint32_t prgmOffset,
                                   const uint32_t basePin) {
  pio_gpio_init (pio, basePin) ;
  pio_gpio_init (pio, basePin + 1) ;
  pio_gpio_init (pio, basePin + 2) ;
  pio_sm_config c = charlieplexing6_program_get_default_config (prgmOffset) ;
  sm_config_set_out_pins (&c, basePin, 3) ;
  pio_sm_init (pio, stateMachine, prgmOffset, &c) ;
  charlieplexing6_set_output (pio, stateMachine, 0) ; // All leds are OFF
}

//-------------------------------------------------------------------------------------------------

void charlieplexing6_set_output (const PIO pio,
                                 const uint32_t stateMachine,
                                 const uint32_t value) {
  uint32_t configuration = 0x05 | (0x3 << 9) | (0x6 << 18) ;
  if ((value & 1) != 0) {
    configuration |= 1 << 3 ;
  }
  if ((value & 2) != 0) {
    configuration |= 4 << 6 ;
  }
  if ((value & 4) != 0) {
    configuration |= 1 << 12 ;
  }
  if ((value & 8) != 0) {
    configuration |= 2 << 15 ;
  }
  if ((value & 16) != 0) {
    configuration |= 2 << 21 ;
  }
  if ((value & 32) != 0) {
    configuration |= 4 << 24 ;
  }
  pio_sm_put_blocking (pio, stateMachine, configuration) ;
}

//-------------------------------------------------------------------------------------------------
