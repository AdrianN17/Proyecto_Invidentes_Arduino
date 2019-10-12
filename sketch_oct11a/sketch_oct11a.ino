#include <SoftwareSerial.h>

#define PIN_TRIGGER 7
#define PIN_ECHO 8
#define PIN_LED 4

SoftwareSerial BT(10, 11); // RX | TX

void setup() {

  pinMode(PIN_TRIGGER, OUTPUT);
  pinMode(PIN_ECHO, INPUT); 
  digitalWrite(PIN_TRIGGER, LOW);

  pinMode(PIN_LED,INPUT);
  
  BT.begin(9600);
  Serial.begin(9600);

}

void loop() {
  digitalWrite(PIN_LED, HIGH);

  
  long t; 
  long d; 

  digitalWrite(PIN_TRIGGER, HIGH);
  delayMicroseconds(10);       
  digitalWrite(PIN_TRIGGER, LOW);
  
  t = pulseIn(PIN_ECHO, HIGH);
  d = t/59; 
  
  /*Serial.print("Distancia: ");
        
  Serial.print("cm");
  Serial.println();*/
  BT.println(d);

  
  
  delay(100);      

     

}
