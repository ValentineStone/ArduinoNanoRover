#include <Arduino.h>
#include <IRremote.h>

const auto MOTOR_A_FW  = A0;
const auto MOTOR_A_BW  = A1;
const auto MOTOR_B_FW  = A2;
const auto MOTOR_B_BW  = A3;
const auto RECV_PIN = DD5;

const auto UP_CMD = 24;
const auto RIGHT_CMD = 90;
const auto LEFT_CMD = 8;
const auto DOWN_CMD = 82;
const auto BREAK_CMD = 28;

const auto speed = 128;

IRrecv reciever(RECV_PIN);

void setup() {
  /*
  pinMode(MOTOR_A_FW, OUTPUT);
  pinMode(MOTOR_A_BW, OUTPUT);
  pinMode(MOTOR_B_FW, OUTPUT);
  pinMode(MOTOR_B_BW, OUTPUT);
  analogWrite(MOTOR_A_FW, speed);
  analogWrite(MOTOR_A_BW, 0);
  analogWrite(MOTOR_B_FW, speed);
  analogWrite(MOTOR_B_BW, 0);
  delay(10000);
  analogWrite(MOTOR_A_FW, 0);
  analogWrite(MOTOR_B_FW, 0);
  */
  Serial.begin(9600);
  reciever.enableIRIn();
  Serial.println("Hello, world!");
  
}

uint64_t last_command = 0;
void loop() {
  if (reciever.decode()) {
    switch (reciever.decodedIRData.command) {
      case UP_CMD: {
        analogWrite(MOTOR_A_FW, speed);
        analogWrite(MOTOR_A_BW, 0);
        analogWrite(MOTOR_B_FW, speed);
        analogWrite(MOTOR_B_BW, 0);
        last_command = millis();
        break;
      }
      case DOWN_CMD: {
        analogWrite(MOTOR_A_FW, 0);
        analogWrite(MOTOR_A_BW, speed);
        analogWrite(MOTOR_B_FW, 0);
        analogWrite(MOTOR_B_BW, speed);
        last_command = millis();
        break;
      }
      case RIGHT_CMD: {
        analogWrite(MOTOR_A_FW, 0);
        analogWrite(MOTOR_A_BW, speed);
        analogWrite(MOTOR_B_FW, speed);
        analogWrite(MOTOR_B_BW, 0);
        last_command = millis();
        break;
      }
      case LEFT_CMD: {
        analogWrite(MOTOR_A_FW, speed);
        analogWrite(MOTOR_A_BW, 0);
        analogWrite(MOTOR_B_FW, 0);
        analogWrite(MOTOR_B_BW, speed);
        last_command = millis();
        break;
      }
      case BREAK_CMD: {
        analogWrite(MOTOR_A_FW, 0);
        analogWrite(MOTOR_A_BW, 0);
        analogWrite(MOTOR_B_FW, 0);
        analogWrite(MOTOR_B_BW, 0);
        last_command = millis();
        break;
      }
    }
    reciever.resume();
  }
  if (millis() - last_command > 1000) {
    analogWrite(MOTOR_A_FW, 0);
    analogWrite(MOTOR_A_BW, 0);
    analogWrite(MOTOR_B_FW, 0);
    analogWrite(MOTOR_B_BW, 0);
  }
}