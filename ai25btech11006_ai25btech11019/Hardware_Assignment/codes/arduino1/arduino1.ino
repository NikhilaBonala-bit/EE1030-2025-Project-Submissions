#include <LiquidCrystal.h>

// LCD pins: RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int analogPin = A0;

// Quadratic coefficients (from least-squares fit)
const float a = 157.349632;
const float b = -891.831915;
const float c = 1236.576660;

// ADC reference and resolution
const float ADC_REF = 5.0;    
const int ADC_RES = 1023;     

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  lcd.print("PT100 Quadratic");
  delay(1500);
  lcd.clear();
}

void loop() {
  int adcValue = analogRead(analogPin);
  float voltage = (adcValue * ADC_REF) / ADC_RES;
  float temperature = a * voltage * voltage + b * voltage + c;

  lcd.setCursor(0, 0);
  lcd.print("V=");
  lcd.print(voltage, 3);
  lcd.print(" V   ");

  lcd.setCursor(0, 1);
  lcd.print("T=");
  lcd.print(temperature, 1);
  lcd.print((char)223);
  lcd.print("C   ");

  Serial.print("ADC=");
  Serial.print(adcValue);
  Serial.print("  V=");
  Serial.print(voltage, 4);
  Serial.print("  T=");
  Serial.print(temperature, 3);
  Serial.println(" C");

  // call helper function from second file
  displayVoltageAverage();

  delay(1000);
}

