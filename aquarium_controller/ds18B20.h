#include <OneWire.h> 
class DS18B20
{
   public:
      DS18B20(int pin);
      float getTemp();
   private:
      OneWire _ds;   
};

DS18B20::DS18B20( int pin ):_ds(pin) 
{
}

float DS18B20::getTemp()
{
   //returns the temperature from one DS18S20 in DEG Celsius

   byte data[12];
   byte addr[8];

   if ( !_ds.search(addr)) {
      //no more sensors on chain, reset search
      _ds.reset_search();
      return -1000;
   }

   if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return -1000;
   }

   if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("Device is not recognized");
      return -1000;
   }

   _ds.reset();
   _ds.select(addr);
   _ds.write(0x44,1); // start conversion, with parasite power on at the end

   byte present = _ds.reset();
   _ds.select(addr);  
   _ds.write(0xBE); // Read Scratchpad


   for (int i = 0; i < 9; i++) { // we need 9 bytes
      data[i] = _ds.read();
   }

   _ds.reset_search();

   byte MSB = data[1];
   byte LSB = data[0];

   float tempRead = ((MSB << 8) | LSB); //using two's compliment
   float TemperatureSum = tempRead / 16;

   return TemperatureSum;
}