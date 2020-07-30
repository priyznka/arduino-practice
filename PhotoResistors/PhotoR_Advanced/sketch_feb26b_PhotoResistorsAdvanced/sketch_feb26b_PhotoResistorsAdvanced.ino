//changes the intensity of LED based on amount of light incident on the photo resistor

//PhotoResistor Pin
int lightPin = A0; 
//the analog pin the photoresistor is connected to the photoresistor is a raw sensor value (relative light)

//LED Pin
int ledPin = 13;   
//pin LED is connected to, controlling the brightness so we use PWM (pulse wiedth modulation)

void setup()
{
  pinMode(ledPin, OUTPUT); //sets the led pin to output
}

void loop()
{
   int threshold = 400;
   if(analogRead(lightPin) > threshold)
   {
    digitalWrite(ledPin, LOW);
   }
   else
   {
    digitalWrite(ledPin, HIGH);
   }
}
