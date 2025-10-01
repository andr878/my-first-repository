const int rLEDpin = 3;
const int bLEDpin = 4;
const int gLEDpin = 5;
const int pushButton = 2;
int buttonState = 0;
int ledcolor = 0;
String color; 

void setup(){
  Serial.begin(9600);
  pinMode(rLEDpin, OUTPUT);
  pinMode (bLEDpin, OUTPUT);
  pinMode (gLEDpin, OUTPUT);
  pinMode(pushButton,INPUT);
}

void loop(){
  buttonState = digitalRead(pushButton);
  Serial.println(color);
  if (buttonState == LOW) {
    ledcolor = ledcolor + 1;
    delay(100);
  }

  if (ledcolor == 0) {
      digitalWrite(rLEDpin, HIGH);
      digitalWrite(bLEDpin, HIGH);
      digitalWrite(gLEDpin, HIGH);
      
    }

  else if (ledcolor == 1){
    //red
      digitalWrite(rLEDpin, LOW);
      digitalWrite(bLEDpin, HIGH);
      digitalWrite(gLEDpin, HIGH);
      color = "red";
  }

 else if (ledcolor == 2){
    //green
      digitalWrite(rLEDpin, HIGH);
      digitalWrite(bLEDpin, HIGH);
      digitalWrite(gLEDpin, LOW);
      color = "green";
  }

   else if (ledcolor == 3){
    //BLUE
      digitalWrite(rLEDpin, HIGH);
      digitalWrite(bLEDpin, LOW);
      digitalWrite(gLEDpin, HIGH);
      color = "blue";
  }

   else if (ledcolor == 4){
    //Yellow
      digitalWrite(rLEDpin, LOW);
      digitalWrite(bLEDpin, HIGH);
      digitalWrite(gLEDpin, LOW);
      color = "yellow";
  }

   else if (ledcolor == 5){
    //PURPLE
      digitalWrite(rLEDpin, LOW);
      digitalWrite(bLEDpin, LOW);
      digitalWrite(gLEDpin, HIGH);
      color = "purple";
  }

   else if (ledcolor == 6){
    //CYAN
      digitalWrite(rLEDpin, HIGH);
      digitalWrite(bLEDpin, LOW);
      digitalWrite(gLEDpin, LOW);
      color = "cyan";
  }

   else if (ledcolor == 7){
    //WHITE
      digitalWrite(rLEDpin, LOW);
      digitalWrite(bLEDpin, LOW);
      digitalWrite(gLEDpin, LOW);
      color = "white";
  }

   else if (ledcolor == 8){
    ledcolor =0;
}

}
