#include <Arduino.h>
#include "PressureSensor.h"

HX711::HX711(String name, int dout, int sck){
    //Safes the HX711 Class with the Pin Config
    this->name = name;
    this->DOUT_PIN=dout;
    this->SCK_PIN=sck;
    this->SCALE_FACTOR = 1.0;
    this->OFFSET= 0.0;
    this->OFFSET_RAW=-80000000;
    Serial.println(this->name+" as HX711 initialized");
}

HX711::~HX711(){
}

void HX711::setup(){
    //Calls the pinMode 
    pinMode(this->DOUT_PIN, INPUT);
    pinMode(this->SCK_PIN, OUTPUT);
    set_U_m_and_U_b();
    Serial.print(this->name+" HX711 finished setup\n");
}

void HX711::set_SCALE_FACTOR(float new_Scale_Factor){
    this->SCALE_FACTOR=new_Scale_Factor;
};

void HX711::set_OFFSET(float new_Offset){
    this->OFFSET=new_Offset;
};


void HX711::read() {
  long value = 0;
  byte data[3] = {0};
  
  while (digitalRead(this->DOUT_PIN));  // Warte, bis DOUT auf LOW geht

  // Lesen der Rohdaten
  for (int i = 0; i < 3; ++i) {
    for (int j = 7; j >= 0; --j) {
      digitalWrite(SCK_PIN, HIGH);
      bitWrite(data[i], j, digitalRead(this->DOUT_PIN)); // Einfügen der gelesenen 3 Bits
      digitalWrite(this->SCK_PIN, LOW);
    }
  }
  
  // HX711 auf standby setzen / in den Leerzustand
  digitalWrite(this->SCK_PIN, HIGH);
  digitalWrite(this->SCK_PIN, LOW);
  
 
  data[2] ^= 0x80;
  value = (static_cast<long>(data[2]) << 16) | (static_cast<long>(data[1]) << 8) | data[0];
  
   this->rawValue=value;
   set_voltage();
   set_pressure_mmHg();
   set_pressure_psi();
   set_pressure_pa();
   //Serial.println(this->name+" finished Reading");
}


void HX711::set_voltage(){
    //4.63V Versorgung
    this->voltage = (this->rawValue/pow(2,24))*(4.91/128); //for mV *1000
    //this->voltage = (this->rawValue * 4.91) / static_cast<float>(0x7FFFFF);
}

void HX711::set_pressure_psi(){
    float pressure_psi;

    //via Point Kalibration
    pressure_psi = (this->voltage - 0.5) * (100.0 / 4.0);
    pressure_psi = (pressure_psi * this->SCALE_FACTOR) + this->OFFSET;
    
    //via Linear Interpolation
    //pressure_psi= (voltage - yIntercept) / slope;

    this->pressure_psi=pressure_psi;
};

void HX711::set_pressure_pa(){
    float pressure_pa;
    pressure_pa = this->pressure_psi * 6.89476;
    pressure_pa = (pressure_pa * this->SCALE_FACTOR) + this->OFFSET;
    this->pressure_pa=pressure_pa;
};

void HX711::set_pressure_mmHg(){
    float pressure_mmHg;
    pressure_mmHg = (this->voltage - 0.5) * (100.0 / 4.0);
    pressure_mmHg = (pressure_mmHg * this->SCALE_FACTOR) + this->OFFSET;
    this->pressure_mmHg = pressure_mmHg;
};


void HX711::set_U_m_and_U_b(){
    this->slope = (this->U_5_8PSI - this->U_1PSI) / (this->P_5_8PSI - this->P_1PSI);
    this->yIntercept = this->U_1PSI - this->slope * this->P_1PSI;
};


void HX711::printTest(){
    //Serial.println(this->name);
    Serial.print("Rohwert: ");

    int num_digits = 1; // Mindestens eine Stelle für den Rohwert

    // Berechnen Sie die Anzahl der Stellen im Rohwert
    long tempValue = this->rawValue;
    if (tempValue < 0) {
        tempValue = -tempValue; // Negative Werte behandeln
    };

    while (tempValue >= 10) {
        tempValue /= 10;
        num_digits++;
    };

    // Füllen Sie die verbleibenden Zeichen mit Leerzeichen auf, um rechtsbündige Ausgabe zu erreichen
    int max_width = 10; // Maximale Breite für die Ausgabe (anpassbar)
    for (int i = num_digits; i < max_width; i++) {
        Serial.print(" ");
    };

    // Ausgabe des Rohwerts
    Serial.print(this->rawValue, DEC);

    //Serial.print(this->rawValue, DEC);
    //Serial.println();
    //Serial.print("\t");
    
    Serial.print(", Spannung: ");
    for ( int i = countDigitsBeforeDecimal(this->voltage) ; i<4;i++){
        Serial.print(" ");
    }
    Serial.print(this->voltage, 4);
    Serial.print(" V");
    
    Serial.print(", Druck (mmHg): ");
    for ( int i = countDigitsBeforeDecimal(this->pressure_mmHg) ; i<4;i++){
        Serial.print(" ");
    }
    Serial.print(this->pressure_mmHg, 2);
    Serial.print(" mmHg");
    /*
    Serial.print(", Druck (PSI): ");
    Serial.print(this->pressure_psi, 2);
    Serial.print(" PSI");

    Serial.print(", Druck (kPa): ");
    Serial.print(this->pressure_pa, 2);
    Serial.println(" kPa");
    */
};

void HX711::printData(){
    Serial.print(this->pressure_pa, 2);
    Serial.print(" kPa");
};


int HX711::countDigitsBeforeDecimal(float value){
    int intValue = (int)value; // Ganzzahliger Teil extrahieren
    int digitCount = 1; // Mindestens eine Ziffer

    while (intValue >= 10) {
        intValue /= 10;
        digitCount++;
    }

    return digitCount;
}