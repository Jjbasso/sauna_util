// Adafruit EMC2101 for ESP Home External Component
#include <Wire.h>
#include <Adafruit_EMC2101.h>

Adafruit_EMC2101  emc2101;
void setup(void) {
  Serial.begin(115200);
  while (!Serial) delay(10);  

  // Try to initialize!
  if (!emc2101.begin()) {
    Serial.println("Failed to find EMC2101 chip");
    while (1) { delay(10); }
  }
  Serial.println("EMC2101 Found!");
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
  
  Serial.print("Internal Temperature: ");
  Serial.print((emc2101.getInternalTemperature()*1.8)+32);Serial.println(" degrees F");
  
  Serial.print("External Temperature: ");
  Serial.print((emc2101.getExternalTemperature()*1.8)+32);Serial.println(" degrees F");

  Serial.println("Just Increment from 1 to 100 with 2 sec delay between each step");
  emc2101.LUTEnabled(true);
  int i;
  for (i = 0; i < 100; ++i) {
    emc2101.setDutyCycle(i);
    delay(2000);
    Serial.print("Duty ");Serial.print(i);Serial.print("||Fan RPM:: "); Serial.println(emc2101.getFanRPM());
  }
  
  Serial.println("Change to Internal Lookup table to run fan");
  emc2101.LUTEnabled(true);
  emc2101.enableForcedTemperature(true);

  Serial.println("Force Temp override to see how fan RPM changes with 2 sec delay between steps of 88 to 125");
  int i;
  for (i = 88; i < 128; ++i) {
    emc2101.setDutyCycle(i);
    delay(2000);
    emc2101.setForcedTemperature((i-32)*.5556);
    Serial.print("Temp ");Serial.print(i);Serial.print("||Fan RPM "); Serial.println(emc2101.getFanRPM());
  }
}

void loop() {
}
