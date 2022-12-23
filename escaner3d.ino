/*
  Button

  Turns on and off a light emitting diode(LED) connected to digital pin 13,
  when pressing a pushbutton attached to pin 2.

  The circuit:
  - LED attached from pin 13 to ground through 220 ohm resistor
  - pushbutton attached to pin 2 from +5V
  - 10K resistor attached to pin 2 from ground

  - Note: on most Arduinos there is already an LED on the board
    attached to pin 13.

  created 2005
  by DojoDave <http://www.0j0.org>
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Button
*/
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

#include <WiFi.h>
//agregar algo desde mac
//agrego algo en el pc
// constants won't change. They're used here to set pin numbers:
const int Shutter1 = 16;  //In shield 4 
const int Focus1 = 17;  //In shield 5
const int Shutter2 = 18;  //In shield 6
const int Focus2 = 19;//In shield 7
const int buttonPin1 = 14;
const int buttonPin2 = 27;
const int buttonPin3 = 26;
const int buttonPin4 = 25;
const int buttonPin5 = 23;
const int buttonPin6 = 32;     // the number of the pushbutton pin
const int sda = 21; //Pin salida SDA = GPIO 21 (G21)
const int scl = 22; //Pin salida SCL = GPIO 22 (G22)
const long previousMillis = 0;
const long interval = 500;
const long paso = 200;
const long potencia = 1000;
static const int ServoPin =  13;      // the number of the Servo pin
int stop = 90; // instruccion para que el servo se detenga
/*
const char* ssid     = "your-ssid";
const char* password = "your-password";

const char* host = "data.sparkfun.com";
const char* streamId   = "....................";
const char* privateKey = "....................";

WiFiServer server(80);
*/
Servo servo1;

// variables will change:
int pasos = 10;

int buttonState1 = 0;
int buttonState2 = 0;         // variable for reading the pushbutton status
int buttonState3 = 0;
int buttonState4 = 0;
int buttonState5 = 0;
int buttonState6 = 0;

void setup() {

  //aquí empieza la función wifi
  

  //aquí termina la funcion wifi
  // initialize Servopin
  servo1.attach(ServoPin);    

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
  pinMode(buttonPin5, INPUT);
  pinMode(buttonPin6, INPUT);

  //Initialize Shutter & Focus Pins
  
  pinMode(Shutter1, OUTPUT);
  pinMode(Focus1, OUTPUT);
  pinMode(Shutter2, OUTPUT);
  pinMode(Focus2, OUTPUT);

  //Initialize SDA & SCL I2C Interface


  }
  

void loop() {
/* //empieza wifi dentro del loop

*///termina el wifi dentro del loop

  // read the state of the pushbutton value:
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin1);
  buttonState5 = digitalRead(buttonPin2);
  buttonState6 = digitalRead(buttonPin3);

  if (buttonState2 == LOW){
     
    servo1.write(40);
    delay(1000);
    servo1.write(stop);
  }

  if (buttonState3 == LOW){
     
    servo1.write(200);
    delay(1000);
    servo1.write(stop);
  }

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState1 == LOW) {
    // turn LED on:
      for(int i = 1; i <= pasos; i++){
      //servo1.attach(ServoPin);    
      servo1.write(potencia);
      delay(paso);
      servo1.write(stop);
      delay(interval);
      digitalWrite(Shutter1, HIGH);
      delay(100);
      digitalWrite(Shutter1, LOW);
      delay(400);
      
      //analogWrite(PWMpin, i);
    }
  }}
