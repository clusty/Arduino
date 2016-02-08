

// Example of sleeping and saving power
// 
// Author: Nick Gammon
// Date:   25 May 2011

#include <avr/sleep.h>
#include <avr/wdt.h>

// watchdog interrupt
ISR(WDT_vect) 
{
    wdt_disable();  // disable watchdog
}


// sleep bit patterns:
//  1 second:  0b000110
//  2 seconds: 0b000111
//  4 seconds: 0b100000
//  8 seconds: 0b100001
void myWatchdogEnable(const byte interval) 
{  
   MCUSR = 0;                          // reset various flags
   WDTCSR |= 0b00011000;               // see docs, set WDCE, WDE
   WDTCSR =  0b01000000 | interval;    // set WDIE, and appropriate delay

   wdt_reset();
   set_sleep_mode (SLEEP_MODE_PWR_DOWN);  
   sleep_mode();            // now goes to Sleep and waits for the interrupt
} 

void mySleep( int secs )
{
   int remainder = secs;
   while ( remainder > 0 )
   {
       if (remainder >= 8 )
       {
           remainder -= 8;
           myWatchdogEnable (0b100001);  // 8 seconds
       } else  if (remainder >= 4 )
       {
           remainder -= 4;
           myWatchdogEnable (0b100000);  // 4 seconds
       } else  if (remainder >= 2 )
       {
           remainder -= 2;
           myWatchdogEnable (0b000111);  // 4 seconds
       } else  if (remainder >= 1 )
       {
           remainder -= 1;
           myWatchdogEnable (0b000110);  // 4 seconds
       }
   }
}

void setup()
{
  Serial.begin( 57600);	// opens serial port, sets data rate to 57600 bps
}  // end of setup

void loop()
{
  Serial.write("Boo!!");
  delay(20);

  mySleep(300);

}  // end ofloop


