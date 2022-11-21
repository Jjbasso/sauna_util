#include "esphome.h"
#include "Adafruit_EMC2101.h"

class emc2101_sensors : public PollingComponent, public Sensor {
 public:
  Adafruit_EMC2101 emc;
  Sensor *temperature_sensor = new Sensor();
  Sensor *dutyCycle_sensor = new Sensor();
  Sensor *rpm_sensor = new Sensor();

  

   // constructor
  emc2101_sensors() : PollingComponent(15000) {}

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
     float temperature = emc.getInternalTemperature();
     temperature_sensor->publish_state((temperature*1.8)+32);

     float dutyCycle = emc.getDutyCycle();
     dutyCycle_sensor->publish_state(dutyCycle);

     float rpm = emc.getFanRPM();
     rpm_sensor->publish_state(rpm);
  }
  
};
