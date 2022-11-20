// Basic demo for readings from Adafruit EMC2101
#include <Wire.h>
#include <Adafruit_EMC2101.h>
//Test Process

Adafruit_EMC2101  emc2101;
void setup(void) {
  Serial.begin(115200);
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit EMC2101 test!");

  // Try to initialize!
  if (!emc2101.begin()) {
    Serial.println("Failed to find EMC2101 chip");
    while (1) { delay(10); }
  }
  Serial.println("EMC2101 Found!");

   emc2101.setLUT(0, (90-32)*.5556, 40);
   emc2101.setLUT(1, (100-32)*.5556, 80);   
   emc2101.setLUT(2, (110-32)*.5556, 90);
   emc2101.setLUT(3, (120-32)*.5556, 100);
   
  emc2101.setFanMinRPM(1000);
  emc2101.configFanSpinup(true);
  emc2101.invertFanSpeed(false);
  delay(5000);
  Serial.print("Fan RPM:: "); Serial.println(emc2101.getFanRPM());
  delay(20000);
}

void loop() {
  emc2101.LUTEnabled(false);
  delay(5000);

  Serial.print("Internal Temperature: ");
  Serial.print((emc2101.getInternalTemperature()*1.8)+32);Serial.println(" degrees F");

  emc2101.setDutyCycle(0);
  Serial.println("Fan duty cycle: 0");
  delay(5000);
  Serial.print("Fan RPM:: "); Serial.println(emc2101.getFanRPM());

  emc2101.setDutyCycle(40);
  Serial.println("Fan duty cycle: 40");
  delay(5000);
  Serial.print("Fan RPM:: "); Serial.println(emc2101.getFanRPM());

  emc2101.setDutyCycle(50);
  Serial.println("Fan duty cycle: 50");
  delay(5000);
  Serial.print("Fan RPM:: "); Serial.println(emc2101.getFanRPM());

  emc2101.setDutyCycle(60);
  Serial.println("Fan duty cycle: 60");
  delay(5000);
  Serial.print("Fan RPM:: "); Serial.println(emc2101.getFanRPM());

  emc2101.setDutyCycle(70);
  Serial.println("Fan duty cycle: 70");
  delay(5000);
  Serial.print("Fan RPM:: "); Serial.println(emc2101.getFanRPM());

  emc2101.setDutyCycle(80);
  Serial.println("Fan duty cycle: 80");
  delay(5000);
  Serial.print("Fan RPM:: "); Serial.println(emc2101.getFanRPM());

  emc2101.setDutyCycle(90);
  Serial.println("Fan duty cycle: 90");
  delay(5000);
  Serial.print("Fan RPM:: "); Serial.println(emc2101.getFanRPM());

  emc2101.setDutyCycle(100);
  Serial.println("Fan duty cycle: 100");
  delay(5000);
  Serial.print("Fan RPM:: "); Serial.println(emc2101.getFanRPM());

  
  Serial.println("Change to Internal Lookup table to run fan");
  emc2101.LUTEnabled(true);
  emc2101.setLUTHysteresis(5); // 5 degree C fudge factor
  emc2101.enableForcedTemperature(true);
  delay(5000);
  
  Serial.print("Forcing to 75 degrees F: ");
  emc2101.setForcedTemperature((75-32)*.5556);
  Serial.print("Forced Temperature: ");Serial.print((emc2101.getForcedTemperature()*1.8)+32);Serial.println(" degrees F");
  delay(5000);
 
  Serial.print("Forcing to 90 degrees F: ");
  emc2101.setForcedTemperature((90-32)*.5556);
  Serial.print("Forced Temperature: ");Serial.print((emc2101.getForcedTemperature()*1.8)+32);Serial.println(" degrees F");
  delay(5000);

  Serial.print("Forcing to 100 degrees F: ");
  emc2101.setForcedTemperature((100-32)*.5556);
  Serial.print("Forced Temperature: ");Serial.print((emc2101.getForcedTemperature()*1.8)+32);Serial.println(" degrees F");
  delay(5000);
  
  Serial.print("Forcing to 110 degrees F: ");
  emc2101.setForcedTemperature((110-32)*.5556);
  Serial.print("Forced Temperature: ");Serial.print((emc2101.getForcedTemperature()*1.8)+32);Serial.println(" degrees F");
  delay(5000);

  Serial.print("Forcing to 120 degrees F: ");
  emc2101.setForcedTemperature((120-32)*.5556);
  Serial.print("Forced Temperature: ");Serial.print((emc2101.getForcedTemperature()*1.8)+32);Serial.println(" degrees F");
  delay(5000);

  
}
