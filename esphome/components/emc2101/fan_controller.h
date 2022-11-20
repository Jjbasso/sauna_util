#include "esphome.h"
#include "Adafruit_EMC2101.h"

class MyCustomSensor : public PollingComponent, public Sensor {
 public:
  Adafruit_EMC2101 emc;

   // constructor
  MyCustomSensor() : PollingComponent(15000) {}

  float get_setup_priority() const override { return esphome::setup_priority::BUS; }


  void setup() override {
    // This will be called by App.setup()
    
    emc.begin();
    emc.setFanMinRPM(1000);
    emc.configFanSpinup(true);
    emc.invertFanSpeed(false);
    emc.LUTEnabled(false);
  }
  void update() override {
    // This will be called every "update_interval" milliseconds.
     int intTemp = emc.getInternalTemperature();
     publish_state((intTemp*1.8)+32);
  }
};
