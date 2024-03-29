 // LED leads connected to PWM pins
const int RED_LED_PIN = 9;
const int GREEN_LED_PIN = 10;
const int BLUE_LED_PIN = 11;

/// ----------------

// (from http://www.kasperkamperman.com/blog/arduino/arduino-programming-hsb-to-rgb/)

void getRGB(int hue, int sat, int val, int colors[3]) {
  /* convert hue, saturation and brightness ( HSB/HSV ) to RGB
    The dim_curve is used only on brightness/value and on saturation
(inverted).
    This looks the most natural.
  */
  int r;
  int g;
  int b;
  int base;

  if (sat == 0) { // Acromatic color (gray). Hue doesn't mind.
    colors[0]=val;
    colors[1]=val;
    colors[2]=val;
  } else  {

    base = ((255 - sat) * val)>>8;

    switch(hue/60) {
    case 0:
        r = val;
        g = (((val-base)*hue)/60)+base;
        b = base;
    break;

    case 1:
        r = (((val-base)*(60-(hue%60)))/60)+base;
        g = val;
        b = base;
    break;

    case 2:
        r = base;
        g = val;
        b = (((val-base)*(hue%60))/60)+base;
    break;

    case 3:
        r = base;
        g = (((val-base)*(60-(hue%60)))/60)+base;
        b = val;
    break;

    case 4:
        r = (((val-base)*(hue%60))/60)+base;
        g = base;
        b = val;
    break;

    case 5:
        r = val;
        g = base;
        b = (((val-base)*(60-(hue%60)))/60)+base;
    break;
    }

    colors[0]=r;
    colors[1]=g;
    colors[2]=b;
  }
}

int rgb_colors[3];
/// ----------------

int redIntensity;
int greenIntensity;
int blueIntensity;

void setup() {

}

void loop() {
  int sensorValue = analogRead(A0);

  getRGB(map(sensorValue, 0, 1023, 0, 255), 0xff, 0xff, rgb_colors);

  redIntensity = rgb_colors[0];
  greenIntensity = rgb_colors[1];
  blueIntensity = rgb_colors[2];

  // Display the requested color
  analogWrite(RED_LED_PIN, 255-redIntensity);
  analogWrite(GREEN_LED_PIN, 255-greenIntensity);
  analogWrite(BLUE_LED_PIN, 255-blueIntensity);

}
