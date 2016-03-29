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

#include "Arduino.h"
#include "SerialUltrasound.h"

/*
 * SerialUltrasound Constructor
 *
 * @param measurementUnits, the preferred measurement units
 * @param port, the serial connection to the SFR sensor
 * @param powerPin, the SRF sensor power pin.
 */
SerialUltrasound::SerialUltrasound(byte address, enum Units units,
		SoftwareSerial &conn) {
	_sensorAddress = address;
	_units = units;
	mySerial = &conn;
}

/*
 * Get a distance reading
 * @returns the distance in the requested measurement units.
 */
int SerialUltrasound::getDistance() {
	sendCommand(_sensorAddress, _units);
	delay(70);
	return getResponse(_sensorAddress);
}

/*
 * Send a command to the sensor.
 * @param address, the sensor address (0-15)
 * @param command, the command to send.
 */
void SerialUltrasound::sendCommand(byte address, int command) {
	mySerial->write(address);
	delayMicroseconds(100);
	mySerial->write(command);
	delayMicroseconds(100);
}

/*
 * Get a reading from the sensor.
 * @param address, the sensor address (0-15).
 * @return distance of last ranging, in the unit specified.
 */
int SerialUltrasound::getResponse(byte address) {
	sendCommand(address, 0x5E);	// Get Range
	while (mySerial->available() < 2) {
		// waitin' for data to arrive
		delay(100);
	}
	int result = mySerial->read() << 8;	// read high byte
	result |= mySerial->read();			// read low byte
	return result;
}

