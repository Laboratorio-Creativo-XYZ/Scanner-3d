/*
  Basado en parte del ejemplo 
  
  Button by DojoDave

  The circuit:
  - pushbutton attached to pin 2 from +5V
  - 10K resistor attached to pin 2 from ground


  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Button
*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ezButton.h>
#include <AccelStepper.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <ArduinoJson.h>
//WiFi param
const char *ssid = "Escaner3D";
const char *password = "LaboratorioXYZ";
WiFiServer server(80);


// constants won't change. They're used here to set pin numbers:
const int Shutter1 = 15;  //In shield 4 
const int Focus1 = 16;  //In shield 5
const int Shutter2 = 17;  //In shield 6
const int Focus2 = 18;//In shield 7
ezButton decButton(12); //12
ezButton incButton(14); //14
ezButton leftButton(27); //27
ezButton rightButton(26); //26
ezButton playButton(25); //25
ezButton stopButton(32); //32
const int sda = 21; //Pin salida SDA = GPIO 21 (G21)
const int scl = 22; //Pin salida SCL = GPIO 22 (G22)
const long interval = 600;//cuanto espera antes de tomar la foto
const int lcdColumns = 20;//set the LCD number of columns
const int lcdRows = 4;//set the LCD number of rows
const long potencia = 1000;//potencia para activar el servo
const int stepPin =  13;
const int dirPin = 19;
AccelStepper stepper(1, stepPin, dirPin); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
int numerodefotos = 10;
int recorridototal = 2700;
int recorrido = recorridototal / numerodefotos;

LiquidCrystal_I2C lcd(0x27,lcdColumns,lcdRows);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//aquí empiezan las strings para reproducir en pantalla
String messageStatic = "Scanner 3D";
String messageToScroll = "Laboratorio Creativo XYZ.";
String nFotos = "Capturas:";
String Velocidad ="Velocidad:";
String Camara ="Camara:";
String tressesenta ="360=";
String numstrFoto = String(numerodefotos);
String recorridototalstr = String(recorridototal);
//aquí terminan


int buttonStateDec = 0;
int buttonStateInc = 0;         // variable for reading the pushbutton status
int buttonStateLeft = 0;
int buttonStateRight = 0;
int buttonStatePlay = 0;
int buttonStateStop = 0;

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

void setup() {
  stepper.setMaxSpeed(500);
  stepper.setAcceleration(100);
  Serial.begin(115200);
  lcd.begin(21, 22);                      // initialize the lcd 
  lcd.backlight();
  Serial.println();
  Serial.println("Configuring access point...");

//aquí empieza la función wifi
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();
  Serial.println("Server started");
//aquí termina la funcion wifi


lcd.setCursor(10, 0);  // Print a message to the LCD.
lcd.print(messageStatic); // print static message
 
scrollText(1, messageToScroll, 500, lcdColumns); // print scrolling message

//Initialize Shutter & Focus Pins
  
  pinMode(Shutter1, OUTPUT);
  pinMode(Focus1, OUTPUT);
  pinMode(Shutter2, OUTPUT);
  pinMode(Focus2, OUTPUT);

  lcd.setCursor(0, 1);
  lcd.print(nFotos);
  lcd.setCursor(9, 1);
  if (numerodefotos < 100) {
      lcd.print("0");
  }
  lcd.print(numerodefotos);
  lcd.setCursor(0, 2);
  lcd.print(tressesenta);
  lcd.setCursor(5, 2);
    if (recorridototal < 10000) {
      lcd.print("0");
  }
  lcd.print(recorridototal);
  lcd.setCursor(5, 3);
  lcd.print(recorrido);
  lcd.setCursor(13, 1);
  lcd.print("Now:");
  lcd.setCursor(17, 1);
  lcd.print("Rdy");
  }
  
void loop() {
  WiFiClient client = server.available();   // listen for incoming clients
    if (client) {
    // A client has connected
    Serial.println("Client connected");
    }
 int recorrido = recorridototal / numerodefotos;

  decButton.loop(); // MUST call the loop() function first
    incButton.loop(); // MUST call the loop() function first
      leftButton.loop(); // MUST call the loop() function first
        rightButton.loop(); // MUST call the loop() function first
          playButton.loop(); // MUST call the loop() function first
            stopButton.loop(); // MUST call the loop() function first


 
  // read the state of the pushbutton value:
  int DecbtnState = decButton.getState();
  //Serial.println(DecbtnState);
  //Serial.println("DEC");
  int IncbtnState = incButton.getState();
  //Serial.println(IncbtnState);
  //Serial.println("INC");
  int LeftbtnState = leftButton.getState();
  //Serial.println(LeftbtnState);
  //Serial.println("LEFT");
  int RightbtnState = rightButton.getState();
  //Serial.println(RightbtnState);
  //Serial.println("RIGHT");
  int PlaybtnState = playButton.getState();
  //Serial.println(PlaybtnState);
  //Serial.println("PLAY");
  int StopbtnState = stopButton.getState();
  //Serial.println(StopbtnState);
  //Serial.println("STOP");

  if (IncbtnState == 0){
    Serial.println("INC");
      numerodefotos++;
      delay(300);
      lcd.setCursor(9, 1);
      if (numerodefotos < 100) {
      lcd.print("0");
        if (numerodefotos < 10) {
        lcd.print("0");
        }
      }
      lcd.print(numerodefotos);
  }

  if (DecbtnState == 0){
    Serial.println("DEC");
      numerodefotos--;
            if (numerodefotos <= 1) {
              numerodefotos = 1;
            }
      delay(300);
      lcd.setCursor(9, 1);
      if (numerodefotos < 100) {
      lcd.print("0");
        if (numerodefotos < 10) {
        lcd.print("0");
        }
      }
      lcd.print(numerodefotos);
  }

  if (LeftbtnState == 0){
    Serial.println("LEFT");
      recorridototal-=1;
            if (recorridototal <= 0) {
              recorridototal = 0;
            }
      delay(200);
      lcd.setCursor(5, 2);
      if (recorridototal < 10000) {
      lcd.print("0");
        if (recorridototal < 1000) {
          lcd.print("0");
            if (recorridototal < 100) {
            lcd.print("0");
              if (recorridototal < 10) {
              lcd.print("0");
            }
          }
        }
      }
      lcd.print(recorridototal);
  }

  if (RightbtnState == 0){
    Serial.println("RIGHT");
      recorridototal+=1;
      delay(200);
      lcd.setCursor(5, 2);
          if (recorridototal < 10000) {
          lcd.print("0");
        if (recorridototal < 1000) {
          lcd.print("0");
            if (recorridototal < 100) {
            lcd.print("0");
              if (recorridototal < 10) {
              lcd.print("0");
          }
        }
      }
    }
      lcd.print(recorridototal);
  }
  if (StopbtnState == 0){
        Serial.println("STOP");
      }
  if (PlaybtnState == 0) {
    Serial.println("PLAY");
        digitalWrite(Shutter1, HIGH);
        delay(100);
        digitalWrite(Shutter1, LOW);
        delay(interval);
      for(int i = 1; i <= numerodefotos; i++){ 
         lcd.setCursor(17, 1);
                     if (i < 100) {
            lcd.print("0");
              if (i < 10) {
              lcd.print("0");
          }
        }
         lcd.print(i);
      Serial.println(i);  
      stepper.move(recorrido);
      stepper.runToPosition();
      delay(interval);
      digitalWrite(Shutter1, HIGH);
      delay(200);
      digitalWrite(Shutter1, LOW);
      delay(interval);
        stopButton.loop();
        int StopbtnState = stopButton.getState();
        if (StopbtnState == 0){
          break;     // Button was pressed, stop the loop
        }
      }
      lcd.setCursor(17, 1);
      lcd.print("Rdy");
  }
  lcd.setCursor(5, 3);
        if (recorrido < 10000) {
        lcd.print("0");
          if (recorrido < 1000) {
          lcd.print("0");
            if (recorrido < 100) {
            lcd.print("0");
              if (recorrido < 10) {
              lcd.print("0");
              }
            }
          }
        }
  lcd.print(recorrido);
}