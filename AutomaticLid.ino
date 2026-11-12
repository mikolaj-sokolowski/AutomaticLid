#include <Streaming.h>
#include <Servo.h>
Servo lid;
const int TRIG_PIN = 9;
const int ECHO_PIN = 10;
const unsigned long timeout = 25000; // in microseconds; unsigned long instead of long because time is never negative

void setup(){
  pinMode(TRIG_PIN, OUTPUT); // Trig sends the signal to the sensor
  pinMode(ECHO_PIN, INPUT); // Echo receives the signal (anything the Arduino reads from is INPUT: buttons, digital inputs, etc.)
  Serial.begin(9600);
  lid.attach(6);
  lid.write(90); // closed position is 90°, not 0°, because of how the servo is attached to the lid
}

void loop(){
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10); // the HC-SR04 trigger pulse has to last 10 microseconds
  digitalWrite(TRIG_PIN, LOW);
  long time = pulseIn(ECHO_PIN, HIGH, timeout); // pulseIn(1. pin, 2. state to measure, 3. optional extras such as the timeout)
  float measure_distance = 0.0343 * time / 2; 
  

  if(time == 0){
    Serial << "can't see anything" << endl;
  }else{
  Serial << measure_distance << " cm" << endl; 
  }

  if(measure_distance > 0 && measure_distance <= 30){
  lid.write(0); 
  }else{
  lid.write(90); 
  }
  delay(500);
}
