import serial


class Robot:
    serialInterface = None

    def __init__(self):
        self.serialInterface = serial.Serial('/dev/ttyACM0', 9600)

    def forward(self, speedInPercentage):
        print " forward"
        self.serialInterface.write('forward:' + str(speedInPercentage))

    def backward(self, speedInPercentage):
        print " backward"
        self.serialInterface.write('backward:' + str(speedInPercentage))

    def turnAround(self):
        print " turn around"
        for x in range(1, 5):
            self.serialInterface.write('left:100')

    def stop(self, ignoredArgument):
        print " stop"
        self.serialInterface.write('stop')

    def left(self, speedInPercentage):
        print " left"
        self.serialInterface.write('left:' + str(speedInPercentage))

    def right(self, speedInPercentage):
        print " right"
        self.serialInterface.write('right:' + str(speedInPercentage))
