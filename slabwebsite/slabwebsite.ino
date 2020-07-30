/* 
 24-1-2013
 Code developed by: Alicia Fortier
 Original structure: Nathan Seidle, Spark Fun Electronics
 This code has a Beerware license: If you meet either of the developers someday, you buy them a beer.
 Otherwise Public Domain
 
 MUSICAL INSTRUMENT SHIELD
 built Vs1053 chip, which holds the sound banks
 we need to communicate to it serially, see documentation page to get more info on the details on how that's done
 The code is (hopefully) filled with helpful comments though so that you don't need to understand 
 all of the nitty gritty to start modifying/playing/understanding what's going on.
 
 WARNING: I tried my best, but being a human being there could be bugs/inefficiencies. Infact, I'm sure there are.
 Feel free to send feed back and rewrite this code (please!) 
 or begrugingly swear and rewrite this code(more likely)
 */
//include software library to communicated with board properly
#include <SoftwareSerial.h>
//start serial communication
SoftwareSerial mySerial(2, 3); //Soft TX on 3, we don't use RX in this code
//ties to chip Reset line
byte resetMIDI = 4;
//DEFINE VALUES THAT WILL NOT BE CHANGED. MORE EFFICIENT THAN CONSTANTS
//HEX NUMBERS FOR COMMANDS
#define CTRLCHANNEL 0xB0
#define CTRLINSTRUMENT 0xC0
#define CTRLON 0x09
#define CTRLOFF 0x08
#define SETVOLUME 0x07

//SOUND BANKS LOCATIONS
#define BNKPERCUSSION 0x78
#define BNKMELODY 0x79

//SOUND ARRAYS
//See page 33 of vs1053 datasheet, available on slab website or from manufacturer
//for what sounds these numbers correspond to
//Percussion
#define MINPerIndex 27 //minimum instrument value
#define MAXPerIndex 87
#define MAXPERCUSSION  61 //length of array
//Melody
#define MINMelIndex 1
#define MAXMelIndex 127 
#define MAXMELODY  127 //length of array
//Instantiate arrays
int perSounds [MAXPERCUSSION];
int melSounds [MAXMELODY];

//BUTTONS
//Sound Navigation
int btnPrev = 8; //red
int btnNext = 9; //blue
int btnBnkToggle = 7;  //Yellow
boolean isPercussion= true;

//booleans to activate when btnpressed
boolean triggerNext = false;
boolean triggerPrev = false;
boolean triggerToggle = false;

//used values
int curVolume;
//inserting small pauses helps everything run smoothly
int pause = 50;

//current values
int curIndexMAX; //keeps track of the max Index available
int curMINVal; //keeps track of the value at index [0]
int curMAXVal;
int curBank; //current music bank (Percussion default, alt Melody)
int curIndex; //current Index current array
int melIndex; //current Index in melody array
int perIndex; //current Index in percussion array

int curInstrumentNumber;

void setup()
{
  //Everything that needs to only be set once or needs an initial value goes here.
  //Start Serial communiccation to be able to view prinlns
  //to see the messages, click the magnifying glass in  the top right corner
  //in the pop-up, be sure that the xxxx baud matches the number below.
  Serial.begin(57600);
  //Setup soft serial for MIDI control; allows you to give commands in noteOn(); noteOff(); and talkMIDI();
  mySerial.begin(31250);
  //Reset the chip (vs1053)
  pinMode(resetMIDI, OUTPUT);
  digitalWrite(resetMIDI, LOW);
  delay(100);
  digitalWrite(resetMIDI, HIGH);
  delay(100);
  //set btn modes, telling them you want to RECEIVE information, not give current
  pinMode (btnNext, INPUT);
  pinMode (btnPrev, INPUT);
  pinMode (btnBnkToggle, INPUT);
  //for each Index i in array; add one to MAXPERCUSSION to compensat for 0base; add one to the index on each iteration
  for (int i=0; i<MAXPERCUSSION; i++)
  {
    //give it the corresponding number between the min and max (27-87)
    perSounds[i] = MINPerIndex +i;
  }  
  for (int i=0; i<MAXMELODY; i++)
  {
    //give it the corresponding number between the min and max (1-128)
    melSounds[i] = MINMelIndex +i; //since index starts at 0 and the bank at 1
  }
  //I set these here since their value could change later in the program
  curIndex = 0;
  perIndex = 0;
  melIndex = 0;
  //default to percussion
  curBank = BNKPERCUSSION;
  curIndexMAX  = MAXPERCUSSION-1;//MAXPERCUSSION is the array length, -1 for index value
  curMAXVal = MAXPerIndex ;
  curMINVal = MINPerIndex;
  curVolume = 100;// max value 127
  //keeps track of the currentInstrumentNumber for the println
  curInstrumentNumber= perSounds[perIndex];
  //print new information aobut what is playing
  printInfo();
}
void loop()
{
  // set the sound volume. talkMidi uses this information to talk to chip
  //channel command, change the volume, to current volume
  talkMIDI (CTRLCHANNEL, SETVOLUME, curVolume);
  //this is channel command, on channel 0, current sound bank
  talkMIDI(CTRLCHANNEL, 0, curBank);
  //check if the buttons are being pressed
  readBTN();
  //play the correct sound
  playSound();
}
void playSound()
{
  if (isPercussion)
  {
    //The instruments here aren't influenced by pitch, so it's really only the index of the instrument you're calling

    //command change instrument, to the value of the current index, only 1 bit data required
    talkMIDI(CTRLINSTRUMENT, curIndex,0);
    //channel 0, instrument in the array,  at the value of the current Volume
    noteOn(0, perSounds[curIndex], curVolume);
    //delay to hear it properly
    delay(500);
    noteOff(0, perSounds[curIndex], curVolume);

    curInstrumentNumber = perSounds[curIndex];
  }
  else
  {
    //melody instruments need the index of the instrument and the pitch to play it at- more like a synthesizer
    talkMIDI(CTRLINSTRUMENT, melSounds[curIndex],0);
    //Note on channel 1 (0x90), some note value (note), middle velocity (0x45):
    //channel 0, pitch(Low), volume
    noteOn(0, 30, curVolume);
    delay(250);
    noteOff(0, 30, curVolume);
    //channel 0, pitch(High), volume
    noteOn(0, 80, curVolume);
    delay(250);
    noteOff(0, 80, curVolume);

    curInstrumentNumber = melSounds[curIndex];
  }
}
void readBTN()
{
  //Check if your buttons are pressed
  //Return HIGH when the button is pressed
  //LOW when button is not pressed
  int btnNextState = digitalRead(btnNext);
  int btnPrevState = digitalRead(btnPrev);
  int btnToggleState = digitalRead(btnBnkToggle); 
  //NEXT BUTTON
  if (btnNextState) //if Next button pressed
  { //if next still needs to be triggered
    if(triggerNext)
    { //if at Maximum, set it to minimum
      if (curIndex == curIndexMAX) //curIndex corresponds to the length, -1 for the index position
      { 
        curIndex = 0; 
        curInstrumentNumber = curMINVal; 
      }
      else //if not, increase index
      { 
        curIndex ++;
        curInstrumentNumber ++; 
      }
      //turn trigger off so it only gets done once
      triggerNext = false;
      //print new information aobut what is playing
      printInfo();
    }  
    else //if next button not being pressed
    {
      triggerNext = true;//so that Next will trigger the next time its pressed    
    }
  }
  //PREVIOUS BUTTON
  if (btnPrevState) //if Prev button pressed
  {
    if(triggerPrev)
    {
      //if at Minimum, set it to maximum
      if (curIndex == 0)
      { 
        curIndex = curIndexMAX; //curIndex corresponds to the length, -1 for the index position

        curInstrumentNumber = curMAXVal; 
      }
      else
      { 
        curIndex --; 
        curInstrumentNumber --; 
      }
      //Serial.println(perSounds[60]);
      triggerPrev = false;
      //print new information aobut what is playing
      printInfo();
    }
    else
    {
      triggerPrev = true; 
    }
  }
  //TOGGLE BUTTON
  if(btnToggleState)
  {//if currently percussion, change to melody
    if(isPercussion && triggerToggle)
    {
      //store the current index as percussion index
      perIndex = curIndex;
      //change the current index to the melody index
      curIndex = melIndex;
      curInstrumentNumber = melSounds[curIndex];
      curIndexMAX = MAXMELODY-1; 
      curMINVal = MINMelIndex; 
      curMAXVal = MAXMelIndex; 
      curBank = BNKMELODY;
      isPercussion = false;
      //trigger Toggle determines whether the action has already been triggered for this press
      //prevents change by holding down button 
      triggerToggle = false;
      //print new information aobut what is playing
      printInfo();
    }
    else if (triggerToggle)
    {
      //store the current index as percussion index
      melIndex = curIndex;
      //change the current index to the melody index
      curIndex = perIndex;
      curInstrumentNumber = perSounds[curIndex];
      curIndexMAX = MAXPERCUSSION-1 ;
      curMINVal = MINPerIndex;
      curMAXVal = MAXPerIndex ;
      curBank = BNKPERCUSSION;
      isPercussion = true;
      triggerToggle = false;
      printInfo();
    }
  }
  else //if button not being held, reset the trigger to true so it activates on next press
  { 
    triggerToggle = true; 
  } 
}
//Send a MIDI note-on message.  Like pressing a piano key
//channel ranges from 0-15
void noteOn(byte channel, byte note, byte attack_velocity) 
{
  talkMIDI( (0x90 | channel), note, attack_velocity);
}
//Send a MIDI note-off message.  Like releasing a piano key
void noteOff(byte channel, byte note, byte release_velocity) 
{
  talkMIDI( (0x80 | channel), note, release_velocity);
}
//Plays a MIDI note. Doesn't check to see that cmd is greater than 127, or that data values are less than 127
void talkMIDI(byte cmd, byte data1, byte data2)
{
  mySerial.write(cmd);
  mySerial.write(data1);
  //Some commands only have one data byte. All cmds less than 0xBn have 2 data bytes 
  //(sort of: http://253.ccarh.org/handout/midiprotocol/)
  if( (cmd & 0xF0) <= 0xB0)
    mySerial.write(data2);
}
void printInfo()
{
  Serial.println("///////////////////////////////////////");
  Serial.println("120 : Percussion Bank // 121 : Melody Bank");
  Serial.println("///////////////////////////////////////");
  Serial.print("You are listening to bank:  ");
  Serial.println( curBank);
  Serial.print("Instrument number:  ");
  Serial.println( curInstrumentNumber);
  Serial.print("At Volume:  ");
  Serial.println( curVolume);
  Serial.println("///////////////////////////////////////");
}
