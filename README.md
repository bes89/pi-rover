# PiRover

The PiRover itself is a robot based on the Raspberry Pi and Arduino UNO.
This repository provides a ready-to-use micro-framework based on Python, C++, JavaScript and HTML5.

## Features

* Communication over Wifi
* A user friendly and beautiful web-interface - no app is needed!
* Video streaming in real time (up to 1080p@30fps - yes, its full hd!)
* Based on arch linux - no limits

## Required Hardware

* Raspberry Pi with the Camera Module
* USB Power Bank: Choose carefully! It should provide a 5V 2A or at least 1.5A usb out to power up the Raspberry Pi.
The Raspberry Pi needs a lot of current for the camera module, wifi, and arduino is also powered by the Raspberry Pi
that's why choose a powerbank with at least 5000mAh! Ideally it has some status led so we can read the battery life with a photo resistor.
* Photo resistor + 10k Resistor: To read the battery life of your powerbank
* micro usb cable 0.6ft: To connect the powerbank with Rapsberry Pi
* usb A-to-B cable 0.6ft: To connect the Raspberry Pi with the Arduino
* Arduino Uno or Mega
* Motor Shield (for example: Adafruit: http://www.adafruit.com/products/81)
* LiPo Battery (for example: Hacker LiPo Akku 11.1 V / 1800 mAh (30 C))
* Chassis with DC Motors and wheels: just google "robot chassis 4wd"
* Servo Motor: for a 180° view
* UltraSonic Range Finder: to measure distance
* one LED: to use it as a status led
* some wire

## How to install

### Step 1: Checkout the project locally

```bash
git clone git@github.com:bes89/pi-rover.git
```

### Step 2: Get your Arduino ready

After you checked out the project locally install these two dependencies:

```bash
mkdir ~/sketchbook/libraries
git clone https://github.com/adafruit/Adafruit-Motor-Shield-library
git clone https://github.com/fmbfla/Arduino.git
```

Then open the arduino/pi_rover/pi_rover.ino in your Arduino IDE and upload it to your Arduino.

The Arduino is now ready.

### Step 3: Checkout the project remotely on your raspberry pi

ssh to your raspi and then:

```bash
git clone git@github.com:bes89/pi-rover.git
cd pi-rover/
virtualenv-2.7 venv
source venv/bin/activate
./venv/bin/pip-2.7 install -r requirements.txt
./venv/bin/python2.7 runserver.py
```

Open this in browser:
```
http://<ip-of-your-raspi>:5000/
```

## Contribute

## TODOs / Planned Features

- lag free video streaming to the browser (for now we are using netcat, tried vlc, ffmpeg, gstreamer and mjpeg-stream - all with lags >2s)
- run with the fast python interpreter "pypy" (gevent is here the problem)
- implement json rpc over websockets to be able to call functions remotely in javascript (https://github.com/brainrape/jsonrpcws)
- handle wifi connections directly in python
- create a basis to work with opencv
