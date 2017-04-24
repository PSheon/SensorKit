#include <ArduinoJson.h>
#include <SoftwareSerial.h>
int incomeByte[6];
int data;
int z=0;
int sum;
unsigned long error;

SoftwareSerial mySerial(5, 10); // RX, TX

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(38400);
  Serial1.begin(57600); 
  // set the data rate for the SoftwareSerial port
  mySerial.begin(2400);
  
}

void loop() { // run over and over
  while (mySerial.available()){
    
    data=mySerial.read();
    if(data == 170){
      z=0;
      incomeByte[z]=data;
    }
    else{
      z++;
      incomeByte[z]=data;
    } 
    if(z==6)
    {
      sum=incomeByte[1]+ incomeByte[2]+ incomeByte[3] + incomeByte[4];
 
      if(incomeByte[5]==sum && incomeByte[6]==255 )
      {
 
        // Serial.print("Data OK! |");
       /* for(int k=0;k<7;k++)
        {
          Serial.print(incomeByte[k]);
          Serial.print("|");
        } */
 
       // Serial.print(" Vo=");
        float vo=(incomeByte[1]*256.0+incomeByte[2])/1024.0*5.00;
       // Serial.print(vo,3);
        //Serial.print("v | ");
        float c=vo*700;
        float avg_pm=0;
        for(int i=0;i<5;i++){
          avg_pm+=c;
          delay(400);
        }
//        StaticJsonBuffer<200> jsonBuffer;
//        JsonObject& Jasonroot = jsonBuffer.createObject();
        
  
        avg_pm/=5;
        
        Serial.print(" PM2.5 = ");
        Serial.print(c,2);
        Serial.print("ug/m3 ");
        Serial.println();

//         Jasonroot["sensor"] = "PM2.5";
//         Jasonroot["data"] = avg_pm;//String
//         Jasonroot.printTo(Serial1);
//         Jasonroot.prettyPrintTo(Serial);
//         Serial.print("\r\n");
      }
     
      
    
      else{
        z=0;
        mySerial.flush();
        data='/0';
        for(int m=0;m<7;m++){
          incomeByte[m]=0;
        }
        /* 
         error++;
         Serial.print(" ### This is ");
         Serial.print(error);
         Serial.println(" Error ###");
         */
      }
      z=0;
    }
  }
 
  
}
