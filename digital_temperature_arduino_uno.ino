/*thermistor parameters:
 * RT0: 10 000 Ω
 * B: 3977 K +- 0.75%
 * T0:  25 C
 * +- 5%
 */

//These values are in the datasheet
#define RT0 10000   // Ω
#define B 3977      // K
//--------------------------------------


#define VCC 5    //Supply voltage
#define R 100000  //R=100KΩ


float getTemp(float VRT) {
  float T0 = 20 + 273.15; //Temperature conversion from Celsius to kelvin              
  VRT = (5.00 / 1023.00) * VRT; //Conversion to voltage
  float VR = VCC - VRT;
  float RT = VRT / (VR / R); //Resistance of RT
  float ln = log(RT / RT0);
  float TX = (1 / ((ln / B) + (1 / T0))); //Temperature from thermistor
  TX = TX - 273.15; //Conversion to Celsius
  return TX;
}

void setup() {
  pinMode(12, OUTPUT);
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop() {
  float val = analogRead(A0);
  float temp = getTemp(val);
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" C");
  
  if (temp > 38.00) {
    digitalWrite(12, HIGH);
    digitalWrite(8, LOW);
  } else {
    digitalWrite(12, LOW);
    digitalWrite(8, HIGH);
  }
  delay(500);
}
