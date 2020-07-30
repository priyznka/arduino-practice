#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); //Soft TX on 3, we don't use RX in this code

byte note = 0; //The MIDI note value to be played
byte resetMIDI = 4; //Tied to VS1053 Reset line
byte ledPin = 13; //MIDI traffic indicator
int instrument = 0;
int scale_major[] = {0, 2, 4, 5, 7, 9, 11};        //one octave of major scale
int scale_minpent[] = {0, 2, 3, 5, 6, 7, 10};     //minor pentatonic scale
int scale_consonant[] = {0, 2, 4, 7, 9, 12, 14}; //major pentatonic scale plus octave and 9th (to be same array length as others)


int drum_motown[100][3] = //Tick (out of 384 per bar), note, velocity
{                         //This is an attempt to adapt data from an actual MIDI file, with
  { 0,54,94 },            //matching 0-velocity lines in place of noteOff messages
  { 0,48,97 },
  { 8,54,0 },
  { 48,54,75 },
  { 51,48,0 },
  { 54,54,0 },
  { 96,50,106 },
  { 96,54,96 },
  { 103,54,0 },
  { 127,50,0 },
  { 144,54,73 },
  { 153,54,0 },
  { 171,50,92 },
  { 177,50,0 },
  { 192,54,82 },
  { 201,54,0 },
  { 219,48,85 },
  { 240,54,84 },
  { 240,48,0 },
  { 246,54,0 },
  { 267,48,86 },
  { 273,48,0 },
  { 288,54,101 },
  { 288,50,103 },
  { 296,54,0 },
  { 318,50,0 },
  { 336,54,77 },
  { 344,54,0 },
  { 363,50,70 },
  { 368,50,0 }
};
int drumSpot = 0;
int drumSpotTime = 0;

long curTime = 0;
int timeclock96 = 0;  //96 ticks per beat, based on 4 subdivs per beat and 24 ticks per subdiv (not 240 like the source midi file)




void setup() {
  Serial.begin(57600);

  //Setup soft serial for MIDI control
  mySerial.begin(31250);

  //Reset the VS1053
  pinMode(resetMIDI, OUTPUT);
  digitalWrite(resetMIDI, LOW);
  delay(100);
  digitalWrite(resetMIDI, HIGH);
  delay(100);
 
 talkMIDI(0xB0, 0, 0x78); //Bank select: drums
  talkMIDI(0xB0, 0, 0x00); //Bank select GM1
 
  talkMIDI(0xB9, 0x07, 50); //0xB0 is channel message for channel 10 (9), set channel volume to 50
  talkMIDI(0xB9, 0, 0x78); //Bank select drums
 
  curTime = millis();
}




void loop() {
  timeclock96 = (millis() - curTime)/96;
  Serial.println(timeclock96);
  for (int j = drumSpot; j<100; j++) {
    drumSpotTime = (int)drum_motown[drumSpot,0];
    if (drumSpotTime < timeclock96) {
      noteOn(0, (byte)10, drum_motown[drumSpot,1], drum_motown[drumSpot,2]);   //ERROR HERE: invalid conversion from int* to byte
    }
  if (timeclock96 >= 96) {
    curTime = millis();
  }
 
//  playNoodling(0, random(48,59), scale_consonant, 180, 0);

}


void playNoodling(byte channel, int key, int scale[], float tempo, int instrument) {
  Serial.print(" Instrument: ");
  Serial.println(instrument, DEC);
  talkMIDI(0xC0, instrument, 0); //Set instrument number. 0xC0 is a 1 data byte command
  talkMIDI(0xCA, 30, 0); //Set instrument number. 0xC0 is a 1 data byte command
 
  for (int i = 0; i < 16; i++) {
    int note = key + scale[random(0, 6)];
    noteOn(1, channel, note, 80);
    noteOn(0, 10, drum_pattern1[i], 50);
   
    //1 minute      60 seconds    1000 ms               
    //---------  x  ---------  x  --------
    //120 Beats     1 minute      1 second
    delay(60000/tempo);
    noteOff(1, channel, note, 0);
    noteOff(0, 10, drum_pattern1[i], 0);
  }
}



void allOff(byte channel) {
  talkMIDI ( (0xB0 | channel), 123, 0);
}

//Send a MIDI note-on message.  Like pressing a piano key
//channel ranges from 0-15
void noteOn(boolean instr, byte channel, byte note, byte attack_velocity) {
  talkMIDI( (0x90 | channel), note, attack_velocity);
}

//Send a MIDI note-off message.  Like releasing a piano key
void noteOff(boolean instr, byte channel, byte note, byte release_velocity) {
  talkMIDI( (0x80 | channel), note, release_velocity);
}

//Plays a MIDI note. Doesn't check to see that cmd is greater than 127, or that data values are less than 127
voi
