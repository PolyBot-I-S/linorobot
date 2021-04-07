#if (ARDUINO >= 100)
    #include <Arduino.h>
#else
    #include <WProgram.h>
#endif

#include <math.h>
#include "Motor.h"


Controller motor1_controller(7, 5, 6);
Controller motor2_controller(16, 14, 15);


void setup(){

  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  
  delay(10);
}


void loop() {
  motor1_controller.spin(50); 
  motor2_controller.spin(50);
  delay(10);
}
