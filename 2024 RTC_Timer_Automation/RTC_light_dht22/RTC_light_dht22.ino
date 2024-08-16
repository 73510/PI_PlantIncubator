#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2 // DHT22 sensor is connected to pin D2
#define DHTTYPE DHT22 // Define DHT type as DHT22
#define RELAY_PIN 3 // Relay connected to pin D3

DHT dht(DHTPIN, DHTTYPE);
RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2); // Adjust 0x27 based on your LCD's I2C address

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(RELAY_PIN, OUTPUT);
  
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  Serial.println("RTC FOUND");
  /*
    rtc.adjust(DateTime(2024, 3, 1, 10, 55, 0));
  
  Serial.println("RTC is set to March 1, 2024, 10:56 AM");*/

  lcd.init();
  lcd.backlight();
}

void loop() {
  DateTime now = rtc.now();
  float temp = dht.readTemperature(); // Read temperature in Celsius
  float humidity = dht.readHumidity(); // Read humidity
  
  // Display the time, temperature, and humidity on the LCD
  lcd.setCursor(0, 0);
  lcd.print(now.hour());
  lcd.print(":");
  lcd.print(now.minute());
  lcd.print(" ");
  lcd.print(temp);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print(humidity);
  lcd.print("% RH");
  // 기존 14시간 : 9~23시 => 현행 6~13, 5~7 -> 9시간
  // Control the relay based on the time
  //(now.hour() >= 6 && now.hour() < 13) || (now.hour()>=17 && now.hour()<=19)
  if ((now.hour() >= 7 && now.hour() < 20)) {
    Serial.print(now.hour());
    Serial.println(now.minute());
    digitalWrite(RELAY_PIN, HIGH);
  } else {
    digitalWrite(RELAY_PIN, LOW);
  }

  delay(2000); // Wait for 2 seconds before updating again
  
  lcd.clear();
}
