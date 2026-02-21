/*
 * A library for controlling servo motors on Arduino.
 *
 * Copyright (c) 2009-2014 Michael Margolis.  All right reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef Servo_h
#define Servo_h

#include <inttypes.h>

/*
 * Defines for 16-bit timers used with Servo library
 *
 * If _useTimerX is defined then TimerX is used for the servo library.
 * (Note that Timer1 is always used if there is no other timer defined.)
 *
 * The timers are identified by a number from 1 to 5, as follows:
 *
 *   Timer1:   16-bit timer on ATmega8/168/328/1280/2560.
 *   Timer3:   16-bit timer on ATmega1280/2560.
 *   Timer4:   16-bit timer on ATmega1280/2560.
 *   Timer5:   16-bit timer on ATmega1280/2560.
 *
 * The appropriate timer is on by default for ATmega8/168/328/1280/2560 chips.
 * For other chips, you must define _useTimerX in your sketch, where X is
 * a number from 1 to 5.
 */

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#define _useTimer5  // default to timer5 on Mega
#else
#define _useTimer1  // default to timer1 on others
#endif

// The following constants are used to calculate pulse widths in microseconds.
// A full-width pulse is equivalent to 20000 microseconds.
#define MIN_PULSE_WIDTH       544     // the shortest pulse sent to a servo
#define MAX_PULSE_WIDTH      2400     // the longest pulse sent to a servo
#define DEFAULT_PULSE_WIDTH  1500     // default pulse width when servo is attached
#define REFRESH_INTERVAL    20000     // minimum time to refresh servos in microseconds

#define SERVOS_PER_TIMER       12     // the maximum number of servos controlled by one timer
#define MAX_SERVOS   (_Nbr_16_bit_timers  * SERVOS_PER_TIMER)

#define INVALID_SERVO         255     // flag indicating an invalid servo index

typedef struct  {
  uint8_t nbr        :6 ;  // a pin number from 0 to 63
  uint8_t isActive   :1 ;  // true if this channel is enabled, pin not pulsed if false
} ServoPin_t   ;

typedef struct {
  ServoPin_t Pin;
  volatile unsigned int ticks;
} servo_t;

class Servo
{
public:
  Servo();
  uint8_t attach(int pin);           // attach the given pin to the next free channel, sets pinMode, returns channel number or 0 if failure
  uint8_t attach(int pin, int min, int max); // as above but also sets min and max values for writes.
  void detach();
  void write(int value);             // if value is < 200 its treated as an angle, otherwise as pulse width in microseconds
  void writeMicroseconds(int value); // Write pulse width in microseconds
  int read();                        // returns current pulse width as an angle between 0 and 180 degrees
  int readMicroseconds();            // returns current pulse width in microseconds for this servo (was read_us() in first release)
  bool attached();                   // return true if this servo is attached, otherwise false
private:
   uint8_t servoIndex;               // index into the channel data for this servo
   int8_t min;                       // minimum is this value times 4 added to MIN_PULSE_WIDTH
   int8_t max;                       // maximum is this value times 4 added to MAX_PULSE_WIDTH
};

#endif
