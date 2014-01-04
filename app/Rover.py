import serial
import commands


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

    def look(self, inDegrees):
        return self.sendCommandToArduino('look', inDegrees)

    def measureDistance(self, ignoredArgument):
        return self.sendCommandToArduino('measureDistance')

    def getBatteryLife(self, ignoredArgument):
        return self.sendCommandToArduino('getBatteryLife')

    def getCpuTemp(self, ignoredArgument):
        tempFile = open('/sys/class/thermal/thermal_zone0/temp')
        cpu_temp = tempFile.read()
        tempFile.close()
        return float(cpu_temp)/1000
        # Uncomment the next line if you want the temp in Fahrenheit
        #return float(1.8*cpu_temp)+32

    def getGpuTemp(self, ignoredArgument):
        gpu_temp = commands.getoutput('/opt/vc/bin/vcgencmd measure_temp').replace('temp=', '').replace('\'C', '')
        return float(gpu_temp)
        # Uncomment the next line if you want the temp in Fahrenheit
        # return float(1.8* gpu_temp)+32

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



