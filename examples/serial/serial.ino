#include <esp32cam.h>

void setup(){

  Serial.begin(9600);
  ESP.restart();
  delay(1000);
  ESP.restart();
  delay(1000);
  
  }

void loop(){
  
  Serial.println("hola mundo");
  delay(1000);
  
  }
