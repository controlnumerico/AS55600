#include <Wire.h>
#include <AS5600.h>
#include <ModbusRTU.h>
#include <SoftwareSerial.h>

SoftwareSerial S(16, 17);// we need one serial port for communicating with RS 485 to TTL adapter

#define REGN 0
#define SLAVE_ID 2

AMS_5600 ams5600;
int ang, Tool, coilValue;
int angle_in = 0;

int Coil_1 = 32;
int Coil_2 = 33;
int Coil_3 = 27;
int Coil_4 = 14;
int Coil_5 = 12;
int Coil_6 = 13;

float AskedTool;

ModbusRTU mb;

void setup() {

  Wire.begin();            //I2C

// Salidas:   D32, D33 D27, D14, D12, D13
pinMode (Coil_1, OUTPUT);
pinMode (Coil_2, OUTPUT);
pinMode (Coil_3, OUTPUT);
pinMode (Coil_4, OUTPUT);
pinMode (Coil_5, OUTPUT);
pinMode (Coil_6, OUTPUT);

  Serial.begin(9600);
  S.begin(9600, SWSERIAL_8N1);
  mb.begin(&S,23); // RE/DE connected to D2
  mb.slave(SLAVE_ID);

mb.addCoil(REGN,0,1);
mb.addHreg(REGN,0,2); //No Registros
mb.addIsts(REGN,0,1);
mb.addIreg(REGN,0,1);

mb.Coil(REGN+0,0);
mb.Hreg(REGN, 01);
mb.Hreg(REGN+1, 0);
mb.Ireg(REGN, 01);


  xTaskCreatePinnedToCore (
    loop2,     // Function to implement the task
    "loop2",   // Name of the task
    1000,      // Stack size in bytes
    NULL,      // Task input parameter
    0,         // Priority of the task
    NULL,      // Task handle.
    0          // Core where the task should run
  );





}


void loop() 
{



angle_in = GetTool();



     
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







}











void loop2 (void* pvParameters) 
          {
          while (1) 
              {

mb.Ireg(REGN, angle_in);
 

//coilValue = mb.Coil(REGN+0);
coilValue = int(mb.Hreg(REGN+1));


AskedTool = mb.Hreg(REGN);

    if (coilValue == 170) {

         
        
      while (AskedTool != angle_in) {
     
      digitalWrite(Coil_5, HIGH);

                                     }


   



     digitalWrite(Coil_5, LOW);
      //mb.Coil(REGN+0,0);    //Resetea Orden de Cambio de Hta

      mb.Hreg(REGN+1,0);

      //===============================
     //===============================
     //===============================

    } else {
      digitalWrite(Coil_5, LOW);
    }
















     //delay(10);
     mb.task();
 

              }
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


