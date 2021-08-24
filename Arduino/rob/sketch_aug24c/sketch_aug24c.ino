#include <Wire.h>
#include <Multiservo.h>

#define MULTISERVO_PIN 17
 
Multiservo myservo;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  myservo.attach(MULTISERVO_PIN);
}

void loop() {
  // put your main code here, to run repeatedly:
   myservo.write(20);
}
