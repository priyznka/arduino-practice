void setup()
{
  Serial.begin(9600);
  //pinMode(13, OUTPUT);
}

void loop()
{
  //digitalWrite(13, LOW);
  int x = analogRead(A0);
  x = map(x, 0, 900, 0, 255); 
  x = constrain(x, 0, 255);
  if(x > 200)
  {
    digitalWrite(13, LOW);
    
  }
  else if (x < 200)
  {
    digitalWrite(13, HIGH);
  }
  
  Serial.println(x);
}

