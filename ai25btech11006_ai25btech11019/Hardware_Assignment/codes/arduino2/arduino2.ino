// helper function to compute average voltage and display
void displayVoltageAverage() {
  const int samplesPerPoint = 100;
  float sum = 0;

  for (int i = 0; i < samplesPerPoint; i++) {
    int raw = analogRead(A0);
    float voltage = raw * (5.0 / 1023.0);
    sum += voltage;
    delay(10);
  }

  float avgVoltage = sum / samplesPerPoint;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Avg Voltage:");
  lcd.setCursor(0, 1);
  lcd.print(avgVoltage, 3);
  lcd.print(" V");

  delay(2000);
}

