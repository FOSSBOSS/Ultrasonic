#include <MIDI.h>

/*
Revisiting the Ultra sonic theramin, using multiple 
sensors. 
Construction notes:
the breadboard has 4 ultra sonics sensors side by side,
and they will totaly interfere with eachother, 
given thier proximity. The ultra sonic field is a cone
around the front face of each sensor.


built on a Teensy 4.1
to configure the Teensy as a MIDI device in the Arduino IDE:
 goto (Menu) tools,USB-Type: MIDI
*/

// Sensor IO
#define TRIG_PIN_1 2
#define ECHO_PIN_1 3

#define TRIG_PIN_2 4
#define ECHO_PIN_2 5

#define TRIG_PIN_3 6
#define ECHO_PIN_3 7

#define TRIG_PIN_4 8
#define ECHO_PIN_4 9
// Limits
#define NOTE_MIN 20
#define NOTE_MAX 100
#define DIST_MIN 5
#define DIST_MAX 100
#define VELOCITY_MIN 0
#define VELOCITY_MAX 127

MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  pinMode(TRIG_PIN_1, OUTPUT);
  pinMode(ECHO_PIN_1, INPUT);
  
  pinMode(TRIG_PIN_2, OUTPUT);
  pinMode(ECHO_PIN_2, INPUT);
  
  pinMode(TRIG_PIN_3, OUTPUT);
  pinMode(ECHO_PIN_3, INPUT);

  pinMode(TRIG_PIN_4, OUTPUT);
  pinMode(ECHO_PIN_4, INPUT);
  
  MIDI.begin(MIDI_CHANNEL_OMNI);

}

void loop() {
  int distance1 = getDistance(TRIG_PIN_1, ECHO_PIN_1);
  int distance2 = getDistance(TRIG_PIN_2, ECHO_PIN_2);
  int distance3 = getDistance(TRIG_PIN_3, ECHO_PIN_3);
  int distance4 = getDistance(TRIG_PIN_4, ECHO_PIN_4);
  int dtime = 100;
 
  if (distance1 >= DIST_MIN && distance1 <= DIST_MAX) {
    int note1 = map(distance1, DIST_MIN, DIST_MAX, NOTE_MIN, NOTE_MAX);
    int velocity1 = map(distance1, DIST_MIN, DIST_MAX, VELOCITY_MIN, VELOCITY_MAX);
    // Serial.printf("Note1: %d, Velocity: %d\n", note1, velocity1);
    usbMIDI.sendNoteOn(note1, velocity1, 1);  
    delay(dtime); 
    usbMIDI.sendNoteOff(note1,0,1);
  }

  if (distance2 >= DIST_MIN && distance2 <= DIST_MAX) {
    int note2 = map(distance2, DIST_MIN, DIST_MAX, NOTE_MIN, NOTE_MAX);
    int velocity2 = map(distance2, DIST_MIN, DIST_MAX, VELOCITY_MIN, VELOCITY_MAX);
    usbMIDI.sendNoteOn(note2, velocity2, 1);
    delay(dtime);
    usbMIDI.sendNoteOff(note2,0,1); 
  }
/* */
  if (distance3 >= DIST_MIN && distance3 <= DIST_MAX) {
    int note3 = map(distance3, DIST_MIN, DIST_MAX, NOTE_MIN, NOTE_MAX);
    int velocity3 = map(distance3, DIST_MIN, DIST_MAX, VELOCITY_MIN, VELOCITY_MAX);
    usbMIDI.sendNoteOn(note3, velocity3, 1);
    delay(dtime); 
    usbMIDI.sendNoteOff(note3,0,1);
  }

  if (distance4 >= DIST_MIN && distance4 <= DIST_MAX) {
    int note4 = map(distance4, DIST_MIN, DIST_MAX, NOTE_MIN, NOTE_MAX);
    int velocity4 = map(distance4, DIST_MIN, DIST_MAX, VELOCITY_MIN, VELOCITY_MAX);
    usbMIDI.sendNoteOn(note4, velocity4, 1);
    delay(dtime);
    usbMIDI.sendNoteOff(note4,0,1); 

  }

}

int getDistance(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  // The value 0.034 corresponds to the speed of sound in centimeters per microsecond through air.
  // Divided by 2, because the signal goes out and comes back. durration * 0.17 would also work
  return distance;
}
