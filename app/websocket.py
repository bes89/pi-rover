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

            if hasattr(pirover, command):
                result = getattr(pirover, command)(argument)
            else:
                result = "Unknown command %s" % command

            r = "Command from you : %s (%s%%), result: %s" % (command, argument, result)
            ws.send(json.dumps({'output': r}))
