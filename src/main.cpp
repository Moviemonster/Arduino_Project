//Include Libraries
#include <Arduino.h>
#include "PressureSensor.h"
#include "Multi_PressureSensor.h"

// Pins am Arduino für HX711
HX711 P1("P1",2,3,32,true);
HX711 P2("P2",2,3,32);
HX711 P3("P3",2,3,32);
multi_HX711 All_HX711("All_HX711", 3, 32);


/*
HX711 P2("P2",4,5,32,true);
HX711 P3("P3",6,7,32,true);
*/


void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("###################################################################");
  Serial.println("Starting Setup for Sensors\n");
  delay(500);
  //Setup Pressure Sensors
  P1.setup();
  P1.print_private_Data();

  All_HX711.add_HX711(&P1);
  All_HX711.print_multi_HX711();
  All_HX711.add_HX711(&P2);
  All_HX711.print_multi_HX711();
  All_HX711.add_HX711(&P3);
  All_HX711.print_multi_HX711();
  //P1.print_private_Data();

  Serial.println("\nFinished Setup for Sensors");
  Serial.println("###################################################################\n\n\n");
  delay(500);
}



void loop() {
  //Reading Pressure Sensors
  Serial.print("\n");
  P1.read();
  /*
  P2.read();
  P3.read();
  */
  //Serial.print("\n");

  // Ausgabe auf der seriellen Konsole
  P1.printTest();
  /*
  P2.printTest();
  P3.printTest();
  */
  delay(2000);  // Eine Sekunde warten, bevor die nächste Messung durchgeführt wird
}
