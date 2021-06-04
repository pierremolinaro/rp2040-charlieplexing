//-------------------------------------------------------------------------------------------------
//  DEMO SKETCH FOR 2 * 6-LEDS CHARLIEPLEXING, USING 6 GPIOs
//
//  This sketch shows how a same PIO program can be ran by two state machines. The reader can
//  easily extend the demo code to run the same program on the 4 state machines of a single PIO,
//  allowing to control 24 leds via 12 pins.
//  Using the 4 state machines of the 2 PIOs, you can drive 48 leds with 24 GPIOs.
//
//  Led connections: there are two groups of 6 leds, see figure 1 in the documentation
//-------------------------------------------------------------------------------------------------

#ifndef ARDUINO_ARCH_RP2040
  #error Select a Raspberry Pi RP2040 board
#endif

//-------------------------------------------------------------------------------------------------

#include <RP2040_PIO_Charlieplexing.h>

//-------------------------------------------------------------------------------------------------
// Select the PIO you want to use (pio0 or pio1)
//-------------------------------------------------------------------------------------------------

static const PIO pio = pio0 ; // pio0 or pio1

//-------------------------------------------------------------------------------------------------
// Select the two state machines you want to use (0, 1, 2 or 3)
//-------------------------------------------------------------------------------------------------

static const uint32_t firstStateMachine  = 0 ;
static const uint32_t secondStateMachine = 1 ;

//-------------------------------------------------------------------------------------------------
//  setup function
//-------------------------------------------------------------------------------------------------

void setup () {
//--- Optional, loop blinks the LED_BUILTIN led
  pinMode (LED_BUILTIN, OUTPUT) ;

//--- Set the PIO program offset. As each PIO has a 32 instructions memory,
//    and the 6-leds PIO program has 11 instructions, you can choose any
//    value between 0 and 32 - 11 = 21 inclusive
  const uint32_t prgmOffset = 0 ;

//--- Set the first group of GPIOs you use. Three consecutive pins are used, you set
//    here the first one. So 0 means GP0, GP1 and GP2 are used.
  const uint32_t firstGroupBasePin = 0 ;

//--- Set the second group of GPIOs you use. Three consecutive pins are used, you set
//    here the first one. So 4 means GP4, GP5 and GP6 are used.
  const uint32_t secondGroupBasePin = 4 ;

//--- Writes the program instructions (11) in the selected PIO instruction
//    memory, from the specified offset.
  charlieplexing6_add_program (pio, prgmOffset) ;

//--- Perform all required initializations for configuring the first state machine
//    and the three output pins.
  charlieplexing6_program_init (pio, firstStateMachine, prgmOffset, firstGroupBasePin) ;

//--- Perform all required initializations for configuring the second state machine
//    and the three output pins. As the same prgmOffset is specified, this state machine
//    runs the same PIO instructions than the first one.
  charlieplexing6_program_init (pio, secondStateMachine, prgmOffset, secondGroupBasePin) ;

//--- Start the state machines
  pio_sm_set_enabled (pio, firstStateMachine, true) ;
  pio_sm_set_enabled (pio, secondStateMachine, true) ;

//--- From now on, the refreshment is launched and is carried out without 
//    intervention of a processor. Initially, all the leds are off. To change,
//    you have to call the charlieplexing6_set_output function, which is done
//    in the loop function.
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
    charlieplexing6_set_output (pio, secondStateMachine, gValue1) ;
  //--- Compute the next configuration of the leds driven by the second state machine
    gValue1 <<= 1 ;
    gValue1 &= 0x3F ;
    if (gValue1 == 0) {
      gValue1 = 1 ;
    }
  }
}

//-------------------------------------------------------------------------------------------------
