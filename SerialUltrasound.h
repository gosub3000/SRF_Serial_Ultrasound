/*
 * Library for reading from Devantech SRF Ultrasound Sensors.
 *
 * Copyright (C) 2015  Chris Collins <gosub3000@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef SerialUltrasound_h
#define SerialUltrasound_h

#if (ARDUINO >= 100)
#include "Arduino.h"
#ifndef __SAM3X8E__  // Arduino Due doesn't support SoftwareSerial
#include <SoftwareSerial.h>
#endif
#else
#include "WProgram.h"
#include <NewSoftSerial.h>
#endif

enum Units {
	microseconds = 0x52, centimeters = 0x51, inches = 0x50
};

class SerialUltrasound {
public:
	SerialUltrasound(byte address, enum Units units, SoftwareSerial &conn);
	int getDistance();
private:
	void sendCommand(byte address, int command);
	int getResponse(byte address);

	byte _sensorAddress = 0x00;
	int _units;
	SoftwareSerial *mySerial;
};

#endif
