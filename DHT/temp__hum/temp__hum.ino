#include <ArduinoJson.h> /* Got wrong grammar */
#include <dht.h>   
  
#define dht_dpin A0
  
dht DHT;   
  
void setup(){   
  Serial.begin(9600);   
  delay(300);             //Let system settle   
  Serial.println("Humidity and temperature\n\n");   
  delay(700);             //Wait rest of 1000ms recommended delay before   
  Serial1.begin(57600);                    
}
  
void loop(){   
  DHT.read11(dht_dpin);   //去library裡面找DHT.read11  
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& Jasonroot = jsonBuffer.createObject();

  //set value sequence every 5 seconds
  double avg_temp=0 , avg_hum=0;
  for(int i = 0; i<5 ;i++){
      avg_temp+=DHT.temperature;
      avg_hum+=DHT.humidity;
      delay(1000);
  }
  avg_temp/=5;avg_hum/=5;
  
  
  Jasonroot["sensor"] = "Temp";
  Jasonroot["data"] = avg_temp;//String
  Jasonroot.printTo(Serial1);
  Jasonroot.prettyPrintTo(Serial);
  Serial1.print("\r\n");
  delay(2000);
  Jasonroot["sensor"] = "Hum";
  Jasonroot["data"] = avg_hum;//String
  Jasonroot.printTo(Serial1);
  Jasonroot.prettyPrintTo(Serial);
  Serial1.print("\r\n");
  
 
/*  Serial.print("Humidity = ");   
  Serial.print(DHT.humidity);   
  Serial.print("% ");   
  Serial.print("temperature = ");   
  Serial.print(DHT.temperature);   
  Serial.println("C ");   */
  
  delay(1000);             
}  
