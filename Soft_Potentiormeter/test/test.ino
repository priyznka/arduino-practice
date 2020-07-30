int red=9;
int green=10;
int blue=11;


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(red, OUTPUT);
pinMode(green, OUTPUT);
pinMode(blue, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
int x = analogRead(3);
Serial.println(x);
}
