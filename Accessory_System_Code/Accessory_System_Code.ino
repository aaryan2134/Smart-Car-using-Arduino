// Temperature controlled fan with cleaning bot.
//By Aaryan Arora
#include <ServoTimer2.h>
#include <dht.h>// for the temperature sensor
#include <LiquidCrystal.h>
#define E1 10  // Enable Pin for motor 
#define I1 8  // Control pin 1 for motor 
#define I2 9  // Control pin 2 for motor 
int D = 1000;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // for the lcd
#define DHT11_PIN 7 // signal pin for temperature sensor
dht DHT;
int angle = 700;
ServoTimer2 myservo; // to make myservo object
void setup() {
  myservo.attach(6);
  myservo.write(angle);        // tell servo to go to position in variable 'angle'
  pinMode(E1, OUTPUT);
  pinMode(I1, OUTPUT);
  pinMode(I2, OUTPUT);
  lcd.begin(16, 2); // to start the lcd
}
void loop()
{
// To sense the temperature and display it
  int chk = DHT.read11(DHT11_PIN);
  lcd.setCursor(0, 0);
  lcd.print("Temp:    ");
  lcd.print(DHT.temperature);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(DHT.humidity);
  lcd.print("%");
  delay(1000);
  int temp = DHT.temperature; // to store the temperature in a variable
  for ( angle = 700; angle < 2300; angle += 5) {
    // to move the servo from 0-180
    myservo.write(angle);
    delay(10);        }
  // to control the speed of the fan according to temperature
  if ( temp == 16)    {
analogWrite(E1, 60); 
    digitalWrite(I1, HIGH);
    digitalWrite(I2, LOW);     }
  else if (temp == 17)      {
    analogWrite(E1, 110); 
    digitalWrite(I1, HIGH);
    digitalWrite(I2, LOW);    }
  else if (temp == 18)      {
    analogWrite(E1, 160); 
    digitalWrite(I1, HIGH);
    digitalWrite(I2, LOW);      }
  else if (temp == 19)    {
    analogWrite(E1, 200); 
digitalWrite(I1, HIGH);
    digitalWrite(I2, LOW);    }
  else if (temp > 19)   {
    analogWrite(E1, 255); 
    digitalWrite(I1, HIGH);
    digitalWrite(I2, LOW);  }
  for ( angle = 2300; angle > 700; angle -= 5) { // to rotate the servo from 180-0
    myservo.write(angle);
    delay(10);
  }
  }
