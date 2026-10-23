#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
 
LiquidCrystal_I2C lcd(0x27, 16, 2);  // LCD address 
 
#define PIEZO_PIN A0 
#define LED_PIN 2 
 
int stepCount = 0; 
float voltage = 0; 
int threshold = 50;   // Adjust according to your circuit 
bool stepDetected = false; 
 
void setup() { 
  pinMode(LED_PIN, OUTPUT); 
  digitalWrite(LED_PIN, LOW); 
 
  lcd.init(); 
  lcd.backlight(); 
 
  lcd.setCursor(0, 0); 
  lcd.print("FOOTSTEP POWER"); 
  lcd.setCursor(0, 1); 
  lcd.print("GENERATION"); 
  delay(2000); 
  lcd.clear(); 
 
  Serial.begin(9600); 
} 
 
void loop() { 
  long sensorValue = 0; 
 
  // Average 10 readings for stable voltage 
  for (int i = 0; i < 10; i++) { 
    sensorValue += analogRead(PIEZO_PIN); 
    delay(2); 
  } 
 
  sensorValue /= 10; 
 
  // Convert analog reading to voltage 
  voltage = sensorValue * (5.0 / 1023.0); 
 

  // Step detection 
  if (sensorValue > threshold && !stepDetected) { 
    stepCount++; 
    stepDetected = true; 
    digitalWrite(LED_PIN, HIGH);  // LED ON when step detected 
  } 
 
  if (sensorValue < threshold / 2) { 
    stepDetected = false; 
    digitalWrite(LED_PIN, LOW);   // LED OFF 
  } 
 
  // LCD Display 
  lcd.setCursor(0, 0); 
  lcd.print("STEP COUNT: "); 
  lcd.print(stepCount); 
  lcd.print("   "); 
 
  lcd.setCursor(0, 1); 
  lcd.print("VOLTAGE: "); 
  lcd.print(voltage, 2); 
  lcd.print("V   "); 
 
  // Serial Monitor 
  Serial.print("Sensor: "); 
  Serial.print(sensorValue); 
  Serial.print(" Voltage: "); 
  Serial.print(voltage); 
  Serial.print(" Steps: "); 
  Serial.println(stepCount); 
 
  delay(100); 
} 
```0