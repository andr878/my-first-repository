const int rLEDpin = 3;
const int bLEDpin = 4;
const int gLEDpin = 5;
const int pushButton = 2;
int buttonState = 0;
int ledstate = 0;
int ledcolor = 0;
String color= "led"; //currentcolor
bool buttonPressed = false;
unsigned long previousMillis = 0;
const long interval = 1000;


void setup(){
  Serial.begin(9600);
  pinMode(rLEDpin, OUTPUT);
  pinMode (bLEDpin, OUTPUT);
  pinMode (gLEDpin, OUTPUT);
  pinMode(pushButton,INPUT);
}

void loop(){
  buttonState = digitalRead(pushButton);
  Serial.print("Current Color: ");
  Serial.println(color);
  if (buttonState == HIGH && !buttonPressed) {
    ledcolor++;
    buttonPressed = true;
    //delay(100);
  }
  if (buttonState == LOW && buttonPressed) {
    buttonPressed = false;
  }
  unsigned long currentMillis = millis();
  if(currentMillis -previousMillis >= interval){
    previousMillis = currentMillis;
  }
  if(ledstate == LOW){
    ledstate = HIGH;
  } else{
    ledstate =LOW;
  }

  if (ledcolor == 0) {
    color = "led OFF";
      digitalWrite(rLEDpin, HIGH);
      digitalWrite(bLEDpin, HIGH);
      digitalWrite(gLEDpin, HIGH);
      
    }

  else if (ledcolor == 1){
    //red
    color = "red";
    if (ledstate ==LOW){
      digitalWrite(rLEDpin, LOW);
      digitalWrite(bLEDpin, HIGH);
      digitalWrite(gLEDpin, HIGH);
  } else{
    digitalWrite(rLEDpin, HIGH);
    digitalWrite(bLEDpin, HIGH);
    digitalWrite(gLEDpin, HIGH);
  }
}

 else if (ledcolor == 2){
    //green
    color = "green";

    if(ledstate ==LOW){
      digitalWrite(rLEDpin, HIGH);
      digitalWrite(bLEDpin, HIGH);
      digitalWrite(gLEDpin, LOW);
  } else{
    digitalWrite(rLEDpin, HIGH);
    digitalWrite(bLEDpin, HIGH);
    digitalWrite(gLEDpin, HIGH);
  }
  }

   else if (ledcolor == 3){
    //BLUE
    color = "blue";
    if(ledstate ==LOW){
      digitalWrite(rLEDpin, HIGH);
      digitalWrite(bLEDpin, LOW);
      digitalWrite(gLEDpin, HIGH);
  }else{
    digitalWrite(rLEDpin, HIGH);
    digitalWrite(bLEDpin, HIGH);
    digitalWrite(gLEDpin, HIGH);
    }
  }

   else if (ledcolor == 4){
    //Yellow
    color = "yellow";
    if (ledstate ==LOW){
      digitalWrite(rLEDpin, LOW);
      digitalWrite(bLEDpin, HIGH);
      digitalWrite(gLEDpin, LOW);
  }else{
    digitalWrite(rLEDpin, HIGH);
    digitalWrite(bLEDpin, HIGH);
    digitalWrite(gLEDpin, HIGH);
  }
  }

   else if (ledcolor == 5){
    //PURPLE
    color = "purple";
    if(ledstate ==LOW){
      digitalWrite(rLEDpin, LOW);
      digitalWrite(bLEDpin, LOW);
      digitalWrite(gLEDpin, HIGH);  
  }else{
    digitalWrite(rLEDpin, HIGH);
    digitalWrite(bLEDpin, HIGH);
    digitalWrite(gLEDpin, HIGH);
  }
}

   else if (ledcolor == 6){
    //CYAN
    color = "cyan";
    if(ledstate==LOW){
      digitalWrite(rLEDpin, HIGH);
      digitalWrite(bLEDpin, LOW);
      digitalWrite(gLEDpin, LOW);
  } else{
    digitalWrite(rLEDpin, HIGH);
    digitalWrite(bLEDpin, HIGH);
    digitalWrite(gLEDpin, HIGH);
  }
  }

   else if (ledcolor == 7){
    //WHITE
    color = "white";
    if(ledstate ==LOW){
      digitalWrite(rLEDpin, LOW);
      digitalWrite(bLEDpin, LOW);
      digitalWrite(gLEDpin, LOW);
  }else{
    digitalWrite(rLEDpin, HIGH);
    digitalWrite(bLEDpin, HIGH);
    digitalWrite(gLEDpin, HIGH);
  }
  }
   else if (ledcolor == 8){
    ledcolor =0;
}
}