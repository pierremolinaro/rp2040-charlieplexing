//-------------------------------------------------------------------------------------------------
//  DEMO SKETCH FOR 5-LEDS CHARLIEPLEXING, USING 3 GPIOs
//
//  Led connections: see figure 2 in the documentation
//-------------------------------------------------------------------------------------------------

//--- Check RP2040 is selected
#ifndef ARDUINO_ARCH_RP2040
  #error Select a Raspberry Pi RP2040 board
#endif

//-------------------------------------------------------------------------------------------------
// Include Charlieplexing library
//-------------------------------------------------------------------------------------------------

#include <RP2040_PIO_Charlieplexing.h>

//-------------------------------------------------------------------------------------------------
// Select the PIO you want to use (pio0 or pio1)
//-------------------------------------------------------------------------------------------------

static const PIO pio = pio0 ;

//-------------------------------------------------------------------------------------------------
// Select the state machine you want to use (0, 1, 2 or 3)
//-------------------------------------------------------------------------------------------------

static const uint32_t stateMachine = 0 ;

//-------------------------------------------------------------------------------------------------
//  setup function
//-------------------------------------------------------------------------------------------------

void setup () {
//--- Optional, loop blinks the LED_BUILTIN led
  pinMode (LED_BUILTIN, OUTPUT) ;

//--- Set the PIO program offset. As each PIO has a 32 instructions memory,
//    and the 5-leds PIO program has 7 instructions, you can choose any
//    value between 0 and 32 - 7 = 25 inclusive
  const uint32_t prgmOffset = 0 ;

//--- Set the GPIOs you use. Three consecutive pins are used, you set here
//    the first one. So 0 means GP0, GP1 and GP2 are used.
  const uint32_t outputBasePin = 0 ;

//--- Writes the program instructions (11) in the selected PIO instruction
//    memory, from the specified offset.
  charlieplexing5_add_program (pio, prgmOffset) ;

//--- Perform all required initializations for configuring the state machine
//    and the three output pins.
  charlieplexing5_program_init (pio, stateMachine, prgmOffset, outputBasePin) ;

//--- Start the state machine
  pio_sm_set_enabled (pio, stateMachine, true) ;

//--- From now on, the refreshment is launched and is carried out without 
//    intervention of a processor. Initially, all the leds are off. To change,
//    you have to call the charlieplexing5_set_output function, which is done
//    in the loop function.
}

//-------------------------------------------------------------------------------------------------
//  The value of gDeadline sets the date when the loop function will execute the next action 
//-------------------------------------------------------------------------------------------------

static uint32_t gDeadline = 0 ;

//-------------------------------------------------------------------------------------------------
//  The gValue global variable memorizes the next configuration of the leds. 
//-------------------------------------------------------------------------------------------------

static uint32_t gValue = 1 ;

//-------------------------------------------------------------------------------------------------
//  loop function
//-------------------------------------------------------------------------------------------------

void loop () {
  if (gDeadline <= millis ()) { // Deadline reached ?
  //--- Update deadline
    gDeadline += 1000 ;
  //--- Blink LED_BUILTIN
    digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
  //--- Update the leds
    charlieplexing5_set_output (pio, stateMachine, gValue) ;
  //--- Compute the next configuration
    gValue <<= 1 ;
    gValue &= 0x1F ;
    if (gValue == 0) {
      gValue = 1 ;
    }
  }
}

//-------------------------------------------------------------------------------------------------
