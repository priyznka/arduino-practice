int lightsense=0;
int resistor_pin=A0;
int threshold =600;
int ledR =9;
int ledG =10;
int ledB =11;

void setup() 
{
  Serial.begin(9600);
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
}

void loop() 
{
  lightsense=analogRead(resistor_pin);
  Serial.print("Photoresistor:");
  Serial.print(lightsense);
  if(lightsense<threshold) 
  {
    ALL_OFF();randomLED();
  }
  else
  {ALL_OFF();}
  delay(500);
}

void randomLED() 
{
  int index;
  index =random(7); // pick a random number between 0 and 7
  switch(index) 
  {
    case 0:
      RED();
      break;
    case 1:
      BLUE();
      break;
    case 2:
      GREEN();
      break;
    case 3:
      YELLOW();
      break;
    case 4:
      CYAN();
      break;
    case 5:
      ORANGE();
      break;
    case 6:
      PURPLE();
      break;
    default:
      RED();
      break;
   }
}

void RED() 
{ //set the LED pins to values that make red    
  analogWrite(ledR, 100);
  analogWrite(ledG, 0);
  analogWrite(ledB, 0);
}

void GREEN() 
{//set the LED pins to values that make green    
  analogWrite(ledG, 100);
  analogWrite(ledR, 0);
  analogWrite(ledB, 0);
}

void BLUE() 
{
  analogWrite(ledB, 100);
  analogWrite(ledR, 0);
  analogWrite(ledG, 0);
}

void CYAN() 
{
  analogWrite(ledR, 0);
  analogWrite(ledG, 100);
  analogWrite(ledB, 100);
}

void ORANGE() {
  analogWrite(ledR, 100);
  analogWrite(ledG, 50);
  analogWrite(ledB, 0);
}

void YELLOW() 
{
  analogWrite(ledR, 100);
  analogWrite(ledG, 100);
  analogWrite(ledB, 0);
}

void PURPLE() 
{
  analogWrite(ledR, 100);
  analogWrite(ledG, 0);
  analogWrite(ledB, 100);
}

void ALL_OFF() 
{
  analogWrite(ledR, 0);
  analogWrite(ledG, 0);
  analogWrite(ledB, 0);
}
