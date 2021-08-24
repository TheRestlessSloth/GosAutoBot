#include <HCSR04.h>
float procval = 0;
const int NUM_READ = 20;

HCSR04 hc(5,6); //HCSR04 (trig pin , echo pin)

void setup()
{ 
  Serial.begin(9600); 
}

void loop()
{ 
  procval = findMedianN_optim(midArifm(hc.dist())); 
  Serial.println(procval); 
  analogWrite(3,procval);
  delay(200);
}//return curent distance in serial

float midArifm (float dista) {
  float sum = 0;
  for (int i = 0; i < NUM_READ; i++)
    sum += dista;
  return (sum / NUM_READ);
}

float med(float val){
  static float buff[3];
  static byte count = 0;
  
  buff[count] = val;
  if (++count >= 3) count = 0;

  float a = buff[0];
  float b = buff[1];
  float c = buff[2];
  
  float middle = 0; 
  
  if ((a <= b) && (a <= c))
  {
    middle = (b <= c) ? b : c;
  }
  else
  {
    if((b <= a ) && (b <= c))
    {
      middle = (a <= c) ? a : c;
    }
    else
    {
      middle = (a <= b) ? a : b;
    }
  }
  return middle;
}

float findMedianN_optim(float newVal) {
  static float buffer[NUM_READ];  // статический буфер
  static byte count = 0;
  buffer[count] = newVal;
  if ((count < NUM_READ - 1) and (buffer[count] > buffer[count + 1])) {
    for (int i = count; i < NUM_READ - 1; i++) {
      if (buffer[i] > buffer[i + 1]) {
        float buff = buffer[i];
        buffer[i] = buffer[i + 1];
        buffer[i + 1] = buff;
      }
    }
  } else {
    if ((count > 0) and (buffer[count - 1] > buffer[count])) {
      for (int i = count; i > 0; i--) {
        if (buffer[i] < buffer[i - 1]) {
          float buff = buffer[i];
          buffer[i] = buffer[i - 1];
          buffer[i - 1] = buff;
        }
      }
    }
  }
  if (++count >= NUM_READ) count = 0;
  return buffer[(int)NUM_READ / 2];
}
