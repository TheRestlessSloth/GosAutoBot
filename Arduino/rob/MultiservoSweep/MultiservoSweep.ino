#include <Wire.h>
#include <Multiservo.h>

Multiservo wrist;
Multiservo thumb, index, middle, ring, pinky; 

#define MAXI 180
#define MINI 0

int pos = 0;  

void servosAttach()
{
  wrist.attach(17);
  thumb.attach(0);
  index.attach(1);
  middle.attach(2);
  ring.attach(3);
  pinky.attach(4);
}

void servosDetach()
{
  wrist.detach();
  thumb.detach();
  index.detach();
  middle.detach();
  ring.detach();
  pinky.detach();
}

void setup(void)
{
  Wire.begin();
  
  servosAttach();
  
  for (pos = MINI; pos <= MAXI; pos += 1) // goes from 0 degrees to 180 degrees
  { // in steps of 1 degree
    foo(pos);
    delay(15);                       // waits 15ms for the servo to reach the position
  }

  for (pos = MAXI; pos >= MINI; pos -= 1) // goes from 180 degrees to 0 degrees
  {
    foo(pos);
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  
  pos = 90;
  foo(pos);
  servosDetach();
}

void foo(int pos)
{
    wrist.write(pos);    // tell servo to go to position in variable 'pos'
    thumb.write(MAXI - pos);
    index.write(pos);
    middle.write(MAXI - pos);
    ring.write(pos);
    pinky.write(pos);
}

void loop(void)
{
  
}
