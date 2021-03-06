/*@author David Stokes 801056264
*@debugging Seth Hensley 801055921
*/

#include <stdint.h>

#include <stdbool.h>

#include <stdio.h>

#include "inc/hw_memmap.h"

#include "driverlib/debug.h"

#include "driverlib/gpio.h"

#include "driverlib/sysctl.h"

//a 16.0-MHz internal circuit clock
//function to stall and do no work based on CR
#define BASE 1600000;
void delay(volatile float modifier) {
  volatile uint32_t i;
  volatile uint32_t size = modifier * BASE
  for (i = 0; i < size; i++) {}
}

//function that takes in a color, rate, and cycles to produce a given led sequence
void blink(volatile char color, float rate, volatile uint32_t cycles) {
  volatile uint32_t i = 0;
  volatile uint32_t blinks = cycles;
  for (i = 0; i < blinks; i++) {
    //make red
    if (color == 'r') {
      //turn on led
      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
      //wait
      delay(rate);
      //turn off led
      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x0);
      delay(rate);
    }
    //make blue
    else if (color == 'b') {
      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
      delay(rate);
      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x0);
      delay(rate);
    }
    //make green
    else {
      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
      delay(rate);
      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x0);
      delay(rate);

    }
  }
}

int main(void)

{
  //a 16.0-MHz internal circuit clock

  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)) {}

  //set the GPIO pins for outputting on led
  //red
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);
  //blue
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
  //should not need this as currently not called
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);

  //infinitely blink blue for 10 sec 1 sec intervals then red 10 sec .5 sec intervals
  while (1) {
    blink('b', 1.0, 5);
    blink('r', .5, 10);
  }

}
