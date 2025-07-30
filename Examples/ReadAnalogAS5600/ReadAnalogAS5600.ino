


int portPin = 26; 
int val = 0; 

void setup() {
  Serial.begin(9600);   
}

void loop() {
  val = getTool();  
  Serial.println(val);  
  delay(200);
}
 


int getTool(){
  int potValor;
      //potValor = map(analogRead(portPin), 0, 4095, 1, 10);
      potValor = analogRead(portPin);

  return potValor;
}


