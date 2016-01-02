# Arduino Piezo Ocarina

This project was created for a Grade 12 Robotics and Control Systems course. The wiring was designed in Fritzing, and the device was programmed and constructed using Arduino to have record/replay functions, 3 musical modes, and an LED bulb mode display.

The following pictorials were created in Fritzing: 
![enter image description here](http://puu.sh/mghhh/5a66c52339.jpg)
![enter image description here](http://puu.sh/mghkm/94ba8d61c2.png)

The program allows a user to control a piezo using 5 button switches; 5 for sound, and 1 for recording. A potentiometer is used to switch between the Ionian, Dorian, and Zeldarian modes. After each switch, an LED shifter with 8 LEDs is used to indicate the modal change. To record a sequence, hold down the large button while playing the sequence. After the button is released, the sequence will be immediately replayed. 
Because of the lack of microphone, the fifth small button switch is used for the open hole fingering.

Reference:
- I. Frequencies from http://www.soundoctor.com/freq.htm
- II. a) Ionian (in C) fingering: http://smule-web.s3.amazonaws.com/ocarina/scores/ionian.pdf
- II. b) Zeldarian (in A#/Bb) fingering: http://smule-web.s3.amazonaws.com/ocarina/scores/zeldarian.pdf
- II. c)Dorian (in D) fingering: http://smule-web.s3.amazonaws.com/ocarina/scores/dorian.pdf
- III. Smule Songbook (to play): https://www.smule.com/songbook/scores
