// Укажем, что к каким пинам подключено
int in = 10; 
int out = 11;  
int f = 36000;
double t1 = 1000/f;

void setup() { 
  Serial.begin (9600); 
  pinMode(in, OUTPUT); 
  pinMode(out, INPUT); 
} 
 
void loop() { 
  int duration, distance;
  
  // для большей точности установим значение LOW на пине Trig
  digitalWrite(in, LOW);

  for(int i=0; i<11; i++)
  {
  delayMicroseconds(27); 
  digitalWrite(in, HIGH);
  
  delayMicroseconds(27); 
  digitalWrite(in, LOW);
  }
  
  duration = pulseIn(out, HIGH); 
 
  // Рассчитаем расстояние
  distance = duration / 58;
  
  // Выведем значение в Serial Monitor
  Serial.print(distance); 
  Serial.println(" cm"); 
  delay(100);
}
