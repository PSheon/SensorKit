#include <ArduinoJson.h>
int incomingByte = 0;
unsigned long systemtime , currenttime;
String data ="";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  
}
//digitalWrite(13, HIGH);
void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available() > 0){
    incomingByte = Serial.read();
    data += (char)incomingByte; 
    
  }
  
  /*  if(data.equals("123\r\n")){
      digitalWrite(13, HIGH);
    }
    else{
      digitalWrite(13, LOW);
    }
    delay(100);
    data = "";
 */
  digitalWrite(13, HIGH);
  systemtime = millis();
  while(!digitalRead(13)){
    currenttime = millis();
    if(currenttime-systemtime >= 500){
      Serial.println("sustain 500 mss");
    }
  }
  delay(100);
 
}

