#include <Adafruit_NeoPixel.h>
/* 
 *  Different restrictions as to how bright the LED will be at what distance(in cm). 
 *  Then we define the different frquencies of the buzzer. Must then create the different variables for the LED's, what pins theyre attached to etc. 
 *  Define the different points which the LED's changing colours.
 *  The buzzer should only sound when the led turns red. When does it turn red?

*/

#define PIN 8//going to be attached to pin 8 on the flora board
#define PINS 3

#define GREEN_LONG 600
#define GREEN_SHORT 200
#define YELLOW_LONG 199
#define YELLOW_SHORT 100
#define RED_LONG 99
#define RED_SHORT 0


#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

//#define NUMPIXELS 3 //going to attach 3 neopixels



int buzzpin = 6;
const int pwPin1 = 10;
long sensor, inches, cm, val1,val2,val3;
boolean t;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1,PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1,PINS, NEO_GRB + NEO_KHZ800);



void setup() {
  // put your setup code here, to run once:
  pinMode(pwPin1, INPUT);
  pinMode(buzzpin,OUTPUT);
  pixels.begin();
  pixel.begin();
  pixel.show();
  pixels.show();
  
}

void read_sensor (){      //Getting sensor readings 
sensor = pulseIn(pwPin1, HIGH); // Variable to store sensor readings 
inches = sensor / 147; // Converting to inches
cm = inches * 2.54; // Going from inches to centimeters
}

void print_range(){ // Printing to the serial monitor
Serial.print("CM");
Serial.println(cm);
}

void loop() {
  // put your main code here, to run repeatedly:    
    val1 = map(cm,RED_SHORT,RED_LONG,1,5);
    val2 = map(cm,YELLOW_SHORT,YELLOW_LONG,1,5);
    val3 = map(cm,GREEN_SHORT,GREEN_LONG,1,5);
    if(cm <= RED_LONG && cm >= RED_SHORT){
      for(int z = 0;z < pixel.numPixels();z++){
       for(int i =0; i <255;i++){
         pixels.setPixelColor(0,pixels.Color(i,0,0));
         pixel.setPixelColor(z,pixel.Color(i,0,0));
         pixel.show();
         pixels.show();
         delay(val1);
      }

      for(int j =255; j > 0;j--){
        pixels.setPixelColor(0,pixels.Color(j,0,0));
        pixel.setPixelColor(z,pixel.Color(j,0,0));
        pixel.show();
        pixels.show();
        delay(val1);
       }
      }
    tone(buzzpin,NOTE_C7); //Using a frequency of 2000 or C7 
    }

    
    else if(cm <= YELLOW_LONG && cm >= YELLOW_SHORT){  // If the sensor reads an object between 200cm and 100cm away, turn the LED Yellow. By using the map function we can change intensity of yellow depending on distance. 
      for(int z = 0;z < pixel.numPixels();z++){
       for(int i =0; i <255;i++){
         pixels.setPixelColor(0,pixels.Color(i,i,0));
         pixel.setPixelColor(z,pixel.Color(i,i,0));
         pixel.show();
         pixels.show();
         delay(val2);
      }

      for(int j =255; j > 0;j--){
        pixels.setPixelColor(0,pixels.Color(j,j,0));
        pixel.setPixelColor(z,pixel.Color(j,j,0));
        pixel.show();
        pixels.show();
        delay(val2);
      }
      }
    
    pixels.show();
    pixel.show();
    noTone(buzzpin);
    }
    
    else if(cm >= GREEN_SHORT){
      for(int z = 0;z < pixel.numPixels();z++){
        for(int i =0; i <255;i++){
         pixels.setPixelColor(0,pixels.Color(0,i,0));
         pixel.setPixelColor(z,pixel.Color(0,i,0));
         pixel.show();
         pixels.show();
         delay(val3);
      }

      for(int j =255; j > 0;j--){
        pixels.setPixelColor(0,pixels.Color(0,j,0));
        pixel.setPixelColor(z,pixel.Color(0,j,0));
        pixel.show();
        pixels.show();
        delay(val3);
      }
      }
    pixels.show();
    pixel.show();
    noTone(buzzpin);
    }

read_sensor();
print_range();
//fade();
delay(100);
}


//void colorWipe(uint32_t c, uint8_t wait){          //This is going to be used to make the number of additional neopixels, setColorPixel sets the color pixel to the RGB value passed in this function
  //for(uint16_t i = 0;i < pixels.numPixels();i++){
    //pixels.setPixelColor(i, c);
    //pixel.setPixelColor(i, c);
    //pixels.show();
    //pixel.show();
    //delay(wait);
    //}



  
