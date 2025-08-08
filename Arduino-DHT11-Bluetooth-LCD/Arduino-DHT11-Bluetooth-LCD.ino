#include <dht.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

#define dht_apin A0 // Analog Pin sensor is connected to

SoftwareSerial BTSerial(10, 11);  //Rx,Tx Of Arduino

dht DHT;

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Start the serial communication
  Serial.begin(9600);
  BTSerial.begin(9600);
  delay(500); // Delay to let the system boot
  Serial.println("DHT11 Humidity & Temperature Sensor\n\n");
  delay(1000); // Wait before accessing the sensor

  // Initialize the LCD
  lcd.init(); // Initialize the LCD
  lcd.backlight(); // Turn on the backlight
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
  delay(2000); // Wait to show the initializing message
}

void loop() {
  // Read data from the DHT sensor
  DHT.read11(dht_apin);

  // Print data to the serial monitor
  Serial.print("Current humidity = ");
  Serial.print(DHT.humidity);
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(DHT.temperature);
  Serial.println("C");

  unsigned long time = millis();  
  BTSerial.write("At time:");
  BTSerial.println(time);
   // Write data to bluetooth
  BTSerial.print("Current humidity = ");
  BTSerial.print(DHT.humidity);
  BTSerial.println("%  ");
  BTSerial.write("temperature = ");
  BTSerial.print(DHT.temperature);
  BTSerial.println("C");


  // Clear the LCD and set the cursor
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Humidity: ");
  lcd.print(DHT.humidity);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(DHT.temperature);
  lcd.print("C");

  // Wait 5 seconds before accessing the sensor again
  delay(5000);
}
