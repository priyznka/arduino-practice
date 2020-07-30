void setup() 
{
//  pinMode(9, OUTPUT);
//  pinMode(13, OUTPUT);
//  pinMode(11, OUTPUT);
  Serial.begin(9600);

}

void loop() 
{
  int sensor = analogRead(A0);
  int red = constrain(map(sensor, 0, 512, 255, 0), 0, 255);
  int green = constrain(map(sensor, 0, 512, 0, 255), 0, 255);
  int blue = constrain(map(sensor, 512, 1025, 0, 255), 0, 255);

  if (sensor > 200 && sensor < 500)
  {
      analogWrite(9, red);
      delay(500);
      analogWrite(9, LOW);
  }
  
  if (sensor < 200)
  {
    analogWrite(11, green); 
    delay(500);     
    analogWrite(11, LOW);
    
  }
  
  if (sensor > 500)
  {
    analogWrite(13, blue);
    delay(500);
    analogWrite(13, LOW);

  }
  Serial.println(sensor);

}

