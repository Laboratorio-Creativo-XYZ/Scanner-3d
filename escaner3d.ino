/*
  Basado en parto del ejemplo 
  
  Button by DojoDave

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
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//#include <WiFi.h>

// constants won't change. They're used here to set pin numbers:
const int Shutter1 = 16;  //In shield 4 
const int Focus1 = 17;  //In shield 5
const int Shutter2 = 18;  //In shield 6
const int Focus2 = 19;//In shield 7
const int decButton = 14;
const int incButton = 27;
const int leftButton = 26;
const int rightButton = 25;
const int playButton = 23;
const int stopButton = 32;     // the number of the pushbutton pin
const int sda = 21; //Pin salida SDA = GPIO 21 (G21)
const int scl = 22; //Pin salida SCL = GPIO 22 (G22)
const long previousMillis = 0;
const long interval = 500;
const long paso = 200;
const long potencia = 1000;
static const int ServoPin =  13;      // the number of the Servo pin
const int stop = 90; // instruccion para que el servo se detenga
int numerodefotos = 100;

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//aquí empiezan las strings para reproducir en pantalla
String messageStatic = "Scanner 3D";
String messageToScroll = "Laboratorio Creativo XYZ.    Laboratorio Creativo XYZ.     Laboratorio Creativo XYZ.    Laboratorio Creativo XYZ";
String nFotos = "Capturas:";
String Velocidad ="Velocidad:";
String Camara ="Camara:";

//aquí terminan


byte fotos[] = {
  B00000,
  B00010,
  B11111,
  B10001,
  B10101,
  B10001,
  B11111,
  B00000
};

byte num[] = {
  B00011,
  B00011,
  B00000,
  B10010,
  B11010,
  B10110,
  B10010,
  B10010
};
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

int buttonStateDec = 0;
int buttonStateInc = 0;         // variable for reading the pushbutton status
int buttonStateLeft = 0;
int buttonStateRight = 0;
int buttonStatePlay = 0;
int buttonStateStop = 0;

void setup() {
//aquí empieza funcion iniciar LCD
  lcd.begin(21, 22);                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("SCANNER 3D");
  lcd.setCursor(0,1);
  lcd.print("LABORATORIO CREATIVO");
//aquí termina función iniciar LCD


  //aquí empieza la función wifi
  

  //aquí termina la funcion wifi
  
  servo1.attach(ServoPin);    // initialize Servopin

  // initialize the pushbutton pin as an input:
  pinMode(decButton, INPUT);
  pinMode(incButton, INPUT);
  pinMode(leftButton, INPUT);
  pinMode(rightButton, INPUT);
  pinMode(playButton, INPUT);
  pinMode(stopButton, INPUT);

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
  buttonStateDec = digitalRead(decButton);
  buttonStateInc = digitalRead(incButton);
  buttonStateLeft = digitalRead(leftButton);
  buttonStateRight = digitalRead(rightButton);
  buttonStatePlay = digitalRead(playButton);
  buttonStateStop = digitalRead(stopButton);

    if (buttonStateStop == LOW){
    servo1.write(stop);
  }

  if (buttonStateInc == LOW){
     
    servo1.write(40);
    delay(1000);
    servo1.write(stop);
  }

  if (buttonStateLeft == LOW){
     
    servo1.write(200);
    delay(1000);
    servo1.write(stop);
  }

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonStateDec == LOW) {
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
