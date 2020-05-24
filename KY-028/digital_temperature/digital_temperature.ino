/**
 * thermistor parameters:
 * RT0: 10 000 Ω
 * B: 3977 K +- 0.75%
 * T0:  25 C
 * +- 5%
 */
#define RT0 10000   // Ω
#define B 3977      // K
#define VCC 5    //Supply voltage
#define R 100000  //R=100KΩ
#define CALIBRATION 25


float getTemp(float VRT) {
  float T0 = CALIBRATION + 273.15; //Temperature conversion from Celsius to kelvin              
  VRT = (5.00 / 1023.00) * VRT; //Conversion to voltage
  float VR = VCC - VRT;
  float RT = VRT / (VR / R); //Resistance of RT
  float ln = log(RT / RT0);
  float TX = (1 / ((ln / B) + (1 / T0))); //Temperature from thermistor
  TX = TX - 273.15; //Conversion to Celsius
  return TX;
}

/* 
 *  Pins
 */
const int pin12 = 12;
const int pin8 = 8;
const int pin2 = 2;
const int pinA0 = A0;
  
void setup() {
  pinMode(pin12, OUTPUT);
  pinMode(pin8, OUTPUT);
  pinMode(pin2, INPUT);
  pinMode(pinA0, INPUT);
  Serial.begin(9600);
}

void loop() {
  float val = analogRead(pinA0);
  float digitalVal = digitalRead(pin2);
  float temp = getTemp(val);
  
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" C");

  Serial.print("digital read: ");
  Serial.print(digitalVal);
  Serial.println(" ");
  
  if (temp > 32.00) {
    digitalWrite(12, HIGH);
    digitalWrite(8, LOW);
  } else {
    digitalWrite(12, LOW);
    digitalWrite(8, HIGH);
  }
  
  delay(500);
}
