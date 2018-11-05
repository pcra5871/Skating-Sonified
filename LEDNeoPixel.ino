
#include <Adafruit_NeoPixel.h>
#include <math.h>

#define N_PIXELS  24  // Number of pixels in strand
#define MIC_PIN   A1  // Microphone is attached to this analog pin
#define LED_PIN    A0  // NeoPixel LED strand is connected to this pin
#define SAMPLE_WINDOW   10  // Sample window for average level
//  #define PEAK_HANG 24 //Time of pause before peak dot falls
//   #define PEAK_FALL 4 //Rate of falling peak dot
#define INPUT_FLOOR 10 //Lower range of analogRead input
#define INPUT_CEILING 300 //Max range of analogRead input, the lower the value the more sensitive (1023 = max)



//    byte peak = 16;      // Peak level of column; used for falling dots
unsigned int sample;

byte dotCount = 0;  //Frame counter for peak dot
byte dotHangCount = 0; //Frame counter for holding peak dot

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

}

void loop() {

  unsigned long startMillis = millis(); // Start of sample window
  float peakToPeak = 0;   // peak-to-peak level

  unsigned int signalMax = 0;
  unsigned int signalMin = 1023;
  unsigned int c, y;





  // collect data for length of sample window (in mS)
  sample = analogRead(MIC_PIN);
  //
  if (sample < 1024)  // toss out spurious readings
  { //Serial.print(sample);
    Serial.println(sample);
    //peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude



    int r = map(sample, 300, 1024, 0, 255);

    Serial.println(r);
    // delay(200);
    uint32_t col = strip.Color(r, 0, r);

    for (int i = 0; i < N_PIXELS; i++) {
      strip.setPixelColor(i,col);
    }
    strip.show(); // Initialize all pixels to 'off'

  }

}
