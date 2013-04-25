import json
from Robot import Robot


def handle_websocket(ws):
    """

    :param ws:
    """
    robot = Robot()

    while True:
        message = ws.receive()
        if message is None:
            break
        else:
            message = json.loads(message)

            command = message['command']

            if command == 'forward':
                robot.forward()

            if command == 'backward':
                robot.backward()

            if command == 'stop':
                robot.stop()

            if command == 'left':
                robot.left()

            if command == 'right':
                robot.right()

            r = "Command from you : %s" % message['command']
            ws.send(json.dumps({'output': r}))