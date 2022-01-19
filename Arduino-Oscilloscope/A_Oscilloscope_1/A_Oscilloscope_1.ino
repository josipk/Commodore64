/*
Arduino Oscilloscope  
Josip Retro Bits
*/

void setup(){
  Serial.begin(115200);
  
  //following three lines speed up ADC to ~200 kHz
  bitClear(ADCSRA,ADPS0);
  bitSet(ADCSRA,ADPS1);
  bitClear(ADCSRA,ADPS2);  

}

void loop(){
  while(1) {
    Serial.print("0,5,");
    Serial.println(analogRead(A4) * 5.0/1023);
  }
}

