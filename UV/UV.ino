///UV
#include <ArduinoJson.h>

const int pinLight =A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(300);
  Serial1.begin(57600);
}

void loop() {
  // put your main code here, to run repeatedly:
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& Jasonroot = jsonBuffer.createObject();
  double v =0;double intensity = 0; double uv_index = 0;
  //for(int i=0;i<5;i++){  
    long analog = 0;
    for(int j = 0; j < 1024; j++){
      analog += analogRead(A0);
      delay(2);
    }
    analog >>= 10; // 算出平均值
    
    v+= analog * 4.98 / 1023.0; // 電壓
    intensity+= v * 307; // 照射強度
    uv_index+= intensity / 200; // 紫外線指數
 /* }
  v/=5;intensity/=5;uv_index/=5;*/
  
  /*Serial.print("The voltage value: ");
  Serial.print(v);
  Serial.println("V");

  Serial.print("Illumination intensity: ");
  Serial.print(intensity);
  Serial.println("mW/m^2");

  Serial.print("UV index: ");
  Serial.println(uv_index);
  */

  Jasonroot["sensor"] = "UV";
  Jasonroot["intensity"] = intensity;
  Jasonroot["uvi"] = uv_index*6.352;
  Jasonroot.printTo(Serial1);
  Jasonroot.prettyPrintTo(Serial);
  Serial1.print("\r\n");
  delay(200);
}
