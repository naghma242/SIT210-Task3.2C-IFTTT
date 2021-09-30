/* 
  Sketch generated by the Arduino IoT Cloud Thing "3.2C"
  https://create.arduino.cc/cloud/things/96142bc9-6a95-4241-b192-965f1f6b92f9 

  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  bool led;
  CloudIlluminance light;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

int light1 =2;
#include <Arduino.h>
#include <hp_BH1750.h>  //  include the library
hp_BH1750 BH1750;


#include "thingProperties.h"

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);

  pinMode(light1,OUTPUT);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  bool avail = BH1750.begin(BH1750_TO_GROUND);

  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
 
  BH1750.start();   //starts a measurement
  light =BH1750.getLux();  //  waits until a conversion finished

   if(light > 100)
   {
    led = HIGH;
    onLedChange();
   }

   else
   {
     led =LOW;
   }
}

void onLedChange() 
{
  digitalWrite(light1,HIGH);
  delay(2000);
  digitalWrite(light1,LOW);
  delay(500);
}
