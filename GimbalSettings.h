// GimbalSettings.h

#pragma once

#include <Arduino.h>

#define PITCH_PIN 26
#define YAW_PIN 13
#define ROLL_PIN 14

#define FREQUENCY 400
#define PITCH_CHANNEL 0
#define YAW_CHANNEL 1
#define ROLL_CHANNEL 2
#define RESOLUTION 8

#define CHANNEL_MIN 900
#define CHANNEL_MID_HIGH 1200
#define CHANNEL_MID_LOW 1008
#define CHANNEL_MAX 2100

#define SCR_WHL_MID 1500
#define SCR_WHL_MAX 2000
#define SCR_WHL_MIN 1100
#define SCR_WHL_LOW_LIMIT 900

#define MAX_PWM 240
#define MID_PWN_LOW 128
#define MID_PWM_HIGH 132
#define MIN_PWM 0

#define MAX_ANGLE 90
#define MID_ANGLE 0
#define MIN_ANGLE -90

#define MODE_SWITCH_DELAY 3000

#define PITCH_MAX_ANGLE 90
#define PITCH_MIN_ANGLE -90

#define YAW_MAX_ANGLE 180
#define YAW_MIN_ANGLE -180

#define ROLL_MID_PWM 130
#define ROLL_MAX_ANGLE 30
#define ROLL_MIN_ANGLE -30


class Gimbal {
private:
	enum modes { PITCH, ROLL, YAW };
	int mode;
	int pwm;
	int default_pwm;
	int last_pwm;
	uint32_t prev_millis;
	bool trigger;
	bool trigger2;
public:
	void init();
	void cam_button();
	void button_a();
	void button_b();
	void run();
};

