#include "esphome.h"

class MMWaveComponent : public Component, public UARTDevice {
 public:
  MMWaveComponent(UARTComponent *parent) : UARTDevice(parent) {}

  void setup() override {
    // nothing to do here
  }
  void loop() override {
    // Use Arduino API to read data, for example
    String line = readString();
      ESP_LOGD("custom", "Found Response - line is: %s", line.c_str());
    }
    // etc
  }
};