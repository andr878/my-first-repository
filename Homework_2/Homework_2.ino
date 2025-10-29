const bool COMMON_ANODE = true;

const int RLedPin = 9;
const int GLedPin = 10;
const int BLedPin = 11;
const int buttonPin = 2;

int mood = 10;               // start at neutral (green)
const int neutralMood = 10;
bool ButtonPressed = false;
int buttonState = 0;

unsigned long touchedTimer = 0;
unsigned long reducedTimer = 0;
const long untouchInterval = 5000;   // 5 seconds before mood starts to drop
const long reducedInterval = 1000;   // drops 1 point per second

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(RLedPin, OUTPUT);
  pinMode(GLedPin, OUTPUT);
  pinMode(BLedPin, OUTPUT);

  mood = neutralMood;
  touchedTimer = millis();
  reducedTimer = millis();
  showLEDstate(mood);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  // Detect button press (rising edge)
  if (buttonState == HIGH && !ButtonPressed) {
    ButtonPressed = true;
    if (mood < 20) mood++;
    touchedTimer = millis();
    showLEDstate(mood);
    delay(200); // simple debounce
  }

  // Reset flag when released
  if (buttonState == LOW && ButtonPressed) {
    ButtonPressed = false;
  }

  // After untouchInterval, decrease mood every reducedInterval
  unsigned long currentMillis = millis();
  if (currentMillis - touchedTimer > untouchInterval) {
    if (currentMillis - reducedTimer > reducedInterval) {
      if (mood > 0) {
        mood--;
        showLEDstate(mood);
      }
      reducedTimer = currentMillis;
    }
  }
}

// Map mood (0..20) to RGB values (0..255) where:
// 0 -> Red (255,0,0), 10 -> Green (0,255,0), 20 -> Blue (0,0,255)
// Then invert PWM if COMMON_ANODE
void showLEDstate(int state) {
  const int SEG = 10;                    // points per segment
  const float STEP = 255.0 / SEG;       // PWM step per point (25.5)

  int r = 0, g = 0, b = 0;

  if (state <= neutralMood) {
    // red (0) -> green (10)
    // red goes from 255 -> 0, green 0 -> 255
    r = round(255 - STEP * state);
    g = round(STEP * state);
    b = 0;
  } else {
    // green (10) -> blue (20)
    int s = state - neutralMood; // 1..10
    r = 0;
    g = round(255 - STEP * s);
    b = round(STEP * s);
  }

  // If using common-anode, invert values for PWM
  if (COMMON_ANODE) {
    r = 255 - r;
    g = 255 - g;
    b = 255 - b;
  }

  analogWrite(RLedPin, r);
  analogWrite(GLedPin, g);
  analogWrite(BLedPin, b);
}

