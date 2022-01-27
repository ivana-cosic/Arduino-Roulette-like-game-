#include <FastLED.h>
#include <OneButton.h>
#include "SevSeg.h"

#define NUM_LEDS 60
#define LED_PIN 2
#define BTN_PIN 3
#define cilj_ind 30 // index of a red LED

CRGB leds[NUM_LEDS];
SevSeg sevseg; 
OneButton btn = OneButton(BTN_PIN, true, true);
int ind;
int level;

unsigned long startMillis;
unsigned long currentMillis;
unsigned long period;           // the value is a number of milliseconds
  
void setup() {
  
  Serial.begin(9600);
  
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(40);    // number from 0 to 255
  
  leds[cilj_ind] = CRGB::Red;
  ind = 0;
  level = 1;
  period = 1000/(level+1); // on level 1 LEDs are switching at 500ms

  byte numDigits = 1;
  byte digitPins[] = {};
  byte segmentPins[] = {6, 5, 4, 7, 8, 9, 10, 11};
  bool resistorsOnSegments = true;

  byte hardwareConfig = COMMON_ANODE; 
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);
  
  startMillis = millis();

  btn.attachClick(check);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  leds[ind] = CRGB::Yellow;

  currentMillis = millis();

  if (currentMillis - startMillis >= period)  // test whether the period has elapsed
  {
    if (ind != cilj_ind) {leds[ind] = CRGB::Black;} else {leds[ind] = CRGB::Red;};
    if (ind != NUM_LEDS -1) { ind++;} else {ind = 0;};
    startMillis = currentMillis;  //IMPORTANT to save the start time of the current LED state.
  }

  FastLED.show();
  btn.tick();
}

void check() { // checking starts on button click
  CRGB color;
  if (ind == cilj_ind) {           // if correct, LEDs will blink yellow, and the player moves on to the next level
    color = CRGB::Yellow;
    level++;
    ind = random(NUM_LEDS/2)+NUM_LEDS/2+1;
    } 
  else {                           // if not correct, LEDs will blink red, and the player returns to level 1
    color = CRGB::Red;
    level = 1;
    ind = random(NUM_LEDS/2)+NUM_LEDS/2+1;
    };
  for (int i= 0; i <= 2; i++) {
    fill_solid(leds, NUM_LEDS, color);
    FastLED.show();
    delay(400);
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
    delay(400);
  }
  leds[cilj_ind] = CRGB::Red;
  if (level >= 10) { level = 1;};
  sevseg.setNumber(level);
  sevseg.refreshDisplay(); 
  period = 1000/(level+1);          // higher level, faster switching
}
