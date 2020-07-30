  int data = 2; //pins for serial communication w/shift register
  int clock = 3;
  int latch = 4;

  int ledState = 0;
  const int ON = HIGH;
  const int OFF = LOW;
  int randomNum = random(1,7);


void setup() 
{
  pinMode(data,OUTPUT);
  pinMode(clock,OUTPUT);
  pinMode(latch,OUTPUT);

}

void updateLEDs(int value)
{
  digitalWrite(latch,LOW);
  shiftOut(data, clock, MSBFIRST, value);
  digitalWrite(latch, HIGH);
}

/*
void updateLEDsLong(int value)
{
  digitalWrite(latch, LOW);
  for (int i = 0; i < 8; i++)
  {
    int bit = value & B10000000;
    value = value << 1;
    if (bit == 128)
    {
      digitalWrite(data, HIGH);
    }
    else
    {
      digitalWrite(data, LOW);
    }
    digitalWrite(clock, HIGH);
    delay(1);
    digitalWrite(clock, LOW);
  }
  digitalWrite(latch, HIGH);
}
*/
void loop() 
{
  int dtime = 100;
  for (int i = 0; i < 256; i++)
  {
    updateLEDs(i);
    delay(100*randomNum);
  }
}

