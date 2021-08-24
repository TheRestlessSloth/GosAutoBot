//Test of servos by TheRestlessSloth
// Как работать с кодом? Заливаешь на микроконтроллер, и не отсоединяя от компа входишь в "Монитор порта" или же "Serial monitor"
// Когда подключишь серву к пину 0 на шилде, есть несколько загвосток...
// 1. Правильное положение потенциометра (потенциометр должен не только стоять в измеримом положении (у некоторых серв 1 - 180, у некоторых 1 - 140) при начальном тесте и установке, но так же и его вращение должно быть обратным вращению самого сочлениения)
// Это нужно для того, чтобы внутренняя электроника работала на уменьшение положения между нужным значением и моментальным значением. Советую сначала снять серву, прикинуть, как она будет стоять, и после тестов ставить на место
// 2. С помощью этого простого кода можно так же перейти ко второму, не менее важному шагу... Замер значений рабочей области каждого из сочленений.
// Для этого подключаешь нужную серву, и после этого минимально меняешь углы, сначала в сторону увеличения, потом уменьшения до тех пор пока сочленение (например, локоть придёт в своё максимальное положение)
// !!Важно!! Если серва не двигается и сильно трещит это может быть по нескольким проблемам:
//  - Достигнут "Экстремум"
//  - Нехватает питания (Обычно пяти вольт 2х ампер хватает с головой)
//  - Самый неприятный, но мне не встречался, это неполадки с самой сервой (Типо обкусанных зубьев на редукторе)
// !!Важно!! При запуске программы "по дефолту" выставляется значение 70 град (Кстати да, нужно скачать с сайта амперки библиотеку Multiservo, для того чтобы всё работало), значения принимаются в градусах
// Пока вроде всё, разберёшься с этим - кину следующие файлы
//------------------------Libraries---------------------------
#include <Wire.h>
#include <Multiservo.h>
//--Declare serv
Multiservo smtg;

float a = 0;

void setup()
{ 
  smtg.attach(0);
  
  Serial.begin(9600); 
  Serial.setTimeout(50*1000);
  Serial.println("Initialization");

  Serial.println(a);
  smtg.write(a);
}

void loop()
{
  if (Serial.available() > 0)
  {
    parsemot(); //parse angle
    smtg.write(a);
  }
}

void parsemot()
{
  if (Serial.available() > 0)
  {
    Serial.println("\nPosition \n");
    a = Serial.parseInt();
    Serial.print("angle is ");
    Serial.println(a);
  }  
}
