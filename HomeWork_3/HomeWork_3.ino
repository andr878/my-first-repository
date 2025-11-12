const int buttonPin = 2;

const int RLedPin = 9;
const int GLedPin = 11;
const int BLedPin = 10;

int ButtonState = 0;

bool buttonPressed = false;

unsigned long PressingTime = 0;

const int longPressInterval = 2000;

int lightNum = 0;

int RLightColor = 0;
int GLightColor = 0;
int BLightColor = 0;

int RCurrentColor = 0;
int BCurrentColor = 0;
int GCurrentColor = 0;

int currentMode = 0;

unsigned long blinkTimer = 0;

const int blinkInterval = 500;

bool blinkOn = true;

const int fadeAmount = 2;
int fadeDirection = 1;

void setup(){
  pinMode(buttonPin, INPUT);
  pinMode(RLedPin, OUTPUT);
  pinMode(BLedPin, OUTPUT);
  pinMode(GLedPin, OUTPUT);
  Serial.begin(9600);

}

void loop(){
  checkButton();
  updateLEDColor();
  setRGBLEDColor(RCurrentColor, GCurrentColor, BCurrentColor);

}
void checkButton(){
ButtonState = digitalRead(buttonPin);

  if(ButtonState == LOW && !buttonPressed){
    PressingTime = millis();
    buttonPressed = true;
  }

  if(ButtonState == HIGH && buttonPressed){
    unsigned long currentTime = millis();
    if(currentTime - PressingTime < longPressInterval){
      //short click
      Serial.println("short click");
      changeLEDColor();
    }
    else{
      //long press
      Serial.println("long press");
      changeMode();
    }
    buttonPressed = false;
  }
}

void setRGBLEDColor(int r, int g, int b){
  analogWrite(RLedPin, r);
  analogWrite(GLedPin, g);
  analogWrite(BLedPin, b);
}

void changeLEDColor(){
  lightNum = lightNum +1;
  if(lightNum >= 5)
  lightNum=0;

  if(lightNum == 0){ //white
    RLightColor = 0;
    GLightColor = 0;
    BLightColor = 0;
  }

  if(lightNum == 1){ //red
    RLightColor = 0;
    GLightColor = 255;
    BLightColor = 255;
  }

  if(lightNum == 2){ //grenn
    RLightColor = 255;
    GLightColor = 0;
    BLightColor = 255;
  }

  if(lightNum == 3){ //blue
    RLightColor = 255;
    GLightColor = 255;
    BLightColor = 0;
  }

  if(lightNum == 4){ //yellow
    RLightColor = 0;
    GLightColor = 0;
    BLightColor = 255;
  }
  RCurrentColor = RLightColor;
  GCurrentColor = GLightColor;
  BCurrentColor = BLightColor;
}

void changeMode(){
  currentMode = currentMode + 1;
  if(currentMode >= 3){
    currentMode = 0;
  }

  if(currentMode == 1){
    blinkTimer = 0;
    blinkOn = true;
  }
  if(currentMode== 2){
    fadeDirection = 1;
  }
}

void updateLEDColor (){
  if(currentMode == 0){
    RCurrentColor = RLightColor;
    GCurrentColor = GLightColor;
    BCurrentColor = BLightColor;
  }

  else if(currentMode == 1){
    unsigned long currentTime = millis();
    if(currentTime - blinkTimer > blinkInterval){
      blinkOn = !blinkOn;
      blinkTimer = currentTime;
    }

    if(blinkOn){
      RCurrentColor = RLightColor;
      GCurrentColor = GLightColor;
      BCurrentColor = BLightColor;
    }

    else{
      RCurrentColor = 255;
      BCurrentColor = 255;
      GCurrentColor = 255;

    }
  }
  else if(currentMode == 2){
    Serial.println("breathing light mode");
    bool negativeDir = false;
    if(RLightColor == 0){
      RCurrentColor = RCurrentColor + fadeDirection * fadeAmount;
      if(RCurrentColor > (255 -RLightColor) || (RCurrentColor < 0)){
        negativeDir = true;
      }
      
      if(RCurrentColor < 0) RCurrentColor = 0;
      if(RCurrentColor > 255) RCurrentColor = 255;
    }

    if(GLightColor == 0){
      GCurrentColor = GCurrentColor + fadeDirection * fadeAmount;
      if(GCurrentColor > (255 -GLightColor) || (GCurrentColor < 0)){
        negativeDir = true;
      }
      
      if(GCurrentColor < 0) GCurrentColor = 0;
      if(GCurrentColor > 255) GCurrentColor = 255;
    }

    if(BLightColor == 0){
      BCurrentColor = BCurrentColor + fadeDirection * fadeAmount;
      if(BCurrentColor > (255 - BLightColor) || (BCurrentColor < 0)){
        negativeDir = true;
      }
      
      if(BCurrentColor < 0) BCurrentColor = 0;
      if(BCurrentColor > 255) BCurrentColor = 255;
    }

    if(negativeDir)
      fadeDirection = - fadeDirection;

    delay(10);
  }

}
