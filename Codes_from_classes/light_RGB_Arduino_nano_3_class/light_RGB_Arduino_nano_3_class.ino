const int rLEDpin = 3;
const int gLEDpin = 4;
const int bLEDpin = 5;

void setup(){
  pinMode(rLEDpin, OUTPUT);
  pinMode(gLEDpin, OUTPUT);
  pinMode(bLEDpin, OUTPUT);

}

void loop(){
  digitalWrite(rLEDpin, LOW);
  digitalWrite(gLEDpin, HIGH);
  digitalWrite(bLEDpin, LOW);
  delay(1000);

  digitalWrite(rLEDpin, HIGH);
  digitalWrite(gLEDpin, LOW);
  digitalWrite(bLEDpin, HIGH);
  delay(1000);

  digitalWrite(rLEDpin, LOW);
  digitalWrite(gLEDpin, HIGH);
  digitalWrite(bLEDpin, LOW);
  delay(1000);

}