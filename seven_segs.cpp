/*
Title:      Program to put an integer value on 7 segment display
Author:     David Ross, Course Code, Student ID
Date:       Today's date
Description:   We will be using the the DigitDisplay public member functions:

                DigitDisplay        (to define the 4 digit display Pin)
                clear               to clear the display
                setBrightness       (to set display brightness 0(low) - 7(high)
                setColon            (1 = colon on, 0 = colon off)
                write               to write a 4 hex digit value
                writeRaw            to write a pattern on 7 segs              
*/

// Include Section
#include "mbed.h"                   // include the MBED library
#include "DigitDisplay.h"           // include the DigitDisplay Library

// Hardware definitions
DigitDisplay segment(D2,D3);          // 4 digit display connected to D16

// Global variables
unsigned char mess[]= {0x00,0x00,0x00,0x00,           // segs are off
                       0x39,0x5c,0x1c,0x04,0x5e,      // segs spell Covid
                       0x00,0x00,0x00,0x00};          // segs are off
unsigned short i;

int main(void)
{
    unsigned short counter;
    segment.clear();                // clear 4 digit display
    segment.setColon(0);            // turn colon off
    segment.setBrightness(4);       // set display brightness to med
    for(counter=9999;counter>0;counter--)
    {
        segment.write(counter);     // write value 1234
        wait_ms(1);                 // wait 1 ms
    }
    segment.write(counter);         // treat 0 as special case otherwise
                                    // you get an infinite loop
    wait_ms(1000);                  // wait for 1 second
    for(;;)                         // loop forever
    {                                   
        segment.writeRaw(0,0x6d);   // Pattern for STOP 
        segment.writeRaw(1,0x78);
        segment.writeRaw(2,0x3f);
        segment.writeRaw(3,0x73);  
        wait_ms(500);
      for(i=0;i<=9;++i)             // scrolls Covid
      {
         segment.writeRaw(&mess[i]); 
         wait_ms(250);
      }
      wait_ms(1000);                // wait for 1 second
    }
                          
}