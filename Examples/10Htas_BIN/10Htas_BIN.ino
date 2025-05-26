#include <Wire.h>
#include <AS5600.h>

AMS_5600 ams5600;

int ang, Tool;
int angle_in = 0;


int Coil_1 = 32;
int Coil_2 = 33;
int Coil_3 = 27;
int Coil_4 = 14;



void setup()
{
  Serial.begin(19200);
  Wire.begin();         //I2C

pinMode (Coil_1, OUTPUT);
pinMode (Coil_2, OUTPUT);
pinMode (Coil_3, OUTPUT);
pinMode (Coil_4, OUTPUT);
}



float Angle(word newAngle)
{
  /* Raw data reports 0 - 4095 segments, which is 0.087 of a degree */
  float retVal = newAngle * 0.087;
  ang = retVal;
  return ang;
}

int GetTool()
{
int a; 
a = int(Angle(ams5600.getRawAngle()));
a = map(a,0,359,1,11);
 return a;
}


void loop()
{

yield(); 

   

angle_in = GetTool();

 //if (angle_in != GetTool()) {
    //  angle_in = GetTool();
    //  Serial.println(angle_in);

     
     switch (angle_in) {
      case 1:
             digitalWrite(Coil_1, HIGH);
             digitalWrite(Coil_2, LOW);
             digitalWrite(Coil_3, LOW);
             digitalWrite(Coil_4, LOW);
      break;
      case 2:
             digitalWrite(Coil_1, LOW);
             digitalWrite(Coil_2, HIGH);
             digitalWrite(Coil_3, LOW);
             digitalWrite(Coil_4, LOW);
      break;
      case 3:
             digitalWrite(Coil_1, HIGH);
             digitalWrite(Coil_2, HIGH);
             digitalWrite(Coil_3, LOW);
             digitalWrite(Coil_4, LOW);
      break;
      case 4:
             digitalWrite(Coil_1, LOW);
             digitalWrite(Coil_2, LOW);
             digitalWrite(Coil_3, HIGH);
             digitalWrite(Coil_4, LOW);
      break;
      case 5:
             digitalWrite(Coil_1, HIGH);
             digitalWrite(Coil_2, LOW);
             digitalWrite(Coil_3, HIGH);
             digitalWrite(Coil_4, LOW);
      break;
      case 6:
             digitalWrite(Coil_1, LOW);
             digitalWrite(Coil_2, HIGH);
             digitalWrite(Coil_3, HIGH);
             digitalWrite(Coil_4, LOW);
      break;
      case 7:
             digitalWrite(Coil_1, HIGH);
             digitalWrite(Coil_2, HIGH);
             digitalWrite(Coil_3, HIGH);
             digitalWrite(Coil_4, LOW);
      break;
      case 8:
             digitalWrite(Coil_1, LOW);
             digitalWrite(Coil_2, LOW);
             digitalWrite(Coil_3, LOW);
             digitalWrite(Coil_4, HIGH);
      break;
      case 9:
             digitalWrite(Coil_1, HIGH);
             digitalWrite(Coil_2, LOW);
             digitalWrite(Coil_3, LOW);
             digitalWrite(Coil_4, HIGH);
      break;
      case 10:
             digitalWrite(Coil_1, LOW);
             digitalWrite(Coil_2, HIGH);
             digitalWrite(Coil_3, LOW);
             digitalWrite(Coil_4, HIGH);
      break;


      default:
        // if nothing else matches, do the default
        // default is optional
        break;
    }





   // }


//Tool = GetTool();
//Serial.println(Tool);

 




}
