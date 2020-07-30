void setup() 
{
  pinMode(9, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);

}

void loop() 
{
  digitalWrite(9, HIGH);
  delay(1000);
  digitalWrite(9, LOW);
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  digitalWrite(11, HIGH);
  delay(1000);
  digitalWrite(11, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(9, LOW);
  digitalWrite(13, LOW);

  digitalWrite(11, HIGH);
  digitalWrite(9, HIGH);
  delay(1000);
  digitalWrite(11, LOW);
  digitalWrite(9, LOW);
  
}
