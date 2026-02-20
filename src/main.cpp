/**
* @file main.cpp
 * @brief Simple servo sweep demonstration for MG995 closed-loop axis control system.
 * @author Ashu pal
 * @date 2026-02-17
 *
 * @details
 * Demonstrates a basic sweep of a servo (MG995) from 0 to 180 degrees and back,
 * printing the current angle to Serial at each step. Intended as a simple test
 * program and starting point for closed-loop axis control development.
 */

#include <Arduino.h>
#include <Servo.h>

Servo myServo;
/**
 * @brief Arduino setup function.
 *
 * Initializes serial communication at 9600 baud, attaches the servo to pin 11,
 * and prints an initialization message over Serial.
 */
void setup() {
 Serial.begin(9600);

 myServo.attach(11);

 Serial.println("Servo initiate");
}
/**
 * @brief Arduino main loop.
 *
 * Sweeps the servo from 0 to 180 degrees in steps of 10 degrees, then back
 * from 180 to 0 degrees in steps of 10 degrees. At each step the current
 * angle is written to the servo and printed to the Serial monitor. Each step
 * pauses for 500 ms.
 */
void loop() {
 for (int i = 0; i <= 180; i += 10) {
  myServo.write(i);

  Serial.print("Servo Angle: ");
  Serial.println(i);

  delay(500);
 }

 for (int i = 180; i >= 0; i -= 10) {
  myServo.write(i);

  Serial.print("Servo Angle: ");
  Serial.println(i);

  delay(500);
 }
}