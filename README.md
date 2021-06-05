# RP2040\_PIO\_Charlieplexing

An Arduino RP2040 Charlieplexing library using PIO.

> See the PDF documentation in the `extras` directory.
 
From [https://en.wikipedia.org/wiki/Charlieplexing](): *Charlieplexing is a technique for driving a multiplexed display in which relatively few I/O pins on a microcontroller are used e.g. to drive an array of LEDs*.

Very often, an interrupt routine is used to periodically refresh the leds. The PIOs built into the RP2040 microcontroller allow this refresh to be performed automatically, without processor intervention. 

This Arduino library uses the PIO (Programmable IO) module of RP2040 microcontroller for handling 5-leds and 6-leds charlieplexing:

  * the 6-leds version requires 11 PIO instructions, and 3 consecutive GPIO ports (demo:`6-leds-charlieplexing`);
  * the 5-leds version requires 7 PIO instructions, and 3 consecutive GPIO ports (demo:`5-leds-charlieplexing`).

## Running several state machines

The `6-leds-charlieplexing` and `5-leds-charlieplexing` demo sketches show how to run one state machine. The PIO is versatile, allowing many combinations: several state machines can run the same program, and several programs can be loaded and executed in a PIO.


The `2-6-leds-charlieplexing` sketch shows how a same PIO program can be ran by two state machines. The reader can easily extend the demo code to run the same program on the 4 state machines of a single PIO, allowing to control 24 leds via 12 pins. Using the 4 state machines of the 2 PIOs, you can drive 48 leds with 24 GPIOs.


The `5-leds-6-leds-charlieplexing` sketch shows how a two state machines of a same PIO can run their own program. Note this demo sketch has no practical interest: it requires 18 PIO instructions and drives 11 leds, while the `2-6leds-charliepexing` demo sketch requires 11 PIO instructions and drives 12 leds. The only purpose is to illustrate the way to deploy and run different program in a PIO. The reader can easily adapt this demo code to its own purpose.
 
## 6-leds

### Connections
The following figure shows how to connect the six leds to the RP2040. The value of the R resistors depends on the brightness you want to achieve; typically 150 Ω or 220 Ω is used.

![](extras/connection-6-leds.pdf)
 
### `6-leds-charlieplexing.ino` Sample Sketch
 
This sample sketch is fully described in the PDF documentation.

```cpp
#include <RP2040_PIO_Charlieplexing.h>

// Select the PIO you want to use (pio0 or pio1)
static const PIO pio = pio0 ;

// Select the state machine you want to use (0, 1, 2 or 3)
static const uint32_t stateMachine = 0 ;

// setup function
void setup () {
//--- Optional, loop blinks the LED_BUILTIN led
  pinMode (LED_BUILTIN, OUTPUT) ;

//--- Set the PIO program offset. As each PIO has a 32 instructions memory,
//    and the 6-leds PIO program has 11 instructions, you can choose any
//    value between 0 and 32 - 11 = 21 inclusive
  const uint32_t prgmOffset = 0 ;

//--- Set the GPIOs you use. Three consecutive pins are used, you set here
//    the first one. So 0 means GP0, GP1 and GP2 are used.
  const uint32_t outputBasePin = 0 ;

//--- Writes the program instructions (11) in the selected PIO instruction
//    memory, from the specified offset.
  charlieplexing6_add_program (pio, prgmOffset) ;

//--- Perform all required initializations for configuring the state machine
//    and the three output pins.
  charlieplexing6_program_init (pio, stateMachine, prgmOffset, outputBasePin) ;

//--- Start the state machine
  pio_sm_set_enabled (pio, stateMachine, true) ;

//--- From now on, the refreshment is launched and is carried out without 
//    intervention of a processor. Initially, all the leds are off. To change,
//    you have to call the charlieplexing6_set_output function, which is done
//    in the loop function.
}

//  The value of gDeadline sets the date when the loop function will execute the next action 
static uint32_t gDeadline = 0 ;

//  The gValue global variable memorizes the next configuration of the leds. 
static uint32_t gValue = 1 ;

//  loop function
void loop () {
  if (gDeadline <= millis ()) { // Deadline reached ?
  //--- Update deadline
    gDeadline += 1000 ;
  //--- Blink LED_BUILTIN
    digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
  //--- Update the leds
    charlieplexing6_set_output (pio, stateMachine, gValue) ;
  //--- Compute the next configuration
    gValue <<= 1 ;
    gValue &= 0x3F ;
    if (gValue == 0) {
      gValue = 1 ;
    }
  }
}
```

## 5-leds

 It is very similar to the 6-leds version, the only advantage is that it requires 7 instructions, unlike the 6-leds version which requires 11.

### Connections
The following figure shows how to connect the five leds to the RP2040. The value of the R resistors depends on the brightness you want to achieve; typically 150 Ω or 220 Ω is used.

![](extras/connection-5-leds.pdf)
 
### `5-leds-charlieplexing.ino` Sample Sketch
 
This sample sketch is fully described in the PDF documentation.

```cpp
#include <RP2040_PIO_Charlieplexing.h>

// Select the PIO you want to use (pio0 or pio1)
static const PIO pio = pio0 ;

// Select the state machine you want to use (0, 1, 2 or 3)
static const uint32_t stateMachine = 0 ;

// setup function
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

//  The value of gDeadline sets the date when the loop function will execute the next action 
static uint32_t gDeadline = 0 ;

//  The gValue global variable memorizes the next configuration of the leds. 
static uint32_t gValue = 1 ;

//  loop function
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
```

