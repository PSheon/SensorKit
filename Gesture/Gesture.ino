#include <ArduinoJson.h>
#include <Wire.h>
#include "paj7620.h"


#define GES_REACTION_TIME    500       // reaction time .
#define GES_ENTRY_TIME      800       // Forward/Backward time .
#define GES_QUIT_TIME     1000

void setup() {
  uint8_t error = 0;

  Serial.begin(9600);
  Serial1.begin(57600);
  Serial.println("\nPAJ7620U2 TEST DEMO: Recognize 9 gestures.");

  error = paj7620Init();      // initialize Paj7620
  if (error) {
    Serial.print("INIT ERROR,CODE:");
    Serial.println(error);
  }
  else {
    Serial.println("INIT OK");
  }
  Serial.println("Please input your gestures:\n");
}

void loop() {
  uint8_t data = 0, data1 = 0, error;
  
  error = paj7620ReadReg(0x43, 1, &data); // Read Bank_0_Reg_0x43/0x44 for gesture result.
  if (!error) {
    String jobj_data = "";
    switch (data) {
      case GES_RIGHT_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_FORWARD_FLAG) {
          Serial.println("Forward");
          jobj_data = "Forward";
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) {
          Serial.println("Backward");
          jobj_data = "Backward";
          delay(GES_QUIT_TIME);
        }
        else {
          Serial.println("Right");
          jobj_data = "Right";
        }          
        break;
      case GES_LEFT_FLAG: 
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_FORWARD_FLAG) {
          Serial.println("Forward");
          jobj_data = "Forward";
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) {
          Serial.println("Backward");
          jobj_data = "Backward";
          delay(GES_QUIT_TIME);
        }
        else {
          Serial.println("Left");
          jobj_data = "Left";
        }          
        break;
      case GES_UP_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_FORWARD_FLAG) {
          Serial.println("Forward");
          jobj_data = "Forward";
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) {
          Serial.println("Backward");
          jobj_data = "Backward";
          delay(GES_QUIT_TIME);
        }
        else {
          Serial.println("Up");
          jobj_data = "Up";
        }          
        break;
      case GES_DOWN_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_FORWARD_FLAG) {
          Serial.println("Forward");
          jobj_data = "Forward";
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) {
          Serial.println("Backward");
          jobj_data = "Backward";
          delay(GES_QUIT_TIME);
        }
        else {
          Serial.println("Down");
          jobj_data = "Down";
        }          
        break;
      case GES_FORWARD_FLAG:
        Serial.println("Forward");
        jobj_data = "Forward";
        delay(GES_QUIT_TIME);
        break;
      case GES_BACKWARD_FLAG:     
        Serial.println("Backward");
        jobj_data = "Backward";
        delay(GES_QUIT_TIME);
        break;
      case GES_CLOCKWISE_FLAG:
        Serial.println("Clockwise");
        jobj_data = "Clockwise";
        break;
      case GES_COUNT_CLOCKWISE_FLAG:
        Serial.println("anti-clockwise");
        jobj_data = "anti-clockwise";
        break;  
      default:
        paj7620ReadReg(0x44, 1, &data1);
        if (data1 == GES_WAVE_FLAG) {
          Serial.println("wave");
          jobj_data = "wave";
        }
        break;
    }
    if(jobj_data != "") {
      StaticJsonBuffer<50> jsonBuffer;
      JsonObject& Jasonroot = jsonBuffer.createObject();
      Jasonroot["sensor"] = "Gesture";
      Jasonroot["data"] = jobj_data;
      delay(10);
      Jasonroot.printTo(Serial1);
      Jasonroot.prettyPrintTo(Serial);
      Serial1.print("\r\n");
    }
  }
  delay(200);
}
