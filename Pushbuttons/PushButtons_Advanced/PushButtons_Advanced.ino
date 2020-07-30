int ledPin = 13;
int inputPin1 = 3;
int inputPin2 = 2;

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(inputPin1, INPUT);
  pinMode(inputPin2, INPUT);
}

void loop()
{  
  if(digitalRead(inputPin1) == LOW)
  {
    digitalWrite(ledPin, LOW);
  }
  else if(digitalRead(inputPin2) == LOW)
  {
    digitalWrite(ledPin, HIGH);
  }
}

