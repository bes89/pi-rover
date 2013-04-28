#include <AFMotor.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

int motorSpeed = 200;

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
  }

  if (input != "") {
    String result = handleCommand(input);
    Serial.print(result + "\n");
    input = "";
  }
  
  delay(100);
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


String handleCommand(String input) {
  String result;
  
  String command = getCommandFromInput(input);
  int argument = getArgumentFromInput(input);
  
  if(command == "check battery status") {
    result = checkBatteryStatus(argument);
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

String forward(int speedInP87ercentage)
{
  turnMotorsOn();
  
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  
  return "ok";
}

String backward(int argument)
{
  turnMotorsOn();
  
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  
  return "ok";
}

String halt(int argument)
{
  turnMotorsOff();
  
  return "ok";
}



String left(int argument)
{
  turnMotorsOn();

  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);

  delay(250);

  turnMotorsOff();

  return "ok";
}

String right(int argument)
{
  turnMotorsOn();

  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);

  delay(250);

  turnMotorsOff();

  return "ok";
}

String checkBatteryStatus(int argument)
{
  return "battery status is " + String(random(0, 1));
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
