//01_drummach_due_generator - drummachine sound test for Arduino Due.

//--------------------------------------------
//Notes:
//--------------------------------------------
//This sketch generates percussion sounds for Arduino Due.
//It's based on drums/06_drum_pedal_2tones_timbres,
//I love sound instabilities, so run sound loop at main loop, and control steps are called by timer!
//Sound is still 1 bit, and I use 12-bit DAC for volume control.
//
//For testing simple Arduino Due sound generation, see tests/due_analog_01

//--------------------------------------------
//Controller: Arduino Due
//Additional Libs to install: Due Timer

//Connections:
//Using 250000 Baud for Serial, because Due can't work properly with 500000 which I would prefer...
//https://forum.arduino.cc/t/arduino-due-baudrate-higher-than-115200/539463/4

//Connect Jack output to Due:
//- Due Gnd -> Jack Gnd
//- Due DAC0 -> Resistor on 500 Ohm -> Jack Signal (if mono, if stereo - to both signals).
//--------------------------------------------

//Links on sound generating with Due:
//http://groovuino.blogspot.com/
//http://rcarduino.blogspot.com/2012/12/arduino-due-dds-part-1-sinewaves-and.html
//https://github.com/Gaetino/Groovuino

//--------------------------------------------
#include <DueTimer.h>

const int FPS = 100;          //Control rate
const int Sample_Rate = 16000; //Sound generator rate

//-----------------------------------------------------------------------
void setup() {
  Serial.begin(250000);
  prln();
  prln("----------------------------------------------------------------");
  prln("Endless Drummachine 01_drummach_due_generator - drummachine sound test for Arduino Due, v. 1.1");
  prln("----------------------------------------------------------------");
  pr("Control rate: "); prln(FPS);

  //Set analogWrite resolution (for DAC)
  analogWriteResolution(12);

  //Run timers
  //Timer0.attachInterrupt(loop1).setFrequency(44100).start();
  Timer8.attachInterrupt(control_loop).setFrequency(FPS).start();

}

//-----------------------------------------------------------------------
//Control loop - called by timer
int time_ = 0;

void control_loop() {
  //start sound each second
  if (time_ == 0) {
    prln("play");
  }
  time_++;
  time_ %= 100;
}

//-----------------------------------------------------------------------
//Main loop - used for audio
void loop() {
  static long int t = 0;
  t++;
  //prln(t);

  //long int mcs = micros();
  //prln(mcs);
  // digitalWrite(LED_BUILTIN, HIGH);
  //float val = sin(t*0.05);
  //val = val * 0.5 + 0.5;
  //int v = int(val * 4095);
  for (int v=0; v<2; v++) {
    analogWrite(DAC0, v*1000);       //Output sound, no need set "OUTPUT" mode
    analogWrite(DAC1, v*1000);
    delayMicroseconds(10);
  }
}

//-----------------------------------------------------------------------
