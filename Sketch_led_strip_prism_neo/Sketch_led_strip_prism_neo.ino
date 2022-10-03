#include <Adafruit_NeoPixel.h>
//#include <FastLED_NeoPixel.h>

// How many internal neopixels do we have? some boards have more than one!
#define NUMPIXELS 101
#define PIN_NEOPIXEL 14 //pin for DIN to daisy chain into led

Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

// the setup routine runs once when you press reset:
void setup() {
  //Serial.begin(115200); //Only for debug

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.setBrightness(30); // not so bright
  pixels.show();
}

void loop() {
  
  colorWipe3(2,254,207, 300); //led are lit from top hex center to bottom hex center
  delay(1000);
  colorWipe2(0x00,0x00,0x00, 300); //led are shutted off from bottom hex center to top hex center
  
}

//////////////////////////////////

//colorWipe--> LED are lit in cirular fashion starting from 0 to NUMPIXELS
void colorWipe(uint32_t red, uint32_t green, uint32_t blue, int SpeedDelay) {
  for(uint16_t i=0; i<NUMPIXELS; i++) {
      pixels.setPixelColor(i, red, green, blue);
      pixels.show();
      delay(SpeedDelay);
  }
}

//colorWipe2--> LED are lit in cirular fashion starting from center of top side (8th led) of the hexagonal shape of PRISM to the center of bottom EDGE(60th led).
//    101 0__
//       /    \
//       \ 60 /
//
//Function can be improved using vectors instead of using if and checking all the possible status of indexes
 
void colorWipe2(uint32_t red, uint32_t green, uint32_t blue, int SpeedDelay) {
  int16_t pos=8;
  int j=0;
  int token=0;
  for(uint16_t i=8; i<60; i++) { 
      
      if(pos<=0 && token==0){
        pos=101;
        j=1;
        token=1;
      }
      else if(token==0){
        pos=i-j;
        j=j+2;
      }
      else{
        pos=101-j;
        j++;
      }
      pixels.setPixelColor(i, red, green, blue);
      pixels.setPixelColor(pos, red, green, blue);
      pixels.show();
      
//      Serial.print("pos: ");Serial.print(pos);Serial.print('\n');
//      Serial.print("i: ");Serial.print(i);Serial.print('\n');
//      Serial.print("j: ");Serial.print(j);Serial.print('\n');
      
      delay(SpeedDelay);
  }
}


//colorWipe3--> LED are lit in cirular fashion starting from center of bottom side (60th led) of the hexagonal shape of PRISM to the center of bottom EDGE(8th led). So arriving at 101 one of the index must be reset to 0
//    101 0__
//       /    \
//       \ 60 /
//
//Function can be improved using vectors instead of using if and checking all the possible status of indexes

void colorWipe3(uint32_t red, uint32_t green, uint32_t blue, int SpeedDelay) {
  int16_t pos=60;
  int j=0;
  int token=0;
  for(uint16_t i=60; i>8; i--) { 
      
      if(pos>=101 && token==0){
        pos=0;
        j=1;
        token=1;
      }
      else if(token==0){
        pos=i+j;
        j=j+2;
      }
      else{
        pos=j;
        j++;
      }
      pixels.setPixelColor(i, red, green, blue);
      pixels.setPixelColor(pos, red, green, blue);
      pixels.show();
      
//      Serial.print("pos: ");Serial.print(pos);Serial.print('\n');
//      Serial.print("i: ");Serial.print(i);Serial.print('\n');
//      Serial.print("j: ");Serial.print(j);Serial.print('\n');
      
      delay(SpeedDelay);
  }
}

void pulse(){
  //set color to hex
  
  pixels.fill(0x1414fe);
  pixels.show();
  delay(1000); // wait half a second

  // turn off
  pixels.fill(0x000000);
  pixels.show();
  delay(1000); // wait half a second  
  
}
