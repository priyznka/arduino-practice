//has one pushbutton that turns the LED on, and another that turns it off
#include <SoftwareSerial.h>

int inputPin = 2;
int inputPin4 = 4;
int inputPin5 = 5;
int val = 0;
int val2 = 0;
int val3 = 0;


void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(inputPin, INPUT);
  pinMode(inputPin4, INPUT);
  pinMode(inputPin5, INPUT);
}

void loop() 
{
  val = digitalRead(inputPin);
  val2 = digitalRead(inputPin4);
  val3 = digitalRead(inputPin5);
  if (val == HIGH or val2 == HIGH or val3 == HIGH)
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
  else
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }

}
