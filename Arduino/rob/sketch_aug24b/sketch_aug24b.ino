#include <Wire.h>
#include <Multiservo.h>

#define MULTISERVO_PIN 17
 
Multiservo myservo;

int mini = 10;
int maxi = 95;
int timeout = 50;

  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  Wire.begin();
  myservo.attach(MULTISERVO_PIN);
   // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
  Serial.setTimeout(timeout*1000);
}

void loop() {
  /*for (pos = mini; pos <= maxi; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = maxi; pos >= mini; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }*/
  if (Serial.available() > 0){
    pos = Serial.parseInt();
    myservo.write(pos);
    Serial.print("pos = ");
    Serial.println(pos);
  }  
}
  
