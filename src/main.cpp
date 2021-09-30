#include <Arduino.h>
#include <PPMReader.h>

const auto MOTOR_A_FW  = 11; // A0;
const auto MOTOR_A_BW  = 10; // A1;
const auto MOTOR_B_FW  =  9; // A2;
const auto MOTOR_B_BW  =  6; // A3;

const auto PPM_PIN  = 3;
const auto PPM_COUNT = 8;
PPMReader ppm(PPM_PIN, PPM_COUNT);

const auto SPEED_CH = 3;
const auto STEER_CH = 4;
// ch3 2000 - forward
// ch3 1000 - back
// ch1 2000 - right
// ch1 1000 - left

const uint8_t MAX_PWM_SPEED = 255;

uint8_t conv(int16_t v) {
  if (v >= 500) return MAX_PWM_SPEED;
  else if (v <= 0) return 0;
  else return v / 500. * MAX_PWM_SPEED;
}

void drive(uint16_t speed_pwm, uint16_t steer_pwm) {
  if (
    speed_pwm < 1000 ||
    speed_pwm > 2000 ||
    steer_pwm < 1000 ||
    steer_pwm > 2000
  ) return;

  int16_t steer = steer_pwm - 1500;
  int16_t speed = speed_pwm - 1500;

  int16_t speed_r = speed - steer;
  int16_t speed_l = speed + steer;
  
  analogWrite(MOTOR_A_FW, conv(+speed_r));
  analogWrite(MOTOR_B_FW, conv(+speed_l));
  analogWrite(MOTOR_A_BW, conv(-speed_r));
  analogWrite(MOTOR_B_BW, conv(-speed_l));
}

void setup() {
  pinMode(MOTOR_A_BW, OUTPUT);
  pinMode(MOTOR_B_FW, OUTPUT);
  pinMode(MOTOR_A_BW, OUTPUT);
  pinMode(MOTOR_B_BW, OUTPUT);
  analogWrite(MOTOR_A_FW, 0);
  analogWrite(MOTOR_B_FW, 0);
  analogWrite(MOTOR_A_BW, 0);
  analogWrite(MOTOR_B_BW, 0);
}

void loop() {
  drive(
    ppm.latestValidChannelValue(SPEED_CH, 1500), 
    ppm.latestValidChannelValue(STEER_CH, 1500)
  );
}