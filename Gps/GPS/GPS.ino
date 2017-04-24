#include <SoftwareSerial.h>
#include "TinyGPS++.h"
TinyGPSPlus gps;

SoftwareSerial SoftSerial(8, 9);             // COM port D5
unsigned char buffer[64];                   // buffer array for data receive over serial port
int count=0;                                // counter for buffer array
 
void setup()
{
    SoftSerial.begin(9600);                 // the SoftSerial baud rate
    Serial.begin(9600);                     // the Serial port of Arduino baud rate.
}
 
void loop()
{
    if (SoftSerial.available())                     // if date is coming from software serial port ==> data is coming from SoftSerial shield
    {
        while(SoftSerial.available())               // reading data into char array
        {
            gps.encode(SoftSerial.read());
            buffer[count++]=SoftSerial.read();      // writing data into array
            if(count == 64)break;
           
              Serial.print("LAT=");  Serial.println(gps.location.lat(), 6);
              Serial.print("LONG="); Serial.println(gps.location.lng(), 6);
              Serial.print("ALT=");  Serial.println(gps.altitude.meters()); 
            
        }
        //Serial.write(buffer,count);                 // if no data transmission ends, write buffer to hardware serial port
        clearBufferArray();                         // call clearBufferArray function to clear the stored data from the array
        count = 0;                                  // set counter of while loop to zero
 
 
    }
    if (Serial.available())                 // if data is available on hardware serial port ==> data is coming from PC or notebook
    SoftSerial.write(Serial.read());        // write it to the SoftSerial shield
}
 
void clearBufferArray()                     // function to clear buffer array
{
    for (int i=0; i<count;i++)
    { buffer[i]=NULL;}                      // clear all index of array with command NULL
}
