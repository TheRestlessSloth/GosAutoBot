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
//|RotBicep    |90          |180      |135          |2        |
//|Shoulder    |65          |0        |35           |3        |
//|RotShoulder |165         |0        |90           |4        |
//------------------------------------------------------------
//|Thumb       |165         |90       |127          |6        |
//|Index       |165         |90       |127          |7        |
//|Middle      |165         |90       |127          |8        |
//|Ring        |165         |90       |127          |9        |
//|Pinky       |165         |90       |127          |10       |
//------------------------------------------------------------

//------------------------Libraries---------------------------
#include <Wire.h>
#include <Multiservo.h>

//------------------------Hand defines------------------------
#define ThumbF 6
#define IndexF 7
#define MiddleF 8
#define RingF 9
#define PinkyF 10

//------------------------Arm defines-------------------------
#define Wrist 0
#define Bicep 1
#define RotBicep 2
#define Shoulder 3
#define RotShoulder 4

//------------------------Other defines-----------------------
#define offset 10
#define maxi 0
#define mini 1
#define midi 2

//------------------------Declaring servos--------------------
Multiservo thuf; Multiservo indf; Multiservo midf; Multiservo rinf; Multiservo pinf;
Multiservo wr; Multiservo bi; Multiservo rbi; Multiservo sho; Multiservo rsho;

//------------------------Position arrays---------------------
byte s[3]  = {65,    17,    35};
byte rs[3] = {165,   0,    90};
byte b[3]  = {160,   75,   110};
byte rb[3] = {90,    180,    135};
byte w[3]  = {170,   0,    85};
byte f[3]  = {165,   90,   127};
int pos = 0;
//------------------------Declaring functions-----------------
void servo_init();

void straight_arm();
void folded_arm();
void halfFolded_arm();

void straight_hand();
void folded_hand();
void halfFolded_hand();
void rock_hand();

//-------------------------Program start----------------------
void setup() {
  servo_init();
  Serial.begin(9600);
  Serial.setTimeout(50*1000);
}

void loop() {
   if (Serial.available() > 0){
    pos = Serial.parseInt();
    switch ( pos )
    {
      case 1:
      straight_arm();
      break;
      case 2:
        folded_arm();
      break;
      default:
        straight_arm();
      break;
    }
    Serial.print("pos = ");
    Serial.println(pos);
  }  
}

//-------------------------Servo initialisation---------------
void servo_init() {
  thuf.attach(ThumbF);
  indf.attach(IndexF);
  midf.attach(MiddleF);
  rinf.attach(RingF);
  pinf.attach(PinkyF);

  wr.attach(Wrist);
  bi.attach(Bicep);
  rbi.attach(RotBicep);
  sho.attach(Shoulder);
  rsho.attach(RotShoulder);
}

//-------------------------Arm--------------------------------
void straight_arm() {
  wr.write(w[midi]);        //Wrist is in middle position
  bi.write(b[mini]);        //Arm is unbended
  rbi.write(rb[mini]);      //Arm is facing torso 
  sho.write(s[mini]);       //Shoulder is down
  rsho.write(rs[mini]);     //Arm is down
}

void folded_arm() {
  wr.write(w[midi]);        //Wrist is in middle position
  bi.write(b[mini]);        //Arm is bended
  rbi.write(rb[mini]);      //Arm is facing forward
  sho.write(s[mini]);       //Плечи ровно
  rsho.write(rs[maxi]);     //Руки по швам,не вытянуты вперёд
}

void halfFolded_arm() {
  wr.write(w[midi]);
  bi.write(b[maxi]);
  rbi.write(rb[mini]);
  sho.write(s[maxi]);
  rsho.write(rs[midi]);
}

//-------------------------Hand-------------------------------
void straight_hand() {
  thuf.write(f[mini]);
  indf.write(f[mini]);
  midf.write(f[mini]);
  rinf.write(f[mini]);
  pinf.write(f[mini]);
}

void rock_hand() {
  thuf.write(f[mini]);
  indf.write(f[mini]);
  midf.write(f[maxi]);
  rinf.write(f[maxi]);
  pinf.write(f[mini]);
}

void halfFolded_hand(){
  thuf.write(f[midi]);
  indf.write(f[midi]);
  midf.write(f[midi]);
  rinf.write(f[midi]);
  pinf.write(f[midi]);
}
