//------------------------Libraries---------------------------
#include <Wire.h>
#include <Multiservo.h>


Multiservo smtg;

float angle = 70;
float a[2] = {3, 4};
float r = 50;

void setup()
{ 
  smtg.attach(0);
  
  Serial.begin(9600); 
  Serial.setTimeout(50*1000);
  Serial.println("Initialization");

  float distancea = sqrt(pow(a[0],2)+pow(a[1],2));
  double alpha = 180*atan(a[1]/a[0])/PI;

  Serial.println(a[0]);
  Serial.println(a[1]);
  Serial.println(distancea);
  Serial.println(alpha);
  smtg.write(alpha);
}

void loop()
{
  if (Serial.available() > 0)
  {
    parsemot();
    calc(a[0], a[1]);
    smtg.write(angle);
  }
}

void parsemot()
{
  if (Serial.available() > 0)
  {
    Serial.println("\nPosition \n");
    a[0] = Serial.parseInt();
    Serial.print("x ");
    Serial.println(a[0]);
    a[1] = Serial.parseInt();
    Serial.print("y ");
    Serial.println(a[1]);
  }  
}

void calc(float x, float y)
{
  float distancea = sqrt(pow(a[0],2)+pow(a[1],2));
    angle = 180*atan(y/x)/PI;
    Serial.print("d ");
    Serial.println(distancea);
    Serial.print("angle(in deg) ");
    Serial.println(angle);
}
