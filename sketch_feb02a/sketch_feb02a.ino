#include <Servo.h>
Servo myservo;
int pos = 0;

void setup() 
{
  //pinMode(A0, INPUT);
  pinMode(13,OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  //Serial.begin(9600);
  myservo.attach(9);

}

void loop()
{
  for (pos = 0; pos < 180; pos++)
  {
    myservo.write(pos);
    delay(15); 
  }
  for (pos = 180; pos >= 1; pos -=1)
  {
    myservo.write(pos);
    delay(15); 
  }
}

/*void Halfspeed()
//{
//  digitalWrite(9, HIGH);
//  delay(700);
//  digitalWrite(9, LOW);
//  delay(100);
//}
//
//void Slowerspeed()
//{
//  digitalWrite(9, HIGH);
//  delay(100);
//  digitalWrite(9, LOW);
//  delay(700);
//}
//
//void loop() 
//{
//  //Halfspeed();
//  //delay(1000);
//  //Slowerspeed();
//  analogWrite(9, 10);
//   digitalWrite(13, HIGH);
//  delay(200);
//  digitalWrite(13, LOW);
//  delay(200);
//  digitalWrite(13, HIGH);
//  delay(200);
//  digitalWrite(13, LOW);
//  delay(600);
////  for (int i = 0; i < 255; i++)
////  {
////    analogWrite(9, i);
////    delay(100);
////    cout << i << endl;
////  }
//}

//13537
*/

/*  
 * heartbeat code
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);
  delay(200);
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);
  delay(600);
*/

/*
 * //sos signal for one LED
  digitalWrite(13, LOW);
  delay(100);
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);
  digitalWrite(13, HIGH);
  delay(100);
  //long
  digitalWrite(13, LOW);
  delay(1000);
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
  digitalWrite(13, HIGH);
  delay(1000);
  //final shorts
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);
  digitalWrite(13, HIGH);
  delay(100);
*/

/*
 * //code for reading the light sensor
  int sensorLevel=analogRead(A0);
  if (sensorLevel >= 400)
  {
     digitalWrite(13,HIGH);
     delay(100);
     digitalWrite(13,LOW);
     delay(100);
  }
  
  else 
  {
    digitalWrite(13,HIGH);
    delay(500);
    digitalWrite(13,LOW);
    delay(500);
  }
  Serial.print("Sensor Value =");
  Serial.print(sensorLevel);
  Serial.println();
*/
