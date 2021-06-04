//-------------------------------------------------------------------------------------------------
//  DEMO SKETCH FOR 6-LEDS CHARLIEPLEXING + 5-LEDS CHARLIEPLEXING, USING 6 GPIOs
//
//  This sketch shows how a two state machines of a same PIO can run their own program.
//  Note this demo sketch has no practical interest: it requires 18 PIO instructions and drives
//  11 leds, while the 2-6leds-charliepexing demo sketch requires 11 PIO instructions and drives
//  12 leds. 
//
//  The only purpose is to illustrate the way to deploy and run different program in a PIO.
//  The reader can easily adapt the demo code to its own purpose.
//
//  Led connections: there are two groups:
//    - first one, 6 leds, see figure 1 in the documentation
//    - second one, 5 leds, see figure 2 in the documentation
//-------------------------------------------------------------------------------------------------

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
// Select the two state machines you want to use (0, 1, 2 or 3)
//-------------------------------------------------------------------------------------------------

static const uint32_t firstStateMachine = 0 ; // Will run the 6-led charlieplexing code
static const uint32_t secondStateMachine = 1 ; // Will run the 5-led charlieplexing code

//-------------------------------------------------------------------------------------------------
//  setup function
//-------------------------------------------------------------------------------------------------

void setup () {
//--- Optional, loop blinks the LED_BUILTIN led
  pinMode (LED_BUILTIN, OUTPUT) ;

//--- Set the PIO program offset. As each PIO has a 32 instructions memory,
//    and the the two PIO program has 18 instructions, you can choose any
//    value between 0 and 32 - 18 = 14 inclusive
  const uint32_t firstPrgmOffset = 0 ;

//--- Set the first group of GPIOs you use. Three consecutive pins are used, you set
//    here the first one. So 0 means GP0, GP1 and GP2 are used.
  const uint32_t firstGroupBasePin = 0 ;

//--- Set the second group of GPIOs you use. Three consecutive pins are used, you set
//    here the first one. So 4 means GP4, GP5 and GP6 are used.
  const uint32_t secondGroupBasePin = 4 ;

//--- Writes the 6-leds program instructions (11) in the selected PIO instruction
//    memory, from the specified offset. It returns the first free address, which is used as
//    the base address for the second program.
  const uint32_t secondPrgmOffset = charlieplexing6_add_program (pio, firstPrgmOffset) ;

//--- Writes the 5-leds program instructions (7) in the selected PIO instruction
//    memory, from the specified offset.
  charlieplexing5_add_program (pio, secondPrgmOffset) ;

//--- Perform all required initializations for configuring the first state machine
//    and the three output pins.
  charlieplexing6_program_init (pio, firstStateMachine, firstPrgmOffset, firstGroupBasePin) ;

//--- Perform all required initializations for configuring the second state machine
//    and the three output pins.
  charlieplexing5_program_init (pio, secondStateMachine, secondPrgmOffset, secondGroupBasePin) ;

//--- Start the state machines
  pio_sm_set_enabled (pio, firstStateMachine, true) ;
  pio_sm_set_enabled (pio, secondStateMachine, true) ;
}

//-------------------------------------------------------------------------------------------------
//  The value of gDeadline0 sets the date when the loop function will blink the LED_BUILTIN led
//  and apply the next setting to the first state machine 
//-------------------------------------------------------------------------------------------------

static uint32_t gDeadline0 = 0 ;

//-------------------------------------------------------------------------------------------------
//  The gValue0 global variable memorizes the next configuration of the leds driven by the
//  first state machine
//-------------------------------------------------------------------------------------------------

static uint32_t gValue0 = 1 ;

//-------------------------------------------------------------------------------------------------
//  The value of gDeadline1 sets the date when the loop function will apply the next setting to
//  the second state machine 
//-------------------------------------------------------------------------------------------------

static uint32_t gDeadline1 = 0 ;

//-------------------------------------------------------------------------------------------------
//  The gValue1 global variable memorizes the next configuration of the leds driven by the
//  second state machine
//-------------------------------------------------------------------------------------------------

static uint32_t gValue1 = 1 ;

//-------------------------------------------------------------------------------------------------
//  loop function
//
// Note the charlieplexing5_set_output_2 function is called for the second state machine. 
// 
// The charlieplexing5_set_output function activates a led for one fifth of the period, making it
// slightly brighter than a led of the first state machine which is activated for one sixth of the
// period. The charlieplexing5_set_output_2 function activates a led for one sixth of the period.
//-------------------------------------------------------------------------------------------------

void loop () {
  if (gDeadline0 < millis ()) { // Deadline reached ?
  //--- Update deadline
    gDeadline0 += 1000 ;
  //--- Blink LED_BUILTIN
    digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
  //--- Update the leds driven by the first state machine
    charlieplexing6_set_output (pio, firstStateMachine, gValue0) ;
  //--- Compute the next configuration of the leds driven by the first state machine
    gValue0 <<= 1 ;
    gValue0 &= 0x3F ;
    if (gValue0 == 0) {
      gValue0 = 1 ;
    }
  }
  if (gDeadline1 < millis ()) {  // Deadline reached ?
  //--- Update deadline, using a period different from the previous one
    gDeadline1 += 999 ;
  //--- Update the leds driven by the second state machine
    charlieplexing5_set_output_2 (pio, secondStateMachine, gValue1) ;
  //--- Compute the next configuration of the leds driven by the second state machine
    gValue1 <<= 1 ;
    gValue1 &= 0x1F ;
    if (gValue1 == 0) {
      gValue1 = 1 ;
    }
  }
}

//-------------------------------------------------------------------------------------------------
