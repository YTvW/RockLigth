#include <ezButton.h>
#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
#include <avr/power.h>
#endif

#define LEDPIN 10
#define BUTTON_PIN 9
#define PI 3.1415926535897932384626433832795
Adafruit_NeoPixel strip = Adafruit_NeoPixel(6, LEDPIN, NEO_GRB);

int mode = 1;
unsigned long CurrentTime = millis();
unsigned long stepTime = 100;
unsigned long stepTimer = 0;
unsigned long stepTimer2 = 0;
unsigned long stepTimer3 = 0;
uint16_t i, j, k, m, n;
uint16_t wheelTime, wheelTime2;
uint16_t wheelAmp, wheelAmp2;
uint16_t modeCount;
uint32_t red, gre, blu, red2, gre2, blu2;
uint32_t red3, gre3, blu3, red4, gre4, blu4;
uint32_t color, color2;
float var, var2, var3, var4;
double percent, percent2;

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
      k = 0;
      m = 0;
      n = 0;
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
      k = 0;
      m = 0;
      n = 0;
      Serial.print("updated to ");
      Serial.println(mode);
      } 
  }


  switch (mode) {
    case 0:
     // Off, all leds are off

     modeCount = 0;
     
      CurrentTime = millis();
      if ((CurrentTime - stepTimer) > 100)
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
      
      if (modeCount == 0)
      {
        j = random(0, 256);
        modeCount++;
      }
      
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
      // color cycle offset

      if (modeCount == 1)
      {
        j = random(0, 256);
        k = random(0, 256);
        modeCount++;
      }
      
      CurrentTime = millis();
      if ((CurrentTime - stepTimer) > 5000)
      {
        stepTimer = millis();
        for (i = 0; i < strip.numPixels()/2; i++) {
          strip.setPixelColor(i, Wheel(( j) & 255));
        }
        strip.show();
        if (j < 256) {
          j++;
        }
        else {
          j = 0;
        }
      }

      if ((CurrentTime - stepTimer2) > 4000)
      {
        stepTimer2 = millis();
        for (i = 3; i < strip.numPixels(); i++) {
          strip.setPixelColor(i, Wheel(( k) & 255));
        }
        strip.show();
        if (k < 256) {
          k++;
        }
        else {
          k = 0;
        }
      }
      break;
    case 3:
      // Pulsing yellow and green

      if (modeCount == 2)
      {
        wheelTime = random(10, 120); // defines the time for one pulse
        wheelAmp = random(50, 100); // defines the amplitude of the pulse, should always be even!
          if ( (wheelAmp % 2) != 0) {
          wheelAmp++;  
          }
        wheelTime2 = random(10, 120); // defines the time for one pulse
        wheelAmp2 = random(50, 100); // defines the amplitude of the pulse, should always be even!
          if ( (wheelAmp2 % 2) != 0) {
          wheelAmp2++;  
          }
        modeCount++;
      }
           
      CurrentTime = millis();
      if ((CurrentTime - stepTimer) > 100)
      {
        stepTimer = millis();
        
        if (var < wheelTime) { // defines the first loop
          var++;
        }
        else {
          var = 0;
          wheelTime = random(10, 120);
          wheelAmp = random(50, 100);
            if ( (wheelAmp % 2) != 0) {
            wheelAmp++;  
            }
        }
        var2 = var / (wheelTime/2);
        double cosine;
        cosine = cos(var2*PI);
        cosine++; // by adding '1' the cosine will cycle between 2 and 0 (instead of 1 and -1)
        m = ((cosine*wheelAmp)+55+((100-wheelAmp)*2)); // m will shift between 255 and minimally 55 and back up again following the cosine

        if (var3 < wheelTime2) { // defines the second loop
          var3++;
        }
        else {
          var3 = 0;
          wheelTime2 = random(10, 120);
          wheelAmp2 = random(50, 100);
            if ( (wheelAmp2 % 2) != 0) {
            wheelAmp2++;  
            }
        }
        var4 = var3 / (wheelTime2/2);
        double cosine2;
        cosine2 = cos(var4*PI);
        cosine2++; // by adding '1' the cosine will cycle between 2 and 0 (instead of 1 and -1)
        n = ((cosine2*wheelAmp2)+55+((100-wheelAmp2)*2)); // n will shift between 255 and minimally 55 and back up again following the cosine
        
        for (i = 0; i < strip.numPixels()/2; i++) {
          color = strip.Color(0, m, 0);
          strip.setPixelColor(i, color);
        }
        for (i = 3; i < strip.numPixels(); i++) {
          color2 = strip.Color(n, n, 0);
          strip.setPixelColor(i, color2);
        }
        strip.show();
      }
      break;
    case 4:
      // Pulsing color cycle offset
      
      if (modeCount == 3) // runs set-up code for this mode
      {
        j = random(0, 256); // randomizes starting position color cycle
        k = random(0, 256); // randomizes starting position color cycle 2
        wheelTime = random(10, 120); // defines the initial time for one pulse
        wheelAmp = random(50, 100); // defines the initial amplitude of the pulse, should always be even!
          if ( (wheelAmp % 2) != 0) {
          wheelAmp++;  
          }
        wheelTime2 = random(10, 120); // defines the initial time for one pulse
        wheelAmp2 = random(50, 100); // defines the initial amplitude of the pulse, should always be even!
          if ( (wheelAmp2 % 2) != 0) {
          wheelAmp2++;  
          }
        modeCount++;
      }

      CurrentTime = millis();
      if ((CurrentTime - stepTimer) > 5000)
      {
        stepTimer = millis();

        color = Wheel(( j) & 255);
        red = color/65536; // The following functions work as a decimal to RGB decoder
        gre = (color-(red*65536))/256;
        blu = color-(red*65536)-(gre*256);
       
        if (j < 256) {
          j++;
        }
        else {
          j = 0;
        }
      }

      if ((CurrentTime - stepTimer2) > 4000)
      {
        stepTimer2 = millis();

        color2 = Wheel(( k) & 255);
        red3 = color2/65536; // The following functions work as a decimal to RGB decoder
        gre3 = (color2-(red3*65536))/256;
        blu3 = color2-(red3*65536)-(gre3*256);
        
        if (k < 256) {
          k++;
        }
        else {
          k = 0;
        }
      }
     
      if ((CurrentTime - stepTimer3) > 100)
      {
        stepTimer3 = millis();
        
        if (var < wheelTime) {
          var++;
        }
        else {
          var = 0;
          wheelTime = random(10, 120);
          wheelAmp = random(50, 100);
            if ( (wheelAmp % 2) != 0) {
            wheelAmp++;  
            }
        }
        var2 = var / (wheelTime/2);
        double cosine;
        cosine = cos(var2*PI);
        cosine++; // by adding '1' the cosine will cycle between 2 and 0 (instead of 1 and -1)
        m = ((cosine*wheelAmp)+55+((100-wheelAmp)*2)); // m will shift between 255 and minimally 55 and back up again following the cosine

        percent = m / 255.00;
        red2 = red*percent;
        gre2 = gre*percent;
        blu2 = blu*percent;

        for (i = 0; i < strip.numPixels()/2; i++) {
          strip.setPixelColor(i, red2, gre2, blu2);
        }

        if (var3 < wheelTime2) { // defines the second loop
          var3++;
        }
        else {
          var3 = 0;
          wheelTime2 = random(10, 120);
          wheelAmp2 = random(50, 100);
            if ( (wheelAmp2 % 2) != 0) {
            wheelAmp2++;  
            }
        }
        var4 = var3 / (wheelTime2/2);
        double cosine2;
        cosine2 = cos(var4*PI);
        cosine2++; // by adding '1' the cosine will cycle between 2 and 0 (instead of 1 and -1)
        n = ((cosine2*wheelAmp2)+55+((100-wheelAmp2)*2)); // n will shift between 255 and minimally 55 and back up again following the cosine

        percent2 = n / 255.00;
        red4 = red3*percent2;
        gre4 = gre3*percent2;
        blu4 = blu3*percent2;
        
        for (i = 3; i < strip.numPixels(); i++) {
          strip.setPixelColor(i, red4, gre4, blu4);
        }
        
        strip.show();
      }
      break;
/*    case 5:
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
      break; */
    case 5:
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
