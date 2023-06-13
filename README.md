# Garage-Range-Detector
Garage Range Detector (GRD) uses an Arduino Nano IOT 33 with an ultrasonic sensor and a flashing LED. Gives the driver a heads up on if they park their car too far or too close from the sensor

## distance_over_udp.ino
Actual software build used on the Arduino Nano to:
* Connect to a network
* Check distance between sensor and car
* Transmit distance data over UDP to remote computer

## client_udp.py
Simple UDP client using Python to receive the Arduino's range data. Helpful for troubleshooting when not connected over serial connection

## ultrasonic_led.ino
A stripped down proof-of-concept that strictly runs on the Arduino (no networking or transmission of data)
