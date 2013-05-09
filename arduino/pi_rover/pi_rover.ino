#include <AFMotor.h>
#include <NewPing.h>

#define runEvery(t) for (static typeof(t) _lasttime;\
                         (typeof(t))((typeof(t))millis() - _lasttime) > (t);\
                         _lasttime += (t))

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

#define TRIGGER_PIN  2
#define ECHO_PIN     13
#define MAX_DISTANCE 200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

int motorSpeed = 100;
bool isMovingForward = false;
bool isMovingBackward = false;
bool safetyDriveMode = true;

String input = "";
  
void setup()
{
  Serial.begin(9600);
  Serial.print("Ready\n");
}

void loop()
{
  char character;
  
  while(Serial.available()) {
    character = Serial.read();    
    input.concat(character);
    delay(2);
  }

  if (input != "") {
    String result = handleCommand(input);
    Serial.print(result + "\n");
    input = "";
  }

  if (safetyDriveMode) {
    int checkDistanceInterval = map(
      motorSpeed,
      0, 255,
      500, 0
    );
    
    runEvery(checkDistanceInterval) {
      if (isMovingForward && getDistanceInCm() < 15) {
          halt(0);
      }
    }
  }
}

String getCommandFromInput(String input) {
  String result = input;
  int positionOfColon = input.indexOf(':');
  
  if (positionOfColon)
  {
    result = input.substring(0, positionOfColon);
  }
 
  return result; 
}

int getArgumentFromInput(String input) {
  int result = -1;
  int positionOfColon = input.indexOf(':');
  
  if (positionOfColon)
  {
    int length = input.length() - positionOfColon;
    String argument = input.substring(positionOfColon + 1);
    result = argument.toInt();
  }
 
  return result; 
}

void setMotorSpeed(int speedInPercentage) {
  motorSpeed = map(
    speedInPercentage,
    0, 100,
    0, 255
  );
  
  Serial.print(String("Set speed to ") + motorSpeed + " ("+ speedInPercentage +"%)\n");
}


String handleCommand(String input) {
  String result;
  
  String command = getCommandFromInput(input);
  int argument = getArgumentFromInput(input);
  
  if(command == "battery") {
    result = checkBatteryStatus(argument);
  } else if(command == "distance") {
    result = measureDistance(argument);
  } else if(command == "forward") {
    result = forward(argument);
  } else if(command == "backward") {
    result = backward(argument);
  } else if(command == "left") {
    result = left(argument);
  } else if(command == "right") {
    result = right(argument);
  } else if(command == "stop") {
    result = halt(argument);
  } else {
    result = "unknown command: " + command + ", arg: " + argument;
  }
    
  return result;
}

String forward(int speedInPercentage)
{
  if (speedInPercentage > 0)
  {
    setMotorSpeed(speedInPercentage);
  }
  
  isMovingForward = true;
  
  turnMotorsOn();
  
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  
  return "ok";
}

String backward(int speedInPercentage)
{
  if (speedInPercentage > 0)
  {
    setMotorSpeed(speedInPercentage);
  }
  
  isMovingBackward = true;
  
  turnMotorsOn();
  
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  
  return "ok";
}

String halt(int argument)
{
  int currentMotorSpeedInPercentage = map(
    motorSpeed,
    0, 255,
    0, 100
  );
  
  if (isMovingForward)
  {
    backward(80);
    delay(currentMotorSpeedInPercentage * 2);
  }
  else if(isMovingBackward)
  {
    forward(80);
    delay(currentMotorSpeedInPercentage * 2);
  }
  
  turnMotorsOff();
  
  isMovingForward = false;
  isMovingBackward = false;
  
  return "ok";
}



String left(int speedInPercentage)
{
  int currentMotorSpeed = motorSpeed;
  setMotorSpeed(100);
  
  turnMotorsOn();
  
  bool turnToTheLeftSharply = speedInPercentage > 25;

  if (turnToTheLeftSharply == false)
  {
    motor1.setSpeed(0);
    motor4.setSpeed(0);
  }

  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
  
  delay(speedInPercentage * 2);

  motorSpeed = currentMotorSpeed;
  
  if (isMovingForward) {
    forward(0);
  } else if (isMovingBackward) {
    backward(0); 
  } else {
    turnMotorsOff();
  }

  return "ok";
}

String right(int speedInPercentage)
{
  int currentMotorSpeed = motorSpeed;
  setMotorSpeed(100);
  
  turnMotorsOn();

  bool turnToTheRightSharply = speedInPercentage > 25;

  if (turnToTheRightSharply == false)
  {
    motor2.setSpeed(0);
    motor3.setSpeed(0);
  }

  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);

  delay(speedInPercentage * 2);

  motorSpeed = currentMotorSpeed;

  if (isMovingForward) {
    forward(0);
  } else if (isMovingBackward) {
    backward(0); 
  } else {
    turnMotorsOff();
  }

  return "ok";
}

String checkBatteryStatus(int argument)
{
  int counter = 0;
  for (int i = 0; i <= 3; i++) {
    int value = analogRead(0);
    if (value < 10) {
      counter = counter + 1;
    }
      
    delay(1000);
  }
  
  String result;
  
  if (counter > 2) {
    result = "low";
  } else {
    result = "ok";
  }
  
  return result;
}

void turnMotorsOff()
{
  motor1.setSpeed(0);
  motor2.setSpeed(0);
  motor3.setSpeed(0);
  motor4.setSpeed(0);
}

void turnMotorsOn()
{
  motor1.setSpeed(motorSpeed);
  motor2.setSpeed(motorSpeed);
  motor3.setSpeed(motorSpeed);
  motor4.setSpeed(motorSpeed);
}

String measureDistance(int argument) {
  return String("Ping: ") + String(getDistanceInCm()) + String("cm");
}

int getDistanceInCm() {
  unsigned int uS = sonar.ping();
  return uS / US_ROUNDTRIP_CM;
}
