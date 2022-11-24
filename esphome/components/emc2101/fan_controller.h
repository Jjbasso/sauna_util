#include "esphome.h"
#include "Adafruit_EMC2101.h"
Adafruit_EMC2101 emc;

class emc2101_sensors : public PollingComponent, public Sensor {
 public:

  Sensor *temperature_sensor = new Sensor();
  Sensor *dutyCycle_sensor = new Sensor();
  Sensor *rpm_sensor = new Sensor();

  

   // constructor
  emc2101_sensors() : PollingComponent(1500) {}

  float get_setup_priority() const override { return esphome::setup_priority::BUS; }


  void setup() override {
    // This will be called by App.setup()
    
    emc.begin();
    emc.LUTEnabled(false);
    emc.setFanMinRPM(350);  // Spec sheet Min Speed
    emc.configFanSpinup(true);  // Run fan at 100% duty  until it hits min rpm setting

    emc.enableTachInput(true);
    emc.configPWMClock(false,true);
    emc.setPWMDivisor(0);
    emc.setPWMFrequency(7);
   
  }
  void update() override {
     float temperature = emc.getInternalTemperature();
     temperature_sensor->publish_state((temperature*1.8)+32);

     float rpm = emc.getFanRPM();
     rpm_sensor->publish_state(rpm);
  }
  
};

class emc2101_fan_switch : public Component, public Switch {
 public:
  
  void write_state(bool state) override {

    //this->state = state;
    // This will be called every time the user requests a state change.
 
   if (state) {
      emc.setDutyCycle(19);
    }
  else {
      emc.setDutyCycle(0);
  }
    // Acknowledge new state by publishing it
    publish_state(state);
  }
};
 
 class emc2101_fan_speed : public Component, public FloatOutput {
  public:
   
    void write_state(float state) override {
      
     // state is the amount this output should be on, from 0.0 to 1.0
     // we need to convert it to an integer first
     int value = state * 19;
     emc.setDutyCycle(value);
    }
 };
