#ifndef PressureSensor_H  
#define PressureSensor_H

#include "Arduino.h"


/*
Achtung Sensoren müssen noch kalibriert werden!!!

Druck (Einheit) = (Rohwert - Rohwert_min) * (Druck_max - Druck_min) / (Rohwert_max - Rohwert_min) + Druck_min
Rohwert ist der vom HX711 ausgelesene Rohwert.
Rohwert_min ist der Rohwert bei deinem Mindestdruck.
Rohwert_max ist der Rohwert bei deinem Höchstdruck.
Druck_min ist der minimale Druckwert im gewünschten Einheitensystem (PSI oder kPa).
Druck_max ist der maximale Druckwert im gewünschten Einheitensystem (PSI oder kPa).



*/
class HX711
{
    private:
        String name;        // Name of Sensor
        int DOUT_PIN;       // DOUT pin am Arduino
        int SCK_PIN;        // SCK pin am Arduino
        float SCALE_FACTOR; // Skalierungsfaktor zur Umrechnung in Druckwerte
        float OFFSET;       // Offset-Korrektur (falls nötig)

        long rawValue;
        long OFFSET_RAW;
        float voltage;
        float pressure_psi;
        float pressure_pa;
        float pressure_mmHg;

        //Referenzpunkte für lineare Interpolation
        float U_1PSI = 0.03;    //30mV
        float U_5_8PSI = 0.075; //75mV
        float P_1PSI = 1.0;
        float P_5_8PSI = 5.8;

        float slope;
        float yIntercept;

    public:
        HX711(String name, int dout, int sck);
        virtual ~HX711();

        void setup();
        void read();

        void set_SCALE_FACTOR(float new_Scale_Factor);
        void set_OFFSET(float new_Offset);

        //Interne Funktionen
        void set_U_m_and_U_b();
        void set_voltage();
        void set_pressure_psi();
        void set_pressure_pa();
        void set_pressure_mmHg();

        int countDigitsBeforeDecimal(float value);

        void printTest();
        void printData();

};

/*
const int analogPin = A0;
const int inputResolution = 1023;
const int maxVoltIn = 5;

//Used if not made in Classes
extern int SensorValue;
extern float voltageSensor;


void readSensor();
void getVoltageSensor();

float getPressure();

*/

#endif