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
  switch (limb)
  {
  case 0:
    wr.write(pos);
    Serial.print("wrist");
    break;
  case 1:
    bi.write(pos);
    Serial.print("Bicep");
    break;
  case 2:
    rb.write(pos);
    Serial.print("Rotation of bicep");
    break;
  case 3:
    sh.write(pos);
    Serial.print("Shoulder");
    break;
  case 4:
    rs.write(pos);
    Serial.print("rotation of shoulder");
    break;
  default:
    Serial.print("not an option, back to normal");
    break;
  }
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

//-------------------------------------------------------
void parsemot()
{
  if (Serial.available() > 0){
    Serial.print("U r moovin ");
    
    int limb = Serial.parseInt(); 
    Serial.print(limb);
    
    Serial.print(" in a ");
    
    int pos = Serial.parseInt(); 
    Serial.print(pos);
    
    Serial.println(" posishn");
    
    move_arm (limb, pos);
  }  
}
