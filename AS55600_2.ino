

#include <Wire.h>
#include <AS5600.h>

AMS_5600 ams5600;

#define NTools 11  //Tools + 1

int angle_in = 0;

void setup() {

  Serial.begin(115200);
  Wire.begin(21, 22);
}

int Angle() {
 
  int in;
  in = map(ams5600.getRawAngle(),0,4095,1,NTools);
  
 if (in == NTools) {
  in = NTools -1;
}



  return in;
}

void loop() {
 
    if (angle_in != Angle()) {
      angle_in = Angle();
      Serial.println(angle_in);
    }
 
}