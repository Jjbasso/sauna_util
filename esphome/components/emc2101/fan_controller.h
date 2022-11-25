#include "esphome.h"
#include "Adafruit_EMC2101.h"
Adafruit_EMC2101 emc2101;

class emc2101_sensors : public PollingComponent, public Sensor {
 public:

  Sensor *external_temperature_sensor = new Sensor();
  Sensor *internal_temperature_sensor = new Sensor();
  Sensor *rpm_sensor = new Sensor();

  // constructor
  emc2101_sensors() : PollingComponent(5000) {}

  float get_setup_priority() const override { return esphome::setup_priority::BUS; }


  void setup() override {
   
   
    emc2101.begin();
    emc2101.enableTachInput(true);
    emc2101.configPWMClock(false,true);
    emc2101.setPWMDivisor(0);
    emc2101.setPWMFrequency(7); // sets the clock speed to 25k (see EMC2101 Spect sheet) which is what pc fans need
   
    emc2101.setLUT(0, (32-32)*.5556, 0);
    emc2101.setLUT(1, (95-32)*.5556, 13);
    emc2101.setLUT(2, (100-32)*.5556, 14);
    emc2101.setLUT(3, (105-32)*.5556, 15);
    emc2101.setLUT(4, (110-32)*.5556, 16);
    emc2101.setLUT(5, (115-32)*.5556, 17);
    emc2101.setLUT(6, (120-32)*.5556, 18);
    emc2101.setLUT(7, (125-32)*.5556, 19);
  }

 
  void update() override {
    float internal_temperature = emc2101.getInternalTemperature();
    internal_temperature_sensor->publish_state((internal_temperature*1.8)+32);

    float external_temperature = emc2101.getExternalTemperature();
    external_temperature_sensor->publish_state((external_temperature*1.8)+32);
   
    float rpm = emc2101.getFanRPM();
    rpm_sensor->publish_state(rpm);
  }
  
};

class emc2101_fan_speed : public Component, public FloatOutput {
 public:
   
    void write_state(float state) override {
       // state is the amount this output should be on, from 0.0 to 1.0
       // We multiple by 19 and not 100 due to calc error or resolution problem
     int value = state * 19;
     ESP_LOGD("custom", "Setting Dutycyle to: %i", value);
     
     
     // if we are not manually setting fan speed then put fan in auto mode
     // based on onboard temp sensor and lookup table given above
     if (value > 0) {
        ESP_LOGD("custom", "Enable Manaul Over Ride of Fan control");
        emc2101.LUTEnabled(false);
        emc2101.enableForcedTemperature(false);
        emc2101.setDutyCycle(value);
     }
     else {
       // LUT for auto fan mode
       ESP_LOGD("custom", "Setup LUT and enable Auto Mode");
       emc2101.LUTEnabled(true);
       // use for testing loookup table  
       //emc2101.enableForcedTemperature(true);
       //emc2101.setForcedTemperature((102-32)*.5556);
     }
    }
 };
