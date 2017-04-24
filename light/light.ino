#include <ArduinoJson.h>

const int pinLight = A0;

void setup()
{
    Serial.begin(9600);
    Serial1.begin(57600);
}

void loop()
{
    int value = analogRead(pinLight);
  /*  Serial.println(value);
    Serial1.print("light = ");
    Serial1.println(value , DEC);*/

    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& Jasonroot = jsonBuffer.createObject();
    Jasonroot["sensor"] = "Light";
    Jasonroot["data"] = value;

    Jasonroot.printTo(Serial1);
    Jasonroot.prettyPrintTo(Serial);
    Serial1.print("\r\n");
    delay(1000);
}
