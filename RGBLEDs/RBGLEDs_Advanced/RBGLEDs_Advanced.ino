
// LED leads connected to PWM pins
const int RED_LED_PIN = 9;
const int GREEN_LED_PIN = 10;
const int BLUE_LED_PIN = 11;

// HTML-style hex triplet color code values from Wikipedia
const unsigned long ORANGE = 0xFF7F00;
const unsigned long TEAL = 0x008080;
const unsigned long AUBERGINE = 0x614051;

// Length of time we spend showing each color
const int DISPLAY_TIME = 2000; // In milliseconds


void setup() {
  // No setup required.  
}


void loop() {
  // Cycle through our awesome colors
  
  setColor(ORANGE);
  delay(DISPLAY_TIME);
  
  setColor(TEAL);
  delay(DISPLAY_TIME);
  
  setColor(AUBERGINE);
  delay(DISPLAY_TIME);
}


void setColor(unsigned long color) {
  /* 
    Sets the color of the RGB LED to the color specified by the
    HTML-style hex triplet color value supplied to the function.
    
    The color value supplied should be an unsigned long number
    of the form:
    
      0xRRGGBB
      
      e.g. 0xFF7F00 is orange
      
    where:
   
       0x specifies the value is a hexadecimal number
       RR is a byte specifying the red intensity
       GG is a byte specifying the green intensity
       BB is a byte specifying the blue intensity


    How it works (you don't need to understand this to use the function):

    The supplied value of the form 0xRRGGBB is an unsigned long which can
    store four bytes. If we view the number in bit form the bits of the
    unsigned long look like this:
    
      iiiiiiiirrrrrrrrggggggggbbbbbbbb
      
    where:
    
      i are bits that are ignored (because we only need three bytes for the value)
      r are bits specifying the red intensity
      g are bits specifying the green intensity
      b are bits specifying the blue intensity
      
    We use bit shifting and masking to extract the individual values.
    
    Bit shifting moves the bits in a number along in one direction to produce
    a new number. For example ">> n" means shift the bits n positions to the
    right.
    
      e.g. iiiiiiiirrrrrrrrggggggggbbbbbbbb >> 8 gives:
      
           00000000iiiiiiiirrrrrrrrgggggggg
           
    
    The number 0xFF represents the bit mask:
    
      00000000000000000000000011111111
      
    The "&" character means the two values are "and"ed together--for each bit
    in the two numbers being "and"ed together the resulting bit is only set in
    the result if the same bits are set in both the input numbers.
  
    So, continuing our example:
    
      00000000iiiiiiiirrrrrrrrgggggggg && 0xFF gives:
      
      00000000iiiiiiiirrrrrrrrgggggggg &&
      00000000000000000000000011111111 =
      000000000000000000000000gggggggg
      
    And we now have extracted only the green bits from our hex triplet.
    
    More details on bit math can be found here:
    
       <http://www.arduino.cc/playground/Code/BitMath>
      
   */

  // Extract the intensity values from the hex triplet
  byte redIntensity = (color >> 16) & 0xFF;
  byte greenIntensity = (color >> 8) & 0xFF;
  byte blueIntensity = color & 0xFF;

  // Display the requested color  
  analogWrite(RED_LED_PIN, redIntensity);
  analogWrite(GREEN_LED_PIN, greenIntensity);
  analogWrite(BLUE_LED_PIN, blueIntensity); 
}

