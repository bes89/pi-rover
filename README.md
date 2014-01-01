# PiRover

The PiRover itself is a robot based on the Raspberry Pi and Arduino UNO.
This repository provides a ready-to-use micro-framework based on Python, C++, JavaScript and HTML5.

## Features

* Communication over Wifi
* A user friendly and beautiful web-interface - no app is needed!
* Video streaming in real time (up to 1080p@30fps - yes, its full hd!)
* Based on arch linux - no limits

## Required Hardware

* 1x Raspberry Pi
* 1x Camera Module for the Raspberry Pi
* 1x Arduino UNO
* 1x USB A-to-B (short)
* 1x Micro USB (short)
* 1x Motor Shield
* 1x Photo resistor
* 1x USB Power Bank
* 1x LiPo Battery
* 1x Chassis with DC Motors and wheels
* 1x Servo Motor
* 1x UltraSonic Range Finder
* 1x LED
* 2x 10k Resistor
* 7x wire

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

- [ ] lag free video streaming to the browser (for now we are using netcat, tried vlc, ffmpeg, gstreamer and mjpeg-stream - all with lags >2s)
- [ ] run with the fast python interpreter "pypy" (gevent is here the problem)
- [ ] implement json rpc over websockets to be able to call functions remotely in javascript (https://github.com/brainrape/jsonrpcws)
- [ ] handle wifi connections directly in python
- [ ] create a basis to work with opencv
