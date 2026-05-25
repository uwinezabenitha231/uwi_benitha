#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
int smokePin = 2;
int tempPin = A0;
int buzzer = 8;
int relay = 7;

float temperature;

void setup() {

  pinMode(smokePin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(relay, OUTPUT);

  digitalWrite(buzzer, LOW);
  digitalWrite(relay, LOW);

  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Fire Alarm Sys");
  delay(2000);
  lcd.clear();
}

void loop() {
  int smoke = digitalRead(smokePin);
  int value = analogRead(tempPin);

  float voltage = value * (5.0 / 1023.0);

  temperature = voltage * 100;
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");
  lcd.setCursor(0,0);
  lcd.print("Temp:");
  lcd.print(temperature);
  lcd.print((char)223);
  lcd.print("C ");

  if(smoke == LOW || temperature > 40){

    lcd.setCursor(0,1);
    lcd.print("FIRE DETECTED ");

    Serial.println("Fire Detected!");

    digitalWrite(buzzer, HIGH);
    digitalWrite(relay, HIGH);
  }

  else{

    lcd.setCursor(0,1);
    lcd.print("System Normal ");

    digitalWrite(buzzer, LOW);

    digitalWrite(relay, LOW);
  }

  delay(1000);
}
