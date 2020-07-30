int red = 9;
int green = 10;
int blue = 11;

void setup() 
{
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{

//  //purple
//  digitalWrite(red, HIGH);
//  digitalWrite(blue, HIGH);
//  delay(1000);
//  digitalWrite(red, LOW);
//  digitalWrite(blue, LOW);
//
//  //yellow
//  digitalWrite(red, HIGH);
//  digitalWrite(green, HIGH);
//  delay(1000);
//  digitalWrite(red, LOW);
//  digitalWrite(green, LOW);

  int x= analogRead(A2);
  Serial.println(x);

     // x = constrain(0, 900, 255);
    //x = map(0, 0, 255, 0, 255);

  if(x < 500)
  {
    digitalWrite(blue, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
//    delay(100);
//    digitalWrite(red, LOW);
  }

  if (x > 500 && x < 1000)
  {
    digitalWrite(green, LOW);
    digitalWrite(red, LOW);
    digitalWrite(blue, HIGH);
//    delay(100);
//    digitalWrite(blue, LOW);
  }

  if (x > 1000)
  {
    digitalWrite(red, LOW);
    digitalWrite(blue, LOW);
    digitalWrite(green, HIGH);
//    delay(100);
//    digitalWrite(green, LOW);
  }
}
