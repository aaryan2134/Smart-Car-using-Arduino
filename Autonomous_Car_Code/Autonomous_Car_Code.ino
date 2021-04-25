// Super Avoider
/*          Arduino Obstacle Avoiding Robot + Not Falling Robot
    with a servo motor and an ultrasonic sensor HC-SR04
              LED and buzzer
  Dev: Aaryan Arora 
*/
//Libraries
#include <Servo.h> 
#include <NewPing.h>
int TurnDelay = 1100;
#define TRIGGER_PIN2  4   // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN2     3  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define TRIGGER_PIN1  8  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN1     12  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonarFRONT(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonarBOTTOM(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
//Constants
const int button = 2;     //Button pin to pin 2
const int buzzer = 7;     //Buzzer pin to pin 7
const int motorA1= 6;     //motor A positive (+) pin to pin 6 (PWM) (from L293 module!)
const int motorA2= 9;         //motor A negative (-) pin to pin 9 (PWM)
const int motorB1=10;     //motor B positive (+) pin to pin 10 (PWM)
const int motorB2=11;     //motor B negative (-) pin to pin 11 (PWM)
Servo myservo;          //Create Servo object to control a servo
//Variables
int distanceBottom; // Variable to store the distance from ground
int distance;         //Variable to store distance from an object
int checkRight;
int checkLeft;
int function=0;         //Variable to store function of robot: '1' running or '0' stoped. By default is stoped
int buttonState=0;            //Variable to store the state of the button. By default '0'
int pos=90;             //Variable to store the servo position. By default 90 degrees - sensor will 'look' forward
int flag=0;           //Useful flag to keep the button state when button is released 
void setup()
{
    myservo.attach(5);      //Servo pin connected to pin 5
    myservo.write(pos);        // tell servo to go to position in variable 'pos' 
  pinMode(button, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  pinMode(motorA1,OUTPUT);
  pinMode(motorA2,OUTPUT);
  pinMode(motorB1,OUTPUT);
  pinMode(motorB2,OUTPUT);
}
int ultraBottom(){
  unsigned int uS = sonarBOTTOM.ping(); // Send ping, get ping time in microseconds (uS).
  delay(50);  // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  return uS / US_ROUNDTRIP_CM;
  }
  int ultraFront(){
      unsigned int uSa = sonarFRONT.ping(); // Send ping, get ping time in microseconds (uS).
       delay(50);  // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  return uSa / US_ROUNDTRIP_CM;
  }
void loop()
{
  //Check button state
  buttonState = digitalRead(button);
  unsigned long currentMillis = millis(); //counting...

  //Change main function (stoped/running) when button is pressed 
    if (buttonState == LOW) {//If button is pressed once...
      delay(500);
      if ( flag == 0){
          function = 1;
          flag=1; //change flag variable
      }
      else if ( flag == 1){  //If button is pressed twice
        function = 0;
        flag=0; //change flag variable again 
      }     }
  if (function == 0){   //If button is unpressed or pressed twice then:
    myservo.write(90);    //set servo 90 degress - sensor will look forward
    stop();         //robot remain stoped
   digitalWrite(buzzer,LOW);     //buzzer off
  }
  else if (function == 1){//If button is pressed then:
    //Read bottom distance
    distanceBottom = ultraBottom(); 
    //Serial.println(distanceBottom);
    if(distanceBottom > 6){
      stop(); //Stop! About to fall! 
      digitalWrite(buzzer,HIGH);
      backward();
      delay(TurnDelay);
     left();
     delay(TurnDelay);
    }
    else {
      digitalWrite(buzzer,LOW);
    //Read distance...
    distance = ultraFront();
    //Check for objects...
    if (distance > 15){
      forward(); //All clear, move forward!
      digitalWrite(buzzer,LOW);
    }
    else if (distance <=15){
      stop(); //Object detected! Stop the robot and check left and right for the better way out!
      digitalWrite(buzzer,HIGH);
      //Start scanning... 
      for(pos = 0; pos < 180; pos += 1){  //goes from 0 degrees to 180 degrees 
                myservo.write(pos);             //tell servo to go to position in variable 'pos' 
                delay(10);                      //waits 10ms for the servo to reach the position 
            } 
            checkLeft = ultraFront();
            for(pos = 180; pos>=0; pos-=1){     //goes from 180 degrees to 0 degrees                           
                myservo.write(pos);             //tell servo to go to position in variable 'pos' 
                delay(10);                      //waits 10ms for the servo to reach the position   
            }
                        checkRight = ultraFront();
                   myservo.write(90);                   // Sensor "look" forward again
            //Finally, take the right decision, turn left or right?
            if (checkLeft < checkRight){
              right();
              delay(TurnDelay); // delay, change value if necessary to make robot turn.            
              }
            else if (checkLeft > checkRight){
              left();
              delay(TurnDelay); // delay, change value if necessary to make robot turn.
            }
            else if (checkLeft <=15 && checkRight <=15){
              backward(); //The road is closed... go back and then left ;)
              delay(TurnDelay);
              left();
            }   } }  }}
// functions
void forward(){
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW); 
}
void backward(){
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}
void right(){
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}
void left(){
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW); 
}

void stop(){
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
}
 
