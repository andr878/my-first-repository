const int rLEDpin = 3;
const int bLEDpin = 4;
const int gLEDpin = 5;
const int pushButton = 2;

const unsigned long debounceDelay    = 50;   
const unsigned long holdThreshold    = 600;  
const unsigned long colorInterval    = 300; 

int ledColor = 0;                  
int lastButtonReading = HIGH;      
int stableButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long pressStartTime = 0;
unsigned long lastColorChange = 0;
bool autoCycle = false;

void setup() {
  Serial.begin(9600);
  pinMode(rLEDpin, OUTPUT);
  pinMode(bLEDpin, OUTPUT);
  pinMode(gLEDpin, OUTPUT);

  pinMode(pushButton, INPUT_PULLUP);

  setColor(0);
}

void loop() {
  int reading = digitalRead(pushButton); 

  if (reading != lastButtonReading) {
    lastDebounceTime = millis();
  }

  if (millis() - lastDebounceTime > debounceDelay) {
    if (reading != stableButtonState) {
      stableButtonState = reading;

      if (stableButtonState == LOW) {
        pressStartTime = millis();
        autoCycle = false;            
        lastColorChange = millis();
      } else {
        unsigned long pressedFor = millis() - pressStartTime;
        if (!autoCycle && pressedFor < holdThreshold) {
          nextColor();
        }
        autoCycle = false;
      }
    }
  }

  lastButtonReading = reading;

  if (stableButtonState == LOW) { 
    unsigned long heldFor = millis() - pressStartTime;
    if (heldFor >= holdThreshold) {
      autoCycle = true;
      if (millis() - lastColorChange >= colorInterval) {
        nextColor();
        lastColorChange = millis();
      }
    }
  }

  setColor(ledColor);

  static unsigned long lastSerial = 0;
  if (millis() - lastSerial > 300) {
    Serial.print("Color: ");
    Serial.println(getColorName(ledColor));
    lastSerial = millis();
  }
}

void nextColor() {
  ledColor++;
  if (ledColor > 7) ledColor = 0;
}


void setColor(int color) {
  switch (color) {
    case 0: // OFF
      digitalWrite(rLEDpin, HIGH);
      digitalWrite(bLEDpin, HIGH);
      digitalWrite(gLEDpin, HIGH);
      break;
    case 1: // RED
      digitalWrite(rLEDpin, LOW);
      digitalWrite(bLEDpin, HIGH);
      digitalWrite(gLEDpin, HIGH);
      break;
    case 2: // GREEN
      digitalWrite(rLEDpin, HIGH);
      digitalWrite(bLEDpin, HIGH);
      digitalWrite(gLEDpin, LOW);
      break;
    case 3: // BLUE
      digitalWrite(rLEDpin, HIGH);
      digitalWrite(bLEDpin, LOW);
      digitalWrite(gLEDpin, HIGH);
      break;
    case 4: // YELLOW (R + G)
      digitalWrite(rLEDpin, LOW);
      digitalWrite(bLEDpin, HIGH);
      digitalWrite(gLEDpin, LOW);
      break;
    case 5: // PURPLE (R + B)
      digitalWrite(rLEDpin, LOW);
      digitalWrite(bLEDpin, LOW);
      digitalWrite(gLEDpin, HIGH);
      break;
    case 6: // CYAN (G + B)
      digitalWrite(rLEDpin, HIGH);
      digitalWrite(bLEDpin, LOW);
      digitalWrite(gLEDpin, LOW);
      break;
    case 7: // WHITE (R + G + B)
      digitalWrite(rLEDpin, LOW);
      digitalWrite(bLEDpin, LOW);
      digitalWrite(gLEDpin, LOW);
      break;
    default:
      // safety: turn off
      digitalWrite(rLEDpin, HIGH);
      digitalWrite(bLEDpin, HIGH);
      digitalWrite(gLEDpin, HIGH);
      break;
  }
}

String getColorName(int color) {
  switch (color) {
    case 0: return "OFF";
    case 1: return "RED";
    case 2: return "GREEN";
    case 3: return "BLUE";
    case 4: return "YELLOW";
    case 5: return "PURPLE";
    case 6: return "CYAN";
    case 7: return "WHITE";
    default: return "UNKNOWN";
  }
}
