/*  ARDUINO OCARINA
    By:              Peter Feng, Sally Hui
    Course:          TER4M1
    Teacher:         Jay, S.
    Date Created:    May 15, 2014
    Description:     This program allows a user to control a piezo using
                     5 button switches; 5 for sound, and 1 for recording.
                     A potentiometer is used to switch between the Ionian.
                     Dorian and Zeldarian modes. After each switch, 
                     an LED shifter with 8 LEDs is used to indicate the 
                     modal change. To record a sequence, hold down the 
                     large button while playing the sequence. After the
                     button is released, the sequence will be immediately
                     replayed. 
    Reference:
    I. Frequencies from http://www.soundoctor.com/freq.htm
    II. a) Ionian (in C) fingering: http://smule-web.s3.amazonaws.com/ocarina/scores/ionian.pdf
    II. b) Zeldarian (in A#/Bb) fingering: http://smule-web.s3.amazonaws.com/ocarina/scores/zeldarian.pdf
    II. c)Dorian (in D) fingering: http://smule-web.s3.amazonaws.com/ocarina/scores/dorian.pdf
    III. Smule Songbook (to play): https://www.smule.com/songbook/scores
    Note: Because of the lack of microphone, the fifth small button switch
    is used for the open hole fingering.
*/

// PIN ASSIGNMENTS
const int buttonPin1 = 8; // "piano" buttons
const int buttonPin2 = 11;
const int buttonPin3 = 9;
const int buttonPin4 = 10;
const int buttonPin5 = 13;
const int speakerPin = 5; // piezo
const int record = 12; // record button
const int potentiometer = 1;
const int data = 4; // shifter
const int clock = 2;
const int latch = 3;

// Piezo
int notesRecord[200]; //array sequences are stored in 
int arrayCounter = 0; // logical size of array used
boolean isRecording = false; // keep track of when is recording
boolean newSequence = false; // new sequence; clear "logical size" of array

// Frequency of square waves sent to piezo made by the following 
// calculation:
//       timeHigh = period / 2 = 1 / (2 * toneFrequency)
// Refer to II. for notes and I. for period lengths
int ionianC[] = {2550, 2400, 2270, 2150, 2000, 1900, 1700, 1500, 
  1450, 1350, 1275, 1200, 1135, 1050, 1000, 950}; // Ionian C mode
int zeldarianASharp[] = {2850, 2270, 2150, 1900, 1800, 1700, 1600, 
  1500, 1450, 1350, 1275, 1200, 1135, 1050, 950, 900}; // Zeldarian A# mode
int dorianD[] = {2270, 2150, 2000, 1900, 1800, 1700, 1500, 1450, 1270, 
  1200, 1135, 1050, 1000, 950, 950, 850}; // Dorian D mode
  
// Various state variables
int recordPressed = 0; // if recording
int potentiometerValue = 0;
boolean isReplayed = true; // has sequence been replayed
int mode = 0; // which mode to play in; 0 ionian, 1 zeldarian, 2 dorian

// Setup necessary variables
void setup() {
  // Piezo
  pinMode(speakerPin, OUTPUT);
  
  // Note buttons
  pinMode(buttonPin1, INPUT); 
  digitalWrite(buttonPin1, HIGH);
  
  pinMode(buttonPin2, INPUT); 
  digitalWrite(buttonPin2, HIGH);
  
  pinMode(buttonPin3, INPUT); 
  digitalWrite(buttonPin3, HIGH);
  
  pinMode(buttonPin4, INPUT); 
  digitalWrite(buttonPin4, HIGH);
  
  // Recording
  pinMode (record, INPUT);
  digitalWrite (record, HIGH);
  
  // Shifter
  pinMode(data, OUTPUT);
  pinMode(clock, OUTPUT);  
  pinMode(latch, OUTPUT); 
}

// Send LED configuration to shifter to display -- from ARDX.ORG
void updateLEDs(int value){
  digitalWrite(latch, LOW);     //Pulls the chips latch low
  shiftOut(data, clock, MSBFIRST, value); //Shifts out the 8 bits to the shift register
  digitalWrite(latch, HIGH);   //Pulls the latch high displaying the data
}

// Play a specified frequency - from ARDX.ORG
void playTone(int tone) {
  if (tone == 0) // no note is being played
      delay(10);
  else
  {
    for (long i = 0; i < 100 * 1000L; i += tone * 2) {
      digitalWrite(speakerPin, HIGH);
      delayMicroseconds(tone);
      digitalWrite(speakerPin, LOW);
      delayMicroseconds(tone);
    }
  }
}
 
// Reads user input (of buttons) and returns frequency of note to play
int getNote()
{
  int freq = 0, note; // Freq is frequency of note to return
                      // Note refers to the "step" of a note on a scale
                      // e.g. E is the third step of the C Major scale
                      
   // Read the state of the pushbutton values
  boolean btn1 = digitalRead(buttonPin1) == LOW;
  boolean btn2 = digitalRead(buttonPin2) == LOW;
  boolean btn3 = digitalRead(buttonPin3) == LOW;
  boolean btn4 = digitalRead(buttonPin4) == LOW;
  boolean btn5 = digitalRead (buttonPin5) == LOW;
   
  // Refer to II for fingerings
  // (don't think there's a faster/more efficient way to do this...)
  if (mode == 0) // IONIAN C
  { 
    if (!btn1 && btn2 && !btn3 && btn4 && !btn5)
      note = 0;
    else if (btn1 && !btn2 && !btn3 && !btn4 && !btn5)
      note = 1;
    else if (btn1 && !btn2 && !btn3 && btn4 && !btn5)
      note = 2;
    else if (btn1 && btn2 && !btn3 && !btn4 && !btn5)
      note = 3;
    else if (btn1 && btn2 && !btn3 && btn4 && !btn5)
      note = 4;
    else if (btn1 && btn2 && btn3 && btn4 && !btn5) 
      note = 5;
    else if (btn1 && !btn2 && btn3 && btn4 && !btn5) 
      note = 6;
    else if (btn1 && btn2 && btn3 && !btn4 && !btn5) 
      note = 7;
    else if (btn1 && !btn2 && btn3 && !btn4 && !btn5)
      note = 8;
    else if (!btn1 && btn2 && btn3 && btn4 && !btn5)
      note = 9;
    else if (!btn1 && !btn2 && btn3 && btn4 && !btn5)
      note = 10;
    else if (!btn1 && btn2 && btn3 && !btn4 && !btn5)
      note = 11;
    else if (!btn1 && !btn2 && btn3 && !btn4 && !btn5)
      note = 12;
    else if (!btn1 && !btn2 && !btn3 && btn4 && !btn5)
      note = 13;
    else if (!btn1 && btn2 && !btn3 && !btn4 && !btn5)
      note = 14;
    else if (!btn1 && !btn2 && !btn3 && !btn4 && btn5) 
      note = 15;
    else // nothing pressed
      note = 42;
     
    if (note != 42)
      freq = ionianC [note];
  }
  
  else if (mode == 1) // ZELDARIAN A#/Bb
  { 
    if (!btn1 && btn2 && !btn3 && btn4 && !btn5)
      note = 0;
    else if (btn1 && btn2 && !btn3 && btn4 && !btn5)
      note = 1;
    else if (btn1 && btn2 && btn3 && btn4 && !btn5)
      note = 2;
    else if (btn1 && !btn2 && btn3 && btn4 && !btn5)
      note = 3;
    else if (btn1 && btn2 && !btn3 && !btn4 && !btn5)
      note = 4;
    else if (btn1 && btn2 && btn3 && !btn4 && !btn5) 
      note = 5;
    else if (btn1 && !btn2 && btn3 && !btn4 && !btn5) 
      note = 6;
    else if (!btn1 && btn2 && btn3 && btn4 && !btn5) 
      note = 7;
    else if (!btn1 && !btn2 && btn3 && btn4 && !btn5)
      note = 8;
    else if (!btn1 && btn2 && btn3 && !btn4 && !btn5)
      note = 9;
    else if (!btn1 && !btn2 && btn3 && !btn4 && !btn5)
      note = 10;
    else if (!btn1 && !btn2 && !btn3 && btn4 && !btn5)
      note = 11;
    else if (!btn1 && btn2 && !btn3 && !btn4 && !btn5)
      note = 12;
    else if (!btn1 && !btn2 && !btn3 && !btn4 && btn5)
      note = 13;
    else if (btn1 && !btn2 && !btn3 && !btn4 && !btn5)
      note = 14;
    else if (btn1 && !btn2 && !btn3 && btn4 && !btn5) 
      note = 15;
    else // no note pressed
      note = 42;
     
    if (note != 42)
      freq = zeldarianASharp [note];
  }
  
  else if (mode == 2) // DORIAN D
  { 
    if (!btn1 && btn2 && !btn3 && btn4 && !btn5)
      note = 0;
    else if (btn1 && !btn2 && !btn3 && !btn4 && !btn5)
      note = 1;
    else if (btn1 && !btn2 && !btn3 && btn4 && !btn5)
      note = 2;
    else if (btn1 && btn2 && !btn3 && !btn4 && !btn5)
      note = 3;
    else if (btn1 && btn2 && !btn3 && btn4 && !btn5)
      note = 4;
    else if (btn1 && btn2 && btn3 && btn4 && !btn5) 
      note = 5;
    else if (btn1 && !btn2 && btn3 && btn4 && !btn5) 
      note = 6;
    else if (btn1 && btn2 && btn3 && !btn4 && !btn5) 
      note = 7;
    else if (btn1 && !btn2 && btn3 && !btn4 && !btn5)
      note = 8;
    else if (!btn1 && btn2 && btn3 && btn4 && !btn5)
      note = 9;
    else if (!btn1 && !btn2 && btn3 && btn4 && !btn5)
      note = 10;
    else if (!btn1 && btn2 && btn3 && !btn4 && !btn5)
      note = 11;
    else if (!btn1 && !btn2 && btn3 && !btn4 && !btn5)
      note = 12;
    else if (!btn1 && !btn2 && !btn3 && btn4 && !btn5)
      note = 13;
    else if (!btn1 && btn2 && !btn3 && !btn4 && !btn5)
      note = 14;
    else if (!btn1 && !btn2 && !btn3 && !btn4 && btn5) 
      note = 15;
    else // no note pressed
      note = 42;
     
    if (note != 42)
      freq = dorianD [note];
  }
  return freq; // return frequency of fingered note   
}

// Main 
void loop() { 
  
  int play; // frequency of note to play
  
  // Read potentiometer
  potentiometerValue = analogRead (potentiometer);
  if (potentiometerValue < 341)
    mode = 0; // change to ionian mode
  else if (potentiometerValue < 682)
    mode = 1; // change to zeldarian mode
  else 
    mode = 2; // change to dorian mode
  
  // Update LEDs -- LEDs display letter of mode being played
  if (mode == 0) // "i"
    updateLEDs(15);
  else if (mode == 1) // "Z"
    updateLEDs(189);
  else // "d"
    updateLEDs (252);
    
  // Read if record button is pressed
  recordPressed = digitalRead(record);
   
  // Record button pressed
  if (recordPressed == LOW)
  {
    play = getNote(); // get pressed note
    playTone (play); // play the note
    
    isReplayed = false; // new/recording sequence; hasn't been replayed
    notesRecord [arrayCounter] = play; // add note to array
    arrayCounter++; // update logical size of array
  }
  
  // Record button is not being pressed
  else
  {    
    // Replay sequence if it hasn't been
    if (!isReplayed) 
    {
      // play through notes stored in logical size of array
      for (int i = 0; i <= arrayCounter; i++) 
        playTone (notesRecord [i]);
        
      isReplayed = true; // update replay status
      arrayCounter = 0; // update logical size of array
    }
    
    // Play new note
    play = getNote(); 
    playTone (play);
  }
}

