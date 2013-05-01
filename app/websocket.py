import json
from Robot import Robot


def handle_websocket(ws):
    robot = Robot()

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

            if hasattr(robot, command):
                result = getattr(robot, command)(argument)
            else:
                result = "Unknown command %s" % command

            r = "Command from you : %s, result: %s" % (message['command'], result)
            ws.send(json.dumps({'output': r}))