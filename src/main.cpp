//Include Libraries
#include <Arduino.h>
#include "PressureSensor.h"
#include "Multi_PressureSensor.h"

// Pins am Arduino für HX711
HX711 P1("P1",5,4,32,true);
HX711 P2("P2",6,6,32,true);
HX711 P3("P3",7,8,32,true);

multi_HX711 All_HX711("All_HX711", 4, 32);

long Loop_counter = 0;

void setup() {
  Serial.begin(115200);
  delay(500);
  
  Serial.println("###################################################################");
  Serial.println("Starting Setup for Sensors\n");
  delay(500);

  //Setup Pressure Sensors
  P1.setup();
  P1.set_U_m_and_U_b(1.1688 , 0.0989);
  P1.set_P_m_and_P_b(0.1972 , 4.0057);
  P1.print_private_Data();

  P2.setup();
  P2.set_U_m_and_U_b(1.1546 , 0.2049);
  P2.set_P_m_and_P_b(0.2021 , 5.1914);
  P2.print_private_Data();

  P3.setup();
  P3.set_U_m_and_U_b(1.1685 , 0.1738);
  P3.set_P_m_and_P_b(0.2002 , 2.9633);
  P3.print_private_Data();
  
  All_HX711.add_HX711(&P1);
  All_HX711.add_HX711(&P2);
  All_HX711.add_HX711(&P3);
  All_HX711.setup_overwrite();
  All_HX711.print_multi_HX711();
  
  test_print(&P1);

  Serial.println("\nFinished Setup for Sensors");
  Serial.println("###################################################################\n\n\n");
  delay(500);
  Serial.println("Start");
}

void loop() {
  Loop_counter ++;
  Serial.print("\n\nMessung ");
  Serial.print(Loop_counter);
  //Reading Pressure Sensors

  /*
  P1.read();
  P2.read();
  P3.read();
  Serial.print("\nP1:\n");
  P1.printTest();
  Serial.println("\nP2:");
  P2.printTest();
  Serial.println("\nP3:");
  P3.printTest();
  */
  
  All_HX711.read();
  //P1.printTest();
  All_HX711.printTest();
  
  // Ausgabe auf der seriellen Konsole

  delay(1000);  // Eine Sekunde warten, bevor die nächste Messung durchgeführt wird
}
