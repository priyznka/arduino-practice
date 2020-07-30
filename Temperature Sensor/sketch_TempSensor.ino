//program to output the current temperature to the IDE's debug window 

//TMP36 Pin Variables
int temperaturePin = 0; //the analog pin the TMP36's Vout (sense) pin is connected to
                        //the resolution is 10 mV / degree centigrade 
                        //(500 mV offset) to make negative temperatures an option

void setup()
{
  Serial.begin(9600);  
  //Start the serial connection with the copmuter to view the result open the serial monitor last button beneath the file bar (looks like a box with an antenae)
}

//returns the voltage on the analog input defined by pin

float getVoltage(int pin)
{
  return (analogRead(pin) * .004882814); //converting from a 0 to 1023 digital range
                                          // to 0 to 5 volts (each 1 reading equals ~ 5 millivolts
}
 
void loop()                  
{
   float temperature = getVoltage(temperaturePin); 
   //gets the voltage reading from temp. sensor
   temperature = ((temperature*10) + .5)
   //for advanced do: temp = ((temperature*10) + .5)*1.8 + 32;  
   
   //converts from 10 mv/degree with 500 mV offset to degrees      
   Serial.println(temperature);                     
   //printing the result
   delay(1000);                                  
}
