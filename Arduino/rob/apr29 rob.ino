//------------------------Libraries---------------------------
#include <Wire.h>
#include <Multiservo.h>
#include <HCSR04.h>

#define OutPin 13
#define InPin 3
#define NUM_READ 3

float procval = 0;
float pv = 0;
volatile boolean flag = false;
//------------------------Declaring servos and sensors--------------------
Multiservo th; Multiservo in; Multiservo mi; Multiservo ri; Multiservo pi;
Multiservo wr; Multiservo bi; Multiservo rb; Multiservo sh; Multiservo rs;
HCSR04 hc(5,6); //HCSR04 (trig pin , echo pin)

struct limbSt
{
  byte maxi;
  byte mini;
  byte midi;
  byte servpin;
};

limbSt WristSt       = {170,    0,    85,    0};
limbSt BicepSt       = {165,   65,   110,    1};
limbSt RotBicepSt    = {180,   0,   90,    2};
limbSt ShoulderSt    = {65,    20,    35,    3};
limbSt RotShoulderSt = {165,    0,    90,    4};

limbSt ThumbSt       = {165,   90,   127,    6};
limbSt IndexSt       = {165,   90,   127,    7};
limbSt MiddleSt      = {165,   90,   127,    8};
limbSt RingSt        = {165,   90,   127,    9};
limbSt PinkySt       = {165,   90,   127,   10};

//------------------------Declaring functions-----------------
void init_rob();
void wave_arm ();
void start_arm ();

void far()
{
  Serial.println("Far");
}

void near()
{
  Serial.println("Mid");
  wave_arm();
  while(true)
  {
    procval = findMedianN_optim(midArifm(hc.dist()));
    Serial.println(procval);
    if (procval > 120)
      break;
    delay(200);
  }
  for(int i = 0; i < NUM_READ; i++) findMedianN_optim(midArifm(0));
}

void toonear()
{
  Serial.println("Too close");
}

void setup()
{ 
  init_rob();
}

void loop()
{ 
  procval = midArifm(findMedianN_optim(hc.dist())); 
  Serial.print(procval,0);
  Serial.print("\t\t");
  if (procval > 80)
    far();
  else if (procval <= 80 && procval > 20)
    {
    near();
    Serial.println("Good bye!");
    }
  else
    toonear();
    
  delay(200);
}

float midArifm (float val) {
  float sum = 0;
  for (int i = 0; i < NUM_READ; i++)
    sum += val;
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
    middle = (b <= c) ? b : c;
  else
  {
    if((b <= a ) && (b <= c))
      middle = (a <= c) ? a : c;
    else
      middle = (a <= b) ? a : b;
  }
  return middle;
}

float findMedianN_optim(float val) {
  static float buffer[NUM_READ];  // статический буфер
  static byte count = 0;
  buffer[count] = val;
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

void start_arm ()
{
  Serial.println("Start position of arm");
  wr.write(WristSt.midi);
  bi.write(BicepSt.mini);
  rb.write(RotBicepSt.midi);
  sh.write(ShoulderSt.mini);
  rs.write(RotShoulderSt.mini);
}

void folded_arm ()
{
  Serial.println("folded_arm");
  wr.write(WristSt.midi);
  bi.write(BicepSt.maxi);
  rb.write(RotBicepSt.midi);
  sh.write(ShoulderSt.maxi);
  rs.write(RotShoulderSt.maxi);

  delay(10000);
}

void wave_arm ()
{
      Serial.println("Waving arm");
      wr.write(WristSt.maxi);
      rb.write(RotBicepSt.midi);
      bi.write(BicepSt.maxi);
      rs.write(RotShoulderSt.midi);
      delay(2500);
      
      for(int i=0; i<4; i++){
      rb.write(RotBicepSt.maxi);
      delay(1500);
      rb.write(RotBicepSt.mini);
      delay(1500);
      }
      
      start_arm();
      delay(5000);
}

void init_rob()
{
  wr.attach(WristSt.servpin);
  bi.attach(BicepSt.servpin);
  rb.attach(RotBicepSt.servpin);
  sh.attach(ShoulderSt.servpin);
  rs.attach(RotShoulderSt.servpin);

  th.attach(ThumbSt.servpin);
  in.attach(IndexSt.servpin);
  mi.attach(MiddleSt.servpin);
  ri.attach(RingSt.servpin);
  pi.attach(PinkySt.servpin);
  
  Serial.begin(9600); 
  Serial.setTimeout(50*1000);
  pinMode(OutPin,OUTPUT);
  pinMode(InPin,INPUT_PULLUP);

  Serial.println("Initialization");
  
  start_arm();
}
