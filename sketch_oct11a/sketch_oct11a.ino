#include <NMEAGPS.h>
#include <AltSoftSerial.h>

#define Bluetooth Serial 
AltSoftSerial gpsPort; // RX is 8 (to GPS tx), TX is 9 (to GPS rx)

 

NMEAGPS gps; 
gps_fix fix; 


#define PIN_TRIGGER 6
#define PIN_ECHO 7

float datos[3] = {0,0,0};


void setup() {
  
  gpsPort.begin(9600);
  Bluetooth.begin(9600);
  Bluetooth.println("GPS Start");
  Bluetooth.println("Bluetooth On please press 1 or 0 blink LED ..");

  pinMode(PIN_TRIGGER, OUTPUT);
  pinMode(PIN_ECHO, INPUT); 
  digitalWrite(PIN_TRIGGER, LOW);

}

void loop() {

  if (gps.available( gpsPort)) {
    fix = gps.read();  

    datos[1] = fix.latitude();
    datos[2] = fix.longitude();

  }
  ultrasonido_modulo();
  
  String cadena=  (String)datos[0] + "-" + (String)datos[1] + "-" +(String)datos[2] ;
  
  Bluetooth.println(cadena);
  
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
