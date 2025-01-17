#ifndef Multi_PressureSensor_H 
#define Multi_PressureSensor_H 

#include "Arduino.h"
#include "PressureSensor.h"


const uint8_t Anz_HX711 = 3; //How much HX711 Sensors you would include in multi_HX711

class multi_HX711
{
    private:
        String Name;
        HX711* HX711s[Anz_HX711];//Array of HX711 Pointers
        bool is_empty;//Simple Flag to indicate if multi_HX711 is empty
        int Shared_SCK_PIN;// SCK pin for all HX711 devices
        int gain;
        byte GAIN;
    public:
        multi_HX711(String name,int Shared_SCK_PIN, int gain = 128);
        virtual ~multi_HX711();
        void setup_overwrite(); 
        void read();
        void add_HX711(HX711* hx711Instance);
        void set_gain(byte gain);
        void print_multi_HX711();   
        void print_all_HX711(); 
        void printTest();   
};
#endif