var PiRover	= function(options) {

    this.websocket = false;

    this.stopped = true;
    this.isMovingForward = false;
    this.isMovingBackward = false;
    this.currentSpeed = 0;

    this.joystick = null;

    this.debug = false;

    this.lookingDirectionDegrees = 90;
    this.lookMode = false;

    this.options = options;

    this.init = function() {

        var self = this;

        if ("WebSocket" in window) {
            this.websocket = new WebSocket("ws://"+document.domain+":5000/websocket");
            this.websocket.onmessage = function (msg) {
                var message = JSON.parse(msg.data);
                document.getElementById('serverFeedback').innerHTML = message.output;
            };

            // Cleanly close websocket when unload window
            window.onbeforeunload = function () {
                self.websocket.onclose = function () {
                }; // disable onclose handler first
                self.websocket.close()
            };
        } else {
            this.log("WebSocket are not supported by your browsers but required to communicate with the rover..");
        }

        // Cleanly close websocket when unload window
        window.onbeforeunload = function () {
            self.websocket.onclose = function () {
            }; // disable onclose handler first
            self.websocket.close()
        };

        this.joystick = new VirtualJoystick({
            container	: document.getElementById('joystick'),
            mouseSupport	: true
        });

        setInterval(function() { self.handle(); }, 500);
        setInterval(function() { self.checkIfIsStopped(false); }, 150);
    }

    this.handle = function () {

        var inputFeedback = "";
        var outputEl = document.getElementById('inputFeedback');

        if (this.checkIfIsStopped(true)) {
            var inputFeedback = "stopped";
        } else {
            if (this.joystick.up() && this.lookMode == false) {
                var argument = this.convertStickDistanceToArgument(false, this.joystick.deltaY(), this.joystick._container);

                if (this.isMovingForward == false || (this.isMovingForward == true && this.currentSpeed != argument)) {
                    this.websocket.send(JSON.stringify({
                        'command': 'forward',
                        'argument': argument
                    }));
                    inputFeedback += inputFeedback == "" ? "" : " & ";
                    inputFeedback += "forward (" + argument + "%)";

                    this.isMovingForward = true;
                    this.currentSpeed = argument;
                }
            }

            if (this.joystick.down() && this.lookMode == false) {
                var argument = this.convertStickDistanceToArgument(false, this.joystick.deltaY(), this.joystick._container);

                if (this.isMovingBackward == false || (this.isMovingBackward == true && this.currentSpeed != argument)) {
                    this.websocket.send(JSON.stringify({
                        'command': 'backward',
                        'argument': argument
                    }));
                    inputFeedback += inputFeedback == "" ? "" : " & ";
                    inputFeedback += "backward (" + argument + "%)";

                    this.isMovingBackward = false;
                    this.currentSpeed = argument;
                }
            }

            if (this.joystick.left()) {
                var argument = this.convertStickDistanceToArgument(false, this.joystick.deltaX(), this.joystick._container);

                if (this.lookMode)
                {
                    var degree = this.map(argument, 0, 100, 90, 0);

                    if (this.lookingDirectionDegrees != degree) {
                        this.lookingDirectionDegrees = degree;

                        this.websocket.send(JSON.stringify({
                            'command': 'look',
                            'argument': degree
                        }));
                    }

                    inputFeedback += "look left (" + argument + "%)";
                }
                else
                {
                    this.websocket.send(JSON.stringify({
                        'command': 'left',
                        'argument': argument
                    }));

                    inputFeedback += inputFeedback == "" ? "" : " & ";
                    inputFeedback += "left (" + argument + "%)";
                }
            }

            if (this.joystick.right()) {
                var argument = this.convertStickDistanceToArgument(false, this.joystick.deltaX(), this.joystick._container);

                if (this.lookMode)
                {
                    var degree = this.map(argument, 0, 100, 90, 180);

                    if (this.lookingDirectionDegrees != degree) {
                        this.lookingDirectionDegrees = degree;

                        this.websocket.send(JSON.stringify({
                            'command': 'look',
                            'argument': degree
                        }));
                    }

                    inputFeedback += "look right (" + argument + "%)";
                }
                else
                {
                    this.websocket.send(JSON.stringify({
                        'command': 'right',
                        'argument': argument
                    }));

                    inputFeedback += inputFeedback == "" ? "" : " & ";
                    inputFeedback += "right (" + argument + "%)";
                }
            }
        }

        outputEl.innerHTML = '<b>Input:</b> ' + inputFeedback;
    }

    this.turnOff = function() {
        return this.websocket.send(JSON.stringify({
            'command': 'turnoff'
        }));
    }

    this.getBatteryLife = function() {
        return this.websocket.send(JSON.stringify({
            'command': 'getBatteryLife'
        }));
    }

    this.measureDistance = function() {
        return this.websocket.send(JSON.stringify({
            'command': 'measureDistance'
        }));
    }

    this.checkIfIsStopped = function checkIfIsStopped(ignoreStoppedFlag) {

        if (ignoreStoppedFlag == false && this.stopped == true) {
            return true;
        }

        if (!this.joystick.up() && !this.joystick.down() && !this.joystick.left() && !this.joystick.right()) {

            if (this.lookMode && this.lookingDirectionDegrees != 90) {
                this.websocket.send(JSON.stringify({
                    'command': 'look',
                    'argument': 90
                }));
                this.lookingDirectionDegrees = 90;
            } else {
                if (this.stopped == false) {
                    this.websocket.send(JSON.stringify({
                        'command': 'stop',
                        'argument': 0
                    }));
                }

                this.stopped = true;
                return true;
            }
        }

        this.stopped = false;
        return false;
    }

    this.convertStickDistanceToArgument = function convertStickDistanceToArgument(xValue, yValue, container) {
        var result = 0;

        if (xValue) {
            xValue = xValue * 6;
            result = xValue / (container.offsetWidth/100);
        } else if(yValue) {
            yValue = yValue * 2;
            result = yValue / (container.offsetHeight/100);
        }

        if (result < 0) {
            result *= -1;
        }
        if (result > 100) {
            result = 100;
        }
        result = Math.round(result);

        return result;
    }

    this.map = function (value, range1From, range1To, range2From, range2To) {
        return range2From + ((range2To - range2From) / (range1To - range1From)) * (value - range1From)
    }

    this.log = function(message) {
        if (typeof console == "object") {
            console.log(message);
        }
    }
}