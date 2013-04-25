import serial


class Robot:
    serialInterface = None

    def __init__(self):
        self.serialInterface = serial.Serial('/dev/ttyACM0', 9600)

    def speed(self, speedInPercent):
        speed = speedInPercent

    def forward(self):
        print " forward"
        self.serialInterface.write('forward')

    def backward(self):
        print " backward"
        self.serialInterface.write('backward')

    def turnAround(self):
        print " turn around"
        self.serialInterface.write('left')
        self.serialInterface.write('left')
        self.serialInterface.write('left')
        self.serialInterface.write('left')

    def stop(self):
        print " stop"
        self.serialInterface.write('stop')

    def left(self):
        print " left"
        self.serialInterface.write('left')

    def right(self):
        print " right"
        self.serialInterface.write('right')
