#include <Wire.h>
#include <Multiservo.h>

Multiservo wrist, sholder, rsholder, bicep, rbicep;
Multiservo thumb, index, middle, ring, pinky; 

//bicep min = 47; max = 120;
//rsholder min = 90; max = 180;
//rbicep mid = 90; min = 0; max = 105
//sholder min = 90; max = 180;

#define MAXI 180
#define MINI 0 

void servosAttach()
{
  wrist.attach(17);
  thumb.attach(0);
  index.attach(1);
  middle.attach(2);
  ring.attach(3);
  pinky.attach(4);
  rsholder.attach(16);
  sholder.attach(14);
  bicep.attach(13);
  rbicep.attach(15);
}

void servosDetach()
{
  wrist.detach();
  thumb.detach();
  index.detach();
  middle.detach();
  ring.detach();
  pinky.detach();
  rsholder.detach();
  sholder.detach();
  bicep.detach();
  rbicep.detach();
}

void startPose()
{
  wrist.write(90);
  bicep.write(47);
  rsholder.write(90);
  rbicep.write(90);
  sholder.write(90);
  delay(1000);
}

void setup(void)
{
  Wire.begin();
  
  servosAttach();
  startPose();
  /*
  for (pos = MINI; pos <= MAXI; pos += 1) // goes from 0 degrees to 180 degrees
  { // in steps of 1 degree
    foo(pos);
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = MAXI; pos >= MINI; pos -= 1) // goes from 180 degrees to 0 degrees
  {
    foo(pos);
    delay(15);                       // waits 15ms for the servo to reach the position
  }*/
  //bicep.write(47);
  fingers_move((MAXI-MINI)/2);
  //servosDetach();
}

void fingers_move(int pos)
{ 
    thumb.write(pos);
    index.write(MAXI - pos);
    middle.write(pos);
    ring.write(MAXI - pos);
    pinky.write(MAXI - pos);
}

void loop(void)
{
  
}

/*class limb
{
  private:
  limb(string limb_name, int servo_pin, int max_val, int min_val)
  {
    Multiservo limb_name
  }
  int maxi;
  int mini;
  public: 

}*/
