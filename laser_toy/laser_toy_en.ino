#include <Servo.h>

#define FIRST_LINK_SERVO_PIN  9   // pin of the first link servo
#define SECOND_LINK_SERVO_PIN 10  // pin of the second link servo
#define LASER_PIN             11  // laser pin

#define BASE_FIRST_LINK_SERVO_POS   90  // base position of servos (in degrees)
#define BASE_SECOND_LINK_SERVO_POS  90

#define MIN_FIRST_LINK_SERVO_POS    45  // minimum angle that the first servo can take
#define MAX_FIRST_LINK_SERVO_POS    135 // minimum angle that the first servo can take

#define MIN_SECOND_LINK_SERVO_POS    80  // minimum angle that the second servo can take
#define MAX_SECOND_LINK_SERVO_POS    150  // minimum angle that the second servo can take

#define LASER_BRIGHTNESS  200 // яlaser brightness
#define SERVO_DELAY       6

Servo firstLinkServo;   // first link servo
Servo secondLinkServo;  // second link servo


void setup() {
  pinMode(LASER_PIN, OUTPUT);
  analogWrite(LASER_PIN, LOW);
  
  firstLinkServo.attach(FIRST_LINK_SERVO_PIN);      // bind drives to ports
  secondLinkServo.attach(SECOND_LINK_SERVO_PIN);    //
  
  firstLinkServo.write(BASE_FIRST_LINK_SERVO_POS);  // set to base position
  delay(200);
  secondLinkServo.write(BASE_SECOND_LINK_SERVO_POS); // set to base position
  delay(200);
  
  analogWrite(LASER_PIN, LASER_BRIGHTNESS);  // start the laser
}


void loop() {
  uint8_t fsp = random(MIN_FIRST_LINK_SERVO_POS, MAX_FIRST_LINK_SERVO_POS);     // set the first servo to a random position
  uint8_t ssp = random(MIN_SECOND_LINK_SERVO_POS, MAX_SECOND_LINK_SERVO_POS);   // set the second servo to a random position
  slowSetServosPos(fsp, ssp, 100, SERVO_DELAY);   // slow change of servo positions (blocking)
  //delay(500);
}


void slowSetServosPos(uint8_t flsPos, uint8_t slsPos, uint8_t steps, uint8_t dt)
{
  static uint8_t flsLastPos = BASE_FIRST_LINK_SERVO_POS;    // previous servo positions (start value centered)
  static uint8_t slsLastPos = BASE_SECOND_LINK_SERVO_POS;   //
  
  for(uint8_t i = 0; i < steps; i++) {      //  add each step a little to the current positions
    firstLinkServo.write(flsLastPos + i*(flsPos-flsLastPos)/steps); 
    secondLinkServo.write(slsLastPos + i*(slsPos-slsLastPos)/steps);
    delay(dt);  
  }
  flsLastPos = flsPos;  // update past positions
  slsLastPos = slsPos;
}
