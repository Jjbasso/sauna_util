#include "esphome.h"
#include "Adafruit_EMC2101.h"
Adafruit_EMC2101 emc;

class emc2101_sensors : public PollingComponent, public Sensor {
 public:

  Sensor *temperature_sensor = new Sensor();
  Sensor *rpm_sensor = new Sensor();

  // constructor
  emc2101_sensors() : PollingComponent(5000) {}

  float get_setup_priority() const override { return esphome::setup_priority::BUS; }


  void setup() override {
   
   
   emc.begin();
    emc.enableTachInput(true);
    emc.configPWMClock(false,true);
    emc.setPWMDivisor(0);
    emc.setPWMFrequency(7); // sets the clock speed to 25k (see EMC2101 Spect sheet) which is what pc fans need
   
  }
  void update() override {
     float temperature = emc.getInternalTemperature();
     temperature_sensor->publish_state((temperature*1.8)+32);

     float rpm = emc.getFanRPM();
     rpm_sensor->publish_state(rpm);
  }
  
};

class emc2101_fan_speed : public Component, public FloatOutput {
 public:
   
    void write_state(float state) override {
       // state is the amount this output should be on, from 0.0 to 1.0
       // We multiple by 19 and not 100 due to calc error or resolution problem
     int value = state * 19;
     ESP_LOGD("custom", "Setting Dutycyle to: %f", state.state);
     
     
     // if we are not manually setting fan speed then put fan in auto enable mode
     // based on onboard temp sensor and lookup table
     if (value > 0) {
        ESP_LOGD("custom", "Enable Manaul Over Ride of Fan control");
        emc.LUTEnabled(false);
        emc.enableForcedTemperature(false);
        emc.setDutyCycle(value);
     }
     else {
       // This will be called by App.setup()
       // LUT for auto fan mode
       ESP_LOGD("custom", "Setup LUT and enable");
       emc.setLUT(0, (32-32)*.5556, 0);
       emc.setLUT(1, (95-32)*.5556, 13);
       emc.setLUT(2, (100-32)*.5556, 14);
       emc.setLUT(3, (105-32)*.5556, 15);
       emc.setLUT(4, (110-32)*.5556, 16);
       emc.setLUT(5, (115-32)*.5556, 17);
       emc.setLUT(6, (120-32)*.5556, 18);
       emc.setLUT(7, (125-32)*.5556, 19);
       emc.LUTEnabled(true);
       // use for testing loookup table  
       emc.enableForcedTemperature(true);
       emc.setForcedTemperature((126-32)*.5556);
     }
    }
 };
