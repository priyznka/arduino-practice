void setup() 
{
  pinMode(13, OUTPUT);
}

void loop() 
{
  //50% cycle
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
    delay(500);

  //75% duty cycle, on for 75% of the time
  digitalWrite(13, HIGH);
  delay(750);
  digitalWrite(13, LOW);
  delay(250);
}
