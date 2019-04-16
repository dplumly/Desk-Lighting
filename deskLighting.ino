#include <FastLED.h>

// NEOPIXEL DEFINITIONS -----------------------------------------------------------------------------
#define NUM_LEDS 21
CRGB strip1[NUM_LEDS];
CRGB strip2[NUM_LEDS];

// Strip One
#define DATA_PIN 5      // Green
#define CLOCK_PIN 6     // Blue    Comment out for Neopixels

// Strip Two
#define DATA_PIN2 8      // Green
#define CLOCK_PIN2 9     // Blue    Comment out for Neopixels



// BUTTON DEFINITIONS -----------------------------------------------------------------------------
const int buttonPin = 2;
bool oldState = HIGH;
int showType = 1;

void setup() {
  Serial.begin(9600);             //initialize Serial connection

  // BUTTON SETUP --------------
  pinMode(buttonPin, INPUT_PULLUP);      //this time we will set the pin as INPUT

  // LEDS SETUP --------------
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN>(strip1, NUM_LEDS);     // Comment out for Neopixels
  FastLED.addLeds<APA102, DATA_PIN2, CLOCK_PIN2>(strip2, NUM_LEDS);     // Comment out for Neopixels

  FastLED.show();
}

void loop() {
  // Get current button state.
  bool newState = digitalRead(buttonPin);
  // Check if state changed from high to low (button press).
  if (newState == LOW && oldState == HIGH) {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.

    newState = digitalRead(buttonPin);
    if (newState == LOW) {
      showType++;
      if (showType > 3)
        showType = 1;
      startShow(showType);
    }

  }
  startShow(showType);
  // Set the last button state to the old state.
  oldState = newState;
}

void startShow(int i) {
  switch (i) {
    case 1:
      Serial.println("off");
      stripsOff();
      break;

    case 2:
      Serial.println("2");
      strip1on();
      break;

    case 3:
      Serial.println("3");
      strip2on();
      break;
  }
}



// FUNCTION LIGHTS 1 ON  -----------------------------------------------------------------------------

void strip1on() {
  for (int dot = 0; dot < NUM_LEDS; dot++) {
    strip1[dot] = CRGB::White;
    FastLED.show();
  }
}

// FUNCTION LIGHTS 2 ON  -----------------------------------------------------------------------------
void strip2on() {
  for (int dot = 0; dot < NUM_LEDS; dot++) {
    strip2[dot] = CRGB::White;
    FastLED.show();
  }
}

// FUNCTION LIGHTS OFF  -----------------------------------------------------------------------------
void stripsOff() {
  for (int dot = 0; dot < NUM_LEDS; dot++) {
    strip1[dot] = CRGB::Black;
    FastLED.show();
  }
  for (int dot = 0; dot < NUM_LEDS; dot++) {
    strip2[dot] = CRGB::Black;
    FastLED.show();
  }

}

