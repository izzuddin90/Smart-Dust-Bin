#include <Adafruit_NeoPixel.h> //neopixel library
#include <Servo.h> //servo library

int led= 6;
long duration, dist, average;   
long aver[3];   //array for average

#define NUM_PIXELS 6 //number of neopixels
#define NEOPIXEL_PIN 13 //pin for neopixels

//dist untuk sensor luar tong
#define TRIG_PIN1 4 //trig pin for first ultrasonic sensor (Gray - Hijau )
#define ECHO_PIN1 5 //echo pin for first ultrasonic sensor (Purple - Orange)

//distance2 untuk sensor dalam tong
#define TRIG_PIN2 6 //trig pin for second ultrasonic sensor (Gray - Kuning)
#define ECHO_PIN2 7 //echo pin for second ultrasonic sensor (Purple - Biru)

#define SERVO_PIN 9 //servo pin (Orange)

#define LED_PIN 13 //built-in LED pin

Adafruit_NeoPixel pixels(NUM_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800); //create neopixel object
Servo servo; //create servo object

void setup() {
  pixels.begin(); //initialize neopixels
  pixels.show(); //update neopixels
  Serial.begin(9600); //initialize Serial communication
  pinMode(TRIG_PIN1, OUTPUT); //set first trig pin to output
  pinMode(ECHO_PIN1, INPUT); //set first echo pin to input
  pinMode(TRIG_PIN2, OUTPUT); //set second trig pin to output
  pinMode(ECHO_PIN2, INPUT); //set second echo pin to input
  pinMode(LED_PIN, OUTPUT); //set LED pin to output
  servo.attach(SERVO_PIN); //attach servo to pin
  servo.write(45); //close servo
  delay(100);
  servo.detach(); //detach servo
}

long measure(int trigPin, int echoPin) {
  digitalWrite(LED_PIN, HIGH); //turn on LED
  digitalWrite(trigPin, LOW); //set trig pin to low
  delayMicroseconds(5); //delay
  digitalWrite(trigPin, HIGH); //set trig pin to high
  delayMicroseconds(15); //delay
  digitalWrite(trigPin, LOW); //set trig pin to low
  long duration = pulseIn(echoPin, HIGH); //measure duration of echo pulse
  digitalWrite(LED_PIN, LOW); //turn off LED
  return (duration / 2) / 29.1; //calculate distance
}

void measure() {  
 digitalWrite(10,HIGH);
digitalWrite(TRIG_PIN1, LOW);
delayMicroseconds(5);
digitalWrite(TRIG_PIN1, HIGH);
delayMicroseconds(15);
digitalWrite(TRIG_PIN1, LOW);
pinMode(ECHO_PIN1, INPUT);
duration = pulseIn(ECHO_PIN1, HIGH);
dist = (duration/2) / 29.1;    //obtain distance
}

void setAllPixels(int red, int green, int blue) {
  for (int i = 0; i < NUM_PIXELS; i++) {
    pixels.setPixelColor(i, red, green, blue);
  }
}



void loop() {
    for (int i=0;i<=2;i++) {   //average distance
    measure();               
   aver[i]=dist;            
    delay(10);              //delay between measurements
  }
 dist=(aver[0]+aver[1]+aver[2])/3;    

if ( dist<50 ) {
//Change distance as per your need
 servo.attach(SERVO_PIN);
  delay(1);
  servo.write(180);    
 delay(3000);
 servo.write(45);  
 delay(500); 
 
}

   
  long distance2 = measure(TRIG_PIN2, ECHO_PIN2); //measure distance from second sensor
  long duration = pulseIn(ECHO_PIN2, HIGH);
  
  digitalWrite(TRIG_PIN2, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN2, LOW);
  
  
  Serial.print("Distance: ");
  Serial.print(distance2);
  Serial.println(" cm");
  
  if (distance2 > 18) {
    setAllPixels(0, 255, 0); // turn all pixels green
  } else {
    setPixelRange(distance2);
  }
  
  pixels.show();
}

void setPixelRange(float distance2) {
  //sampah sikit

  if (distance2 >= 15 && distance2 <= 17) {
    pixels.setPixelColor(5, 0, 255, 0);
    pixels.setPixelColor(4, 0, 255, 0);
    pixels.setPixelColor(3, 0, 255, 0);
    pixels.setPixelColor(2, 0, 255, 0);
    pixels.setPixelColor(1, 0, 255, 0);
    pixels.setPixelColor(0, 255, 0, 0);
  } 

  if (distance2 >= 12 && distance2 <= 14) {
    pixels.setPixelColor(5, 0, 255, 0);
    pixels.setPixelColor(4, 0, 255, 0);
    pixels.setPixelColor(3, 0, 255, 0);
    pixels.setPixelColor(2, 0, 255, 0);
    pixels.setPixelColor(1, 255, 0, 0);
    pixels.setPixelColor(0, 255, 0, 0);
  } 
  
  if (distance2 >= 9 && distance2 <= 11) {
    pixels.setPixelColor(5, 0, 255, 0);
    pixels.setPixelColor(4, 0, 255, 0);
    pixels.setPixelColor(3, 0, 255, 0);
    pixels.setPixelColor(2, 255, 0, 0);
    pixels.setPixelColor(1, 255, 0, 0);
    pixels.setPixelColor(0, 255, 0, 0);
  } 
  
  if (distance2 >= 6 && distance2 <= 8) {
    pixels.setPixelColor(5, 0, 255, 0);
    pixels.setPixelColor(4, 0, 255, 0);
    pixels.setPixelColor(3, 255, 0, 0);
    pixels.setPixelColor(2, 255, 0, 0);
    pixels.setPixelColor(1, 255, 0, 0);
    pixels.setPixelColor(0, 255, 0, 0);
  } 
  
  if (distance2 >= 4 && distance2 <= 5) {
    pixels.setPixelColor(5, 0, 255, 0);
    pixels.setPixelColor(4, 255, 0, 0);
    pixels.setPixelColor(3, 255, 0, 0);
    pixels.setPixelColor(2, 255, 0, 0);
    pixels.setPixelColor(1, 255, 0, 0);
    pixels.setPixelColor(0, 255, 0, 0);
    
  } 
  
  if (distance2 >= 0 && distance2 <= 3) {
    pixels.setPixelColor(5, 255, 0 , 0);
    pixels.setPixelColor(4, 255, 0, 0);
    pixels.setPixelColor(3, 255, 0, 0);
    pixels.setPixelColor(2, 255, 0, 0);
    pixels.setPixelColor(1, 255, 0, 0);
    pixels.setPixelColor(0, 255, 0, 0);
    
  } 




		}
