# CCollins Serial Ultrasound Library

This library is intended for addressing SRFxx Ultrasonic Distance Rangers using
serial communications.

This library will take a SoftwareSerial object initialised for these settings, 
and allow distance ranging using it.  

See the included example.

## Pin Connections
For example, using a SRF02, connect the pins as follows:

- SRF02 -> Arduino
- 5v Vcc -> 5V
- Rx -> 10(TX)
- Tx -> 11(RX)
- Mode -> GND
- 0v Ground -> GND


