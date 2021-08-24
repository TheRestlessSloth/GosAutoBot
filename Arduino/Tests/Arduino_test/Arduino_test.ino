int i = 0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
i++;
Serial.println(3*sin(3*cos(5*sin(0.01*i))));
delay(50);
}
