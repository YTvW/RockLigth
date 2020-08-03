#include <ezButton.h>
#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
#include <avr/power.h>
#endif

#define LEDPIN 10
#define BUTTON_PIN 9
Adafruit_NeoPixel strip = Adafruit_NeoPixel(6, LEDPIN, NEO_GRB);

int mode = 1;
unsigned long CurrentTime = millis();
unsigned long stepTime = 100;
unsigned long stepTimer = 0;
uint16_t i, j;

ezButton button(BUTTON_PIN);
unsigned long pressedTime = 0;
unsigned long releasedTime = 0;

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code
  pinMode(BUTTON_PIN, INPUT);
  button.setDebounceTime(50);
  strip.begin();
  strip.setBrightness(100);
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
  unsigned long timeout = millis();
  while (!Serial) {
    if (millis() - timeout > 2500) {
      break;
    }
  }
  Serial.println("Connected");
}

void loop() {
 
  button.loop(); // MUST call the loop() function first, this update the buttonstate in the library

  if(button.isPressed()){
    Serial.println("The button is pressed");
    pressedTime = millis();
  }
  if(button.isReleased()){
    Serial.println("The button is released");
    releasedTime = millis();
  
    if ((releasedTime-pressedTime) >= 500){
      Serial.println("Long press");
      Serial.println(( releasedTime-pressedTime));
      pressedTime = 0;
      releasedTime = 0;
      mode = 0;
      stepTimer = 0;
      j = 0;
      Serial.print("updated to ");
      Serial.println(mode);
      }
     else if ((releasedTime-pressedTime) < 500){
      Serial.println("Short press");
      Serial.println(( releasedTime-pressedTime));
      pressedTime = 0;
      releasedTime = 0;
      mode += 1;
      stepTimer = 0;
      j = 0;
      Serial.print("updated to ");
      Serial.println(mode);
      } 
  }


  switch (mode) {
    case 0:
     // Off, all leds are off
      CurrentTime = millis();
      if ((stepTimer - CurrentTime) > 100)
      {
        stepTimer = millis();
        for (i = 0; i < strip.numPixels(); i++) {
          strip.setPixelColor(i, 0, 0, 0);
        }
        strip.show();
      }
      break;
    case 1:
      // colour cycle
      CurrentTime = millis();
      if ((CurrentTime - stepTimer) > 5000)
      {

        stepTimer = millis();
        for (i = 0; i < strip.numPixels(); i++) {
          strip.setPixelColor(i, Wheel(( j) & 255));
        }
        strip.show();
        if (j < 256) {
          j++;
        }
        else {
          j = 0;
        }

        //        Serial.println(stepTimer);
      }
      break;
    case 2:
      // red and yellow
      CurrentTime = millis();
      if ((stepTimer - CurrentTime) > 100)
      {
        stepTimer = millis();
        for (i = 0; i < strip.numPixels()/2; i++) {
          strip.setPixelColor(i, strip.Color(255, 0, 0));
        }
        for (i = 3; i < strip.numPixels(); i++) {
          strip.setPixelColor(i, strip.Color(255, 255, 0));
        }
        strip.show();
      }
      break;
    case 3:
      // yellow and green
      CurrentTime = millis();
      if ((stepTimer - CurrentTime) > 100)
      {
        stepTimer = millis();
        for (i = 0; i < strip.numPixels()/2; i++) {
          strip.setPixelColor(i, strip.Color(0, 255, 0));
        }
        for (i = 3; i < strip.numPixels(); i++) {
          strip.setPixelColor(i, strip.Color(255, 255, 0));
        }
        strip.show();
      }
      break;
    case 4:
      // green and purple
      CurrentTime = millis();
      if ((stepTimer - CurrentTime) > 100)
      {
        stepTimer = millis();
        for (i = 0; i < strip.numPixels()/2; i++) {
          strip.setPixelColor(i, strip.Color(0, 255, 0));
        }
        for (i = 3; i < strip.numPixels(); i++) {
          strip.setPixelColor(i, strip.Color(255, 0, 255));
        }
        strip.show();
      }
      break;
    case 5:
      // cyan
      CurrentTime = millis();
      if ((stepTimer - CurrentTime) > 100)
      {
        stepTimer = millis();
        for (i = 0; i < strip.numPixels(); i++) {
          strip.setPixelColor(i, 0, 255, 255);
        }
        strip.show();
      }
      break;
    case 6:
       // blue
      CurrentTime = millis();
      if ((stepTimer - CurrentTime) > 100)
      {
        stepTimer = millis();
        for (i = 0; i < strip.numPixels(); i++) {
          strip.setPixelColor(i, 0, 0, 255);
        }
        strip.show();
      }
      break;
    case 7:
      // magenta
      CurrentTime = millis();
      if ((stepTimer - CurrentTime) > 100)
      {
        stepTimer = millis();
        for (i = 0; i < strip.numPixels(); i++) {
          strip.setPixelColor(i, 255, 0, 255);
        }
        strip.show();
      }
      break;

    case 8:
      // white
      CurrentTime = millis();
      if ((stepTimer - CurrentTime) > 100)
      {
        stepTimer = millis();
        for (i = 0; i < strip.numPixels()/2; i++) {
          strip.setPixelColor(i, strip.Color(0, 0, 255));
        }
        for (i = 3; i < strip.numPixels(); i++) {
          strip.setPixelColor(i, strip.Color(200, 215, 215));
        }
        strip.show();
      }
      break;
    case 9:
      // blue and green
      CurrentTime = millis();
      if ((stepTimer - CurrentTime) > 100)
      {
        stepTimer = millis();
        for (i = 0; i < 3; i++) {
          strip.setPixelColor(i, 0, 255, 0);
        }
        for (i = 3; i < strip.numPixels(); i++) {
          strip.setPixelColor(i, 0, 0, 255);
        }
        strip.show();
      }
      break;
    case 10:
      // magenta blue
      CurrentTime = millis();
      if ((stepTimer - CurrentTime) > 100)
      {
        stepTimer = millis();
        for (i = 0; i < 3; i++) {
          strip.setPixelColor(i, 200, 0, 200);
        }
        for (i = 3; i < strip.numPixels(); i++) {
          strip.setPixelColor(i, 0, 0, 255);
        }
        strip.show();
      }
      break;
    case 11:
      // blue red
      CurrentTime = millis();
      if ((stepTimer - CurrentTime) > 100)
      {
        stepTimer = millis();
        for (i = 0; i < 3; i++) {
          strip.setPixelColor(i, 255, 0,0);
        }
        for (i = 3; i < strip.numPixels(); i++) {
          strip.setPixelColor(i, 0, 0, 255);
        }
        strip.show();
      }
      break;
    case 12:
      // reset mode to 0
      mode = 0;
      Serial.println("reset mode");
      break;
  };

}

void rainbow(uint16_t wait) {
  Serial.println(stepTimer);
  if ((stepTimer - millis()) >= 1000)
  {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    if (j < 256) {
      j++;
    }
    else {
      j = 0;
    }
    stepTimer = millis();
    //        Serial.println(stepTimer);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, c);  //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, Wheel( (i + j) % 255)); //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
