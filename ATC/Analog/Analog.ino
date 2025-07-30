#include <ModbusRTU.h>
#include <SoftwareSerial.h>

SoftwareSerial S(16, 17);// we need one serial port for communicating with RS 485 to TTL adapter

#define POT_VAL_REG 0
#define REGN 0
#define SLAVE_ID 2

const int portPin = 26;


int coilValue = 0;
int AskedTool = 0;

int Coil_1 = 32;
int Coil_2 = 33;
int Coil_3 = 27;
int Coil_4 = 14;
int Coil_5 = 12;
int Coil_6 = 13;

ModbusRTU mb;

void setup() {

// Salidas:   D32, D33 D27, D14, D12, D13
pinMode (Coil_1, OUTPUT);
pinMode (Coil_2, OUTPUT);
pinMode (Coil_3, OUTPUT);
pinMode (Coil_4, OUTPUT);
pinMode (Coil_5, OUTPUT);
pinMode (Coil_6, OUTPUT);

  //Serial.begin(115200);
  S.begin(57600, SWSERIAL_8N1);
  mb.begin(&S,23); // RE/DE connected to D2
  mb.slave(SLAVE_ID);

mb.addCoil(REGN,0,6);
mb.addHreg(REGN,0,5); //No Registros
mb.addIsts(REGN,0,5);
mb.addIreg(REGN,0,5);

mb.Coil(REGN+0,0);
mb.Coil(REGN+1,0);
mb.Coil(REGN+2,0);
mb.Coil(REGN+3,0);
mb.Coil(REGN+4,0);
mb.Coil(REGN+5,0);

  mb.Hreg(REGN, 01);
  mb.Hreg(REGN+1, 02);
  mb.Hreg(REGN+2, 03);
  mb.Hreg(REGN+3, 04);
  mb.Hreg(REGN+4, 05);



mb.Ireg(REGN, 01);

}

void loop() {
  
     
 
//uint16_t Hreg(uint16_t offset);
//bool Ists(uint16_t offset);
//uint16_t Ireg(uint16_t offset);
  

//(Read 6 Coils)



coilValue = int(mb.Hreg(REGN+1));


AskedTool = mb.Hreg(REGN);




 
    if (coilValue == 170) {

         mb.Hreg(REGN+1,0);  //Resetea Valor
         
         


           while (AskedTool != getTool()) {
     
    digitalWrite(Coil_1, HIGH);




                                     }


    } else {
      digitalWrite(Coil_1, LOW);
    }
  





mb.Ireg(REGN, getTool());



     delay(1);
     mb.task();
     
}


// D23  RS485

// Salidas:   D32, D33 D27, D14, D12, D13
// Entradas:  D15, D2, D4, D5, D18, D19

//  DAC2  D25
//  DAC1  D26






int getTool(){
  int potValor;
      potValor = map(analogRead(portPin), 0, 4095, 1, 10);
  return potValor;
}


