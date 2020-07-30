int sensorPin = 0;
int ledPin = 13;
int sensorValue = 0;
int sensorLevel=analogRead(A0);


void setup() 
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  sensorValue = analogRead(sensorPin);
  digitalWrite(ledPin, HIGH);
  delay(sensorValue);
  digitalWrite(ledPin, LOW);
  delay(sensorValue);

    if (sensorLevel >= 180)
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
}
