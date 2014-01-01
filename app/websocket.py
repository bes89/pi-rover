import json
from Rover import Rover


def handle_websocket(ws):
    pirover = Rover()

    while True:
        message = ws.receive()
        if message is None:
            break
        else:
            message = json.loads(message)

            command = message['command']
            argument = -1

            if 'argument' in message:
                argument = message['argument']

            if message == 'turnoff':
                command = "/sbin/shutdown -P 2"
                import subprocess
                process = subprocess.Popen(command.split(), stdout=subprocess.PIPE)
                result = process.communicate()[0]

            if hasattr(pirover, command):
                result = getattr(pirover, command)(argument)
            else:
                result = "Unknown command %s" % command

            r = "Command from you : %s (%s%%), result: %s" % (command, argument, result)
            ws.send(json.dumps({'output': r}))
