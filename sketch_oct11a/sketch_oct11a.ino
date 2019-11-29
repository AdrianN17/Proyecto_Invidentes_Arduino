#include <NMEAGPS.h>
const float FEET_PER_METER = 3.28084;

#include <AltSoftSerial.h>// import the serial library
AltSoftSerial gpsPort; // RX is 8 (to GPS tx), TX is 9 (to GPS rx)

#define Genotronex Serial  // just an "alias" for Serial to make the code more readable

NMEAGPS gps; // the parser
gps_fix fix; // the struct with all the parsed values


#define PIN_TRIGGER 6
#define PIN_ECHO 7

float datos[3] = {0,0,0};


void setup() {
  //Serial.begin(9600);  // not needed if Genotronex *is* Serial
  gpsPort.begin(9600);
  Genotronex.begin(9600);
  Genotronex.println("GPS Start");
  Genotronex.println("Bluetooth On please press 1 or 0 blink LED ..");

  pinMode(PIN_TRIGGER, OUTPUT);
  pinMode(PIN_ECHO, INPUT); 
  digitalWrite(PIN_TRIGGER, LOW);

}

void loop() {

  if (gps.available( gpsPort)) {
    fix = gps.read();  // get the latest GPS info (all in one struct)

    datos[1] = fix.latitude();
    datos[2] = fix.longitude();
  


      /*Genotronex.println("LED  On D13 ON ! ");

      //Get the latest info from the gps object which it derived from the data sent by the GPS unit
      Genotronex.println("Satellite Count:");
      Genotronex.println( fix.satellites );
      Genotronex.println("Latitude:");
      Genotronex.println( fix.latitude(), 6);
      Genotronex.println("Longitude:");
      Genotronex.println( fix.longitude(), 6);
      Genotronex.println("Speed MPH:");
      Genotronex.println( fix.speed_mph() );
      Genotronex.println("Altitude Feet:");
      Genotronex.println( fix.altitude() * FEET_PER_METER );
      Genotronex.println();*/
 
    
  }
  ultrasonido_modulo();
  
  String cadena=  (String)datos[0] + "-" + (String)datos[1] + "-" +(String)datos[2] ;
  
  Genotronex.println(cadena);
  
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
