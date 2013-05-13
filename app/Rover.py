import serial


class Rover:
    serialInterface = None

    def __init__(self):
        self.serialInterface = serial.Serial('/dev/ttyACM0', 9600)

    def forward(self, speedInPercentage):
        return self.sendCommandToArduino('forward', speedInPercentage)

    def backward(self, speedInPercentage):
        return self.sendCommandToArduino('backward', speedInPercentage)

    def stop(self, ignoredArgument):
        return self.sendCommandToArduino('stop')

    def left(self, speedInPercentage):
        return self.sendCommandToArduino('left', speedInPercentage)

    def right(self, speedInPercentage):
        return self.sendCommandToArduino('right', speedInPercentage)

    def sendCommandToArduino(self, cmd, arg=None):
        if self.serialInterface.writable():
            if arg is None:
                arg = 0

            print "cmd %s with %s ok" % (cmd, arg)
            self.serialInterface.write(str(cmd) + ':' + str(arg))
            return self.serialInterface.readline()
        else:
            print "cmd %s with %s failed" % (cmd, arg)
            return "failed"
