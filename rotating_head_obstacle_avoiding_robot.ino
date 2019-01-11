#include <Servo.h>                                  //includes the servo library
#include <NewPing.h>
int pingPin = 7; 
int motorPin1 = 5;
int motorPin2 = 4;
int motorPin3 = 2;
int motorPin4 = 3;
int servoPin = 11;
int object = 10;
int maxdist = 100;
long cm,inches,duration;
int leftdist = 0;
int rightdist = 0;
void halt();
void backward();
void lookleft();
void lookright();
void turnleft();
void turnright();
long readsensor();
void findroute();
Servo myservo;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(11);
 pinMode(motorPin1,OUTPUT);
 pinMode(motorPin2,OUTPUT);
 pinMode(motorPin3,OUTPUT);
 pinMode(motorPin4,OUTPUT);
 myservo.write(90);
 delay(500);
  }

void loop() {
  // put your main code here, to run repeatedly:
  
readsensor();
if((cm>object)&&(cm<maxdist))
 {
  lookleft();
  lookright(); 
  findroute();
 }
 else
 forward();
 }
long readsensor()
{   
 pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  delay(100);
}

long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are 73.746
  // microseconds per inch (i.e. sound travels at 1130 feet per second).
  // This gives the distance travelled by the ping, outbound and return,
  // so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}
void lookleft() {
 myservo.write(150);
 delay(700);                                //wait for the servo to get there
 leftdist = digitalRead(pingPin);
 myservo.write(90);
 delay(700);                                 //wait for the servo to get there
 return;
}
void lookright () {
 myservo.write(30);
 delay(700);                           //wait for the servo to get there
 rightdist = digitalRead(pingPin);
 myservo.write(90);                                  
 delay(700);                        //wait for the servo to get there
 return;
}
void forward() {                         
  digitalWrite(motorPin1,HIGH );
  digitalWrite(motorPin2,LOW);
  digitalWrite(motorPin3,HIGH);
  digitalWrite(motorPin4,LOW);
  delay(1000);
  return;
}
void halt () {
 digitalWrite(motorPin1,LOW);
 digitalWrite(motorPin2,LOW);
 digitalWrite(motorPin3,LOW);
 digitalWrite(motorPin4,LOW);
 delay(700);//wait after stopping
 return;
}
void turnleft () {
 digitalWrite(motorPin1,HIGH);       //use the combination which works for you
 digitalWrite(motorPin2,LOW);      //right motor rotates forward and left motor backward
 digitalWrite(motorPin3,LOW);
 digitalWrite(motorPin4,HIGH);
 delay(500);
 return;         
}
void turnright () {
 digitalWrite(motorPin1,LOW);       //use the combination which works for you
 digitalWrite(motorPin2,HIGH);    //left motor rotates forward and right motor backward
 digitalWrite(motorPin3,HIGH);
 digitalWrite(motorPin4,LOW);
 delay(500);                    
 return;
}
void findroute()
{
  if(leftdist<rightdist)
  {
  turnright();
  forward();
  }
  else if(leftdist>rightdist)
  {
    turnleft();
    forward();
  }
  
  else
  halt();
}
