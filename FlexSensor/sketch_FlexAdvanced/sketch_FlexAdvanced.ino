// Controlling a servo position using a potentiometer (variable resistor) 

#include <Servo.h> 

Servo myservo;  // create servo object to control a servo 

int potpin = 0;  // analog pin used to connect the potentiometer
int val;  

void setup() 
{ 
  Serial.begin(9600);
  myservo.attach(9);  
} 

void loop() 

{ 
  val = analogRead(potpin);            
  Serial.println(val);  
  val = map(val, 30, 200, 0, 179);      
  myservo.write(val);                 
  delay(15);                           
} 

