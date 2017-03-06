#include <Adafruit_NeoPixel.h>
/* 
 *  Different restrictions as to how bright the LED will be at what distance(in cm). 
 *  Then we define the different frquencies of the buzzer. Must then create the different variables for the LED's, what pins theyre attached to etc. 
 *  Define the different points which the LED's changing colours.
 *  The buzzer should only sound when the led turns red. When does it turn red?

*/

#define PIN 8//going to be attached to pin 8 on the flora board
#define PINS 3
#define TRIG_PIN 1
#define ECHO_PIN 0

#define GREEN_LONG 600
#define GREEN_SHORT 200
#define YELLOW_LONG 199
#define YELLOW_SHORT 100
#define RED_LONG 99
#define RED_SHORT 0




//#define NUMPIXELS 3 //going to attach 3 neopixels



int buzzpin = 6;
const int pwPin1 = 10;
long sensor, inches, cm, val1,val2,val3,val4;
boolean t;
unsigned long t1;
unsigned long t2;
unsigned long pulse_width;
float cm2;
//const unsigned int MAX_DIST = 23200;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1,PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1,PINS, NEO_GRB + NEO_KHZ800);



void setup() {
  // put your setup code here, to run once:
  pinMode(pwPin1, INPUT);
  pinMode(buzzpin,OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  pixels.begin();
  pixel.begin();
  pixel.show();
  pixels.show();
  
}

void read_front_sensor (){      //Getting sensor readings 
sensor = pulseIn(pwPin1, HIGH); // Variable to store sensor readings 
inches = sensor / 147; // Converting to inches
cm = inches * 2.54; // Going from inches to centimeters
}

void read_back_sensor(){
   digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Wait for pulse on echo pin
  while ( digitalRead(ECHO_PIN) == 0 );

  // Measure how long the echo pin was held high (pulse width)
  // Note: the micros() counter will overflow after ~70 min
  t1 = micros();
  while ( digitalRead(ECHO_PIN) == 1);
  t2 = micros();
  pulse_width = t2 - t1;


  inches = pulse_width / 147;
  cm2 = inches * 2.54;
  
    Serial.print(cm2);
    Serial.println(" cm \t");
    Serial.println(cm);
    
  }
  
  // Wait at least 60ms before next measurement
 
  



void print_range(){ // Printing to the serial monitor
Serial.print("CM");
Serial.println(cm2);
}

void loop() {
// put your main code here, to run repeatedly:
if(cm < 100 && cm2 < 100){
  val4 = map(cm2,0,100,1,5);
  for(int z = 0;z < pixel.numPixels();z++){
       for(int i =0; i <= 255;i++){
         pixels.setPixelColor(0,pixels.Color(i,0,i));
         pixel.setPixelColor(z,pixel.Color(i,0,i));
         pixel.show();
         pixels.show();
         delay(val4);
      }
      for(int j =255; j > 0;j--){
        pixels.setPixelColor(0,pixels.Color(j,0,j));
        pixel.setPixelColor(z,pixel.Color(j,0,j));
        pixel.show();
        pixels.show();
        tone(buzzpin,1000,100);
        delay(val4);
       }
       
      }
  }

else{
  if(cm2 < 100){    
  PWM();
  }

  else{
    Ultrasonic();
    }
  }
    read_front_sensor();
    read_back_sensor();
}


void PWM(){
  val4 = map(cm2,0,100,1,5);
  for(int z = 0;z < pixel.numPixels();z++){
       for(int i =0; i <= 255;i++){
         pixels.setPixelColor(0,pixels.Color(0,0,i));
         pixel.setPixelColor(z,pixel.Color(0,0,i));
         pixel.show();
         pixels.show();
         delay(val4);
      }
      for(int j =255; j > 0;j--){
        pixels.setPixelColor(0,pixels.Color(0,0,j));
        pixel.setPixelColor(z,pixel.Color(0,0,j));
        pixel.show();
        pixels.show();
        tone(buzzpin,2000,100);
        delay(val4);
       }
       
      }
      
  }

void Ultrasonic(){
    val1 = map(cm,RED_SHORT,RED_LONG,1,5);
    val2 = map(cm,YELLOW_SHORT,YELLOW_LONG,1,5);
    val3 = map(cm,GREEN_SHORT,GREEN_LONG,1,5);
    
    
    if((cm <= 100 && cm >= 0)){
      for(int z = 0;z < pixel.numPixels();z++){
       for(int i =0; i <= 255;i++){
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
     //Using a frequency of 2000 or C7 
    tone(buzzpin,4000,100);
    }
    

    
    else if((cm <= YELLOW_LONG && cm >= YELLOW_SHORT)){  // If the sensor reads an object between 200cm and 100cm away, turn the LED Yellow. By using the map function we can change intensity of yellow depending on distance. 
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
    
    else if((cm >= GREEN_SHORT)){
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
}



//void colorWipe(uint32_t c, uint8_t wait){          //This is going to be used to make the number of additional neopixels, setColorPixel sets the color pixel to the RGB value passed in this function
  //for(uint16_t i = 0;i < pixels.numPixels();i++){
    //pixels.setPixelColor(i, c);
    //pixel.setPixelColor(i, c);
    //pixels.show();
    //pixel.show();
    //delay(wait);
    //}



  
