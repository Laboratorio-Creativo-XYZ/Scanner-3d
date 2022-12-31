/*
  Basado en parte del ejemplo 
  
  Button by DojoDave

  The circuit:
  - pushbutton attached to pin 2 from +5V
  - 10K resistor attached to pin 2 from ground


  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Button
*/
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ezButton.h>
//#include <WiFi.h>

// constants won't change. They're used here to set pin numbers:
const int Shutter1 = 15;  //In shield 4 
const int Focus1 = 16;  //In shield 5
const int Shutter2 = 17;  //In shield 6
const int Focus2 = 18;//In shield 7
ezButton decButton(12);
ezButton incButton(14);
ezButton leftButton(27);
ezButton rightButton(26);
ezButton playButton(25);
ezButton stopButton(32);
ezButton stopButton2(19);     // the number of the pushbutton pin
const int sda = 21; //Pin salida SDA = GPIO 21 (G21)
const int scl = 22; //Pin salida SCL = GPIO 22 (G22)
const long interval = 500;//cuanto espera antes de tomar la foto
const int lcdColumns = 16;//set the LCD number of columns
const int lcdRows = 4;//set the LCD number of rows
const long potencia = 1000;//potencia para activar el servo
const int ServoPin =  13;// the number of the Servo pin
const int stop = 90; // instruccion para que el servo se detenga

int numerodefotos = 10;
int recorridototal = 2000;
int recorrido = recorridototal / numerodefotos;
long previousMillis = 0;

LiquidCrystal_I2C lcd(0x27,lcdColumns,lcdRows);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//aquí empiezan las strings para reproducir en pantalla
String messageStatic = "Scanner 3D";
String messageToScroll = "Laboratorio Creativo XYZ.";
String nFotos = "Capturas:";
String Velocidad ="Velocidad:";
String Camara ="Camara:";
String 360 ="360º=";
String numstrFoto = String(numerodefotos);
String recorridototalstr = String(recorridototal);
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


int buttonStateDec = 0;
int buttonStateInc = 0;         // variable for reading the pushbutton status
int buttonStateLeft = 0;
int buttonStateRight = 0;
int buttonStatePlay = 0;
int buttonStateStop = 0;
int buttonStateStop2 = 0;

//aquí empieza la función ScollText
void scrollText(int row, String message, int delayTime, int lcdColumns) {
  for (int i=0; i < lcdColumns; i++) {
    message = " " + message;  
  } 
  message = message + " "; 
  for (int pos = 0; pos < message.length(); pos++) {
    lcd.setCursor(0, row);
    lcd.print(message.substring(pos, pos + lcdColumns));
    delay(delayTime);
  }
}
//Aquí termina la función ScrollText

/*/Aquí empieza la función waitForMillis
void waitForMillis(unsigned long millis) {
  unsigned long start = millis();
  while (millis() - start < millis) {
    // Do nothing
  }
}
*///Aquí termina waitForMillis

/*/Aquí empieza la función startScan
void startScan() {
      for(int i = 0; i <= numerodefotos; i++){   
      servo1.write(potencia);
      delay(paso);
      servo1.write(stop);
      delay(interval);
      digitalWrite(Shutter1, HIGH);
      delay(100);
      digitalWrite(Shutter1, LOW);
      delay(interval);
          if (buttonStateStop == HIGH){
    break;     // Button was pressed, stop the loop
  }
  delay(5000);
}
}
*///Aquí termina la función startScan

void setup() {
  Serial.begin(19200);
//aquí empieza funcion iniciar LCD
  lcd.begin(21, 22);                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0, 0);
  // print static message
  lcd.print(messageStatic);
  // print scrolling message
  scrollText(1, messageToScroll, 500, lcdColumns);
//aquí termina función iniciar LCD


  //aquí empieza la función wifi
  

  //aquí termina la funcion wifi
  
  servo1.attach(ServoPin);    // initialize Servopin

  /*// initialize the pushbutton pin as an input:
  pinMode(decButton, INPUT);
  pinMode(incButton, INPUT);
  pinMode(leftButton, INPUT);
  pinMode(rightButton, INPUT);
  pinMode(playButton, INPUT);
  pinMode(stopButton, INPUT);
  pinMode(stopButton2, INPUT);
*/
  //Initialize Shutter & Focus Pins
  
  pinMode(Shutter1, OUTPUT);
  pinMode(Focus1, OUTPUT);
  pinMode(Shutter2, OUTPUT);
  pinMode(Focus2, OUTPUT);

  lcd.setCursor(0, 1);
  lcd.print(nFotos);
  lcd.setCursor(9, 1);
  lcd.print(numstrFoto);
  lcd.setCursor(0, 2);
  lcd.print(360);
  }
  
void loop() {
  decButton.loop(); // MUST call the loop() function first
    incButton.loop(); // MUST call the loop() function first
      leftButton.loop(); // MUST call the loop() function first
        rightButton.loop(); // MUST call the loop() function first
          playButton.loop(); // MUST call the loop() function first
            stopButton.loop(); // MUST call the loop() function first
              stopButton2.loop(); // MUST call the loop() function first

/* //empieza wifi dentro del loop

*///termina el wifi dentro del loop
 
  // read the state of the pushbutton value:
  int DecbtnState = decButton.getState();
  Serial.println(DecbtnState);
    Serial.println("DEC");
  int IncbtnState = incButton.getState();
  Serial.println(IncbtnState);
   Serial.println("INC");
  int LeftbtnState = leftButton.getState();
  Serial.println(LeftbtnState);
   Serial.println("LEFT");
  int RightbtnState = rightButton.getState();
  Serial.println(RightbtnState);
   Serial.println("RIGHT");
  int PlaybtnState = playButton.getState();
  Serial.println(PlaybtnState);
   Serial.println("PLAY");
  int StopbtnState = stopButton.getState();
  Serial.println(StopbtnState);
   Serial.println("STOP");
  int Stop2btnState = stopButton2.getState();
  Serial.println(Stop2btnState);
   Serial.println("STOP2");

/*
  buttonStateDec = digitalRead(decButton);
  buttonStateInc = digitalRead(incButton);
  buttonStateLeft = digitalRead(leftButton);
  buttonStateRight = digitalRead(rightButton);
  buttonStatePlay = digitalRead(playButton);
  buttonStateStop = digitalRead(stopButton);
  buttonStateStop2 = digitalRead(stopButton2);
*/
  if (IncbtnState == 0){
      numerodefotos++;
      lcd.setCursor(9, 1);
  lcd.print(numstrFoto);
  }

  if (DecbtnState == 0){
      numerodefotos--;
      lcd.setCursor(6, 1);
  lcd.print(numstrFoto);
  }

  if (LeftbtnState == 0){
      recorridototal++;
      lcd.setCursor(6, 2);
      lcd.print(recorridototalstr);
  }

  if (RighttbtnState == 0){
      recorridototal--;
      lcd.setCursor(9, 2);
      lcd.print(recorridototalstr);
  }

  if (PlaybtnState == 0) {
    
      for(int i = 1; i <= numerodefotos; i++){   
      servo1.write(potencia);
      delay(recorrido);
      servo1.write(stop);
      delay(interval);
      digitalWrite(Shutter1, HIGH);
      delay(100);
      digitalWrite(Shutter1, LOW);
      delay(interval);
        stopButton.loop();
        int StopbtnState = stopButton.getState();
        if (StopbtnState == 0){
    break;     // Button was pressed, stop the loop
    }
  }
  }
}
