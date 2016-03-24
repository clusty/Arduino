#include"ds18B20.h"
#include "atlasPh.h"

DS18B20 ds(13);
AtlasPh ph( Serial1 );
int counter = 0;

void setup(void) {
   Serial.begin(9600);
   Serial1.begin(9600);  
}

void loop(void) {
   const float t = ds.getTemp(); 
   Serial.print("Temp:");
   Serial.println( t );
   if ( counter == 300 )
   {
      Serial.println("Compensating T"); 
      ph.setTemp( t );
      counter=0;
   }
   Serial.print("Ph:");
   Serial.println(ph.getPh());
   delay(1000); //just here to slow down the output so it is easier to read
}

