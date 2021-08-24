//╔══╦╗░░╔═╗░╔═╦╗░░░░╔═╦═╦══╗░░░╔╗╔╗░
//╚╗╔╣╚╦═╣╬╠═╣═╣╚╦╗╔═╣═╣═╣══╬╗╔═╣╚╣╚╗
//░║║║║║╩╣╗╣╩╬═║╔╣╚╣╩╬═╠═╠══║╚╣╬║╔╣║║
//░╚╝╚╩╩═╩╩╩═╩═╩═╩═╩═╩═╩═╩══╩═╩═╩═╩╩╝
//░░░░╔═╗░░░░╔╗░░╔╗░░╔╗░
//╔═╦═╣═╬═╗╔╦╣╚╦═╣╚╦═╣╚╗
//║╬║╬╠═║╬╚╣║║╔╣╬║╬║╬║╔╣
//╠╗╠═╩═╩══╩═╩═╩═╩═╩═╩═╝
//╚═╝░░░░░░░░░░░░░░░░░░░
//------------------------------------------------------------
//|            |Max         | Min     |Mid          |Servo pin|
//|Wrist       |170         |0        |85           |0        |
//|Bicep       |160         |65       |110          |1        |
//|RotBicep    |180         |90       |135          |2        |
//|Shoulder    |65          |17       |35           |3        |
//|RotShoulder |165         |0        |90           |4        |
//------------------------------------------------------------
//|Thumb       |165         |90       |127          |6        |
//|Index       |165         |90       |127          |7        |
//|Middle      |165         |90       |127          |8        |
//|Ring        |165         |90       |127          |9        |
//|Pinky       |165         |90       |127          |10       |
//------------------------------------------------------------
//move(arm_finger,mid)
//------------------------Libraries---------------------------
#include <Wire.h>
#include <Multiservo.h>

//------------------------Declaring servos--------------------
Multiservo th; Multiservo in; Multiservo mi; Multiservo ri; Multiservo pi;
Multiservo wr; Multiservo bi; Multiservo rb; Multiservo sh; Multiservo rs;

//------------------------Limb structure----------------------
struct limbSt
{
  byte maxi;
  byte mini;
  byte midi;
  byte servpin;
};

struct limbSt WristSt       = {170,    0,    85,    0};
struct limbSt BicepSt       = {165,   65,   110,    1};
struct limbSt RotBicepSt    = {180,   0,   90,    2};
struct limbSt ShoulderSt    = {65,    20,    35,    3};
struct limbSt RotShoulderSt = {165,    0,    90,    4};

struct limbSt ThumbSt       = {165,   90,   127,    6};
struct limbSt IndexSt       = {165,   90,   127,    7};
struct limbSt MiddleSt      = {165,   90,   127,    8};
struct limbSt RingSt        = {165,   90,   127,    9};
struct limbSt PinkySt       = {165,   90,   127,   10};


//------------------------Declaring functions-----------------
void servo_init();
void move_arm (int limb, int pos);
void wave_arm ();
void start_arm ();
void parsemot();
//------------------------Some useful defines-----------------
#define arm 0
#define hand 1
#define unfolded 0
#define folded 1

//-------------------------Program start----------------------
void setup() {
  servo_init();
  Serial.begin(9600);
  Serial.setTimeout(50*1000);
  start_arm();
  //folded_arm();
  wave_arm();
}

void loop() {
  parsemot();
}

//-------------------------Servo initialisation---------------
void servo_init() {
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
}

//-------------------------Moving function--------------------
void move_arm (int limb, int pos)
{
  if (limb == arm)
  {
    if (pos == unfolded)
    {
      Serial.println("Am is unfolded");
      wr.write(WristSt.midi);
      bi.write(BicepSt.mini);
      rb.write(RotBicepSt.midi);
      sh.write(ShoulderSt.mini);
      rs.write(RotShoulderSt.mini);
    }
    else if (pos == folded)
    {
      Serial.println("Am is folded");
      wr.write(WristSt.midi);
      bi.write(BicepSt.maxi);
      rb.write(RotBicepSt.midi);
      sh.write(ShoulderSt.midi);
      rs.write(RotShoulderSt.midi);
    }
    else
      Serial.println("Sowwy, a kant moove ma am");
  }
  else if (limb == hand)
  {
    if (pos == unfolded)
    {
      Serial.println("Hand is unfolded");
      th.write(ThumbSt.mini);
      in.write(IndexSt.mini);
      mi.write(RotBicepSt.midi);
      ri.write(RingSt.mini);
      pi.write(PinkySt.mini);
    }
    else if (pos == folded)
    {
      Serial.println("Hand is folded");
      th.write(ThumbSt.maxi);
      in.write(IndexSt.maxi);
      mi.write(RotBicepSt.midi);
      ri.write(RingSt.maxi);
      pi.write(PinkySt.maxi);
    }
    else
      Serial.println("Sowwy, a kant moove ma hand");
  }
  else
    Serial.println("Sowwy, that is not an opshn");
}
//---------------------------------------------------------
void start_arm ()
{
  wr.write(WristSt.midi);
  bi.write(BicepSt.mini);
  rb.write(RotBicepSt.midi);
  sh.write(ShoulderSt.mini);
  rs.write(RotShoulderSt.mini);
}

//---------------------------------------------------------
void folded_arm ()
{
  wr.write(WristSt.midi);
  bi.write(BicepSt.maxi);
  rb.write(RotBicepSt.midi);
  sh.write(ShoulderSt.maxi);
  rs.write(RotShoulderSt.maxi);

  delay(10000);
}

//---------------------------------------------------------
void wave_arm ()
{
      Serial.println("Am is waving");
      wr.write(WristSt.maxi);
      rb.write(RotBicepSt.maxi);
      bi.write(BicepSt.maxi);
      rs.write(RotShoulderSt.mini);
      sh.write(ShoulderSt.maxi);
      delay(2500);
      
      for(int i=0; i<4; i++){
      bi.write(BicepSt.mini);
      delay(1000);
      bi.write(BicepSt.maxi);
      delay(1000);
      }
      
      start_arm();
}
//-------------------------------------------------------
void parsemot()
{
  if (Serial.available() > 0){
    Serial.print("U r moovin ");
    int limb = Serial.parseInt(); //(0 - arm, 1 - hand)
    Serial.print(limb);
    Serial.print(" in a ");
    int pos = Serial.parseInt(); //(0 - unfolded, 1 - folded)
    Serial.print(pos);
    Serial.println(" posishn");
    move_arm (limb, pos);
  }  
}
