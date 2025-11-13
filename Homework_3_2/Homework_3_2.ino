const int buttonPin = 4;   // Pushbutton pin
const int ledPin = 3;      // LED pin

// Button and LED states
int buttonState;           
int lastButtonState = LOW; 
int mode = 0;              // 0 = steady, 1 = slow, 2 = medium, 3 = fast, 4 = steady again, 5 = off
int ledState = HIGH;       

// Timing variables
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;  // debounce delay (ms)
unsigned long previousMillis = 0;  // for blink timing

// Blink speeds (in milliseconds)
const long slowInterval = 1000;   // 1 second
const long mediumInterval = 500;  // 0.5 seconds
const long fastInterval = 200;    // 0.2 seconds

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(ledPin, HIGH); // Start in steady ON mode
}

void loop() {
  int reading = digitalRead(buttonPin);

  // Debounce the button
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading == HIGH && buttonState == LOW) {
      // Button pressed — advance to next mode
      mode = (mode + 1) % 6;  // cycle through 0–5
      ledState = HIGH;        // reset LED state when switching modes
      digitalWrite(ledPin, ledState);
    }
    buttonState = reading;
  }

  lastButtonState = reading;

  // Handle lighting modes
  switch (mode) {
    case 0: // Steady ON (initial)
      digitalWrite(ledPin, HIGH);
      break;

    case 1: // Slow Blink
      blinkLED(slowInterval);
      break;

    case 2: // Medium Blink
      blinkLED(mediumInterval);
      break;

    case 3: // Fast Blink
      blinkLED(fastInterval);
      break;

    case 4: // Steady ON (again)
      digitalWrite(ledPin, HIGH);
      break;

    case 5: // OFF
      digitalWrite(ledPin, LOW);
      break;
  }
}

// Helper function for blinking behavior
void blinkLED(long interval) {
  if (millis() - previousMillis >= interval) {
    previousMillis = millis();
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
  }
}
