#include "TinyGPS++.h"
#include "NeoSWSerial.h"
#include "AltSoftSerial.h"

#define PIN_TRIGGER 6
#define PIN_ECHO 7

NeoSWSerial BT(10,11); // RX | TX
NeoSWSerial serial_connection(9,8); //RX=pin 10, TX=pin 11
TinyGPSPlus gps;//This is the GPS object that will pretty much do all the grunt work with the NMEA data


float datos[3] = {0,0,0};

void setup()
{
  Serial.begin(9600);
  
  //BT.begin(9600);

  serial_connection.begin(9600);
  
  pinMode(PIN_TRIGGER, OUTPUT);
  pinMode(PIN_ECHO, INPUT); 
  digitalWrite(PIN_TRIGGER, LOW);
}

void loop()
{
  gps_modulo();
  
  ultrasonido_modulo();
  
  String cadena=  (String)datos[0] + "-" + (String)datos[1] + "-" +(String)datos[2] ;
  
  //BT.println(cadena);
  Serial.println(cadena);
}

void ultrasonido_modulo()
{

  long t;  

  digitalWrite(PIN_TRIGGER, HIGH);
  delayMicroseconds(10);       
  digitalWrite(PIN_TRIGGER, LOW);
  
  t = pulseIn(PIN_ECHO, HIGH);
  datos[0] = t/59; 

}

void gps_modulo()
{
  while(serial_connection.available())//While there are characters to come from the GPS
  {
      gps.encode(serial_connection.read());//This feeds the serial NMEA data into the library one char at a time
  }
  
  if(gps.location.isUpdated())//This will pretty much be fired all the time anyway but will at least reduce it to only after a package of NMEA data comes in
  {    
    datos[1] = gps.location.lat();
    datos[2] = gps.location.lng();
  }
}
