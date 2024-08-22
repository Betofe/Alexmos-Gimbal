// 
// 
// 

#include "GimbalSettings.h"
#include "Globals.h"

void Gimbal::init() {

	ledcAttachPin(PITCH_PIN, PITCH_CHANNEL);
	ledcAttachPin(YAW_PIN, YAW_CHANNEL);
	ledcAttachPin(ROLL_PIN, ROLL_CHANNEL);

	ledcSetup(PITCH_CHANNEL, FREQUENCY, RESOLUTION);
	ledcSetup(YAW_CHANNEL, FREQUENCY, RESOLUTION);
	ledcSetup(ROLL_CHANNEL, FREQUENCY, RESOLUTION);

	trigger = false;
	trigger2 = false;
	mode = YAW;
	pwm = 132;
	default_pwm = 132;
	last_pwm = 132;
	prev_millis = 0;
}

void Gimbal::cam_button() {
	if (channel_pwms[CHAN9_INDEX] > CHANNEL_MID_HIGH && channel_pwms[CHAN9_INDEX] <= CHANNEL_MAX) {
		trigger = true;
	}
	if (channel_pwms[CHAN9_INDEX] > 0 && channel_pwms[CHAN9_INDEX] < CHANNEL_MID_HIGH) {
		trigger2 = true;
	}
}

void Gimbal::button_a() {
	if (channel_pwms[CHAN11_INDEX] > CHANNEL_MID_HIGH && channel_pwms[CHAN11_INDEX] <= CHANNEL_MAX) {
		pwm = last_pwm;
		if (pwm < 195) {
			pwm += 1;
			last_pwm = pwm;
			Serial.println(pwm);
			delay(50);
		}
		else {
			pwm = 132;
		}
	}
	else if (channel_pwms[CHAN11_INDEX] > 0 && channel_pwms[CHAN11_INDEX] < CHANNEL_MID_HIGH) {
		pwm = default_pwm;
	}
}

void Gimbal::button_b() {
	if (channel_pwms[CHAN12_INDEX] > CHANNEL_MID_HIGH && channel_pwms[CHAN12_INDEX] <= CHANNEL_MAX) {
		pwm = last_pwm;
		if (pwm > 85) {
			pwm -= 1;
			last_pwm = pwm;
			Serial.println(pwm);
			delay(50);
		}
		else {
			pwm = 132;
		}
	}

}

void Gimbal::run() {
	//Serial.println(channel_pwms[CHAN11_INDEX]);
	cam_button();
	if (trigger == true && trigger2 == true) {
		switch (mode) {
		case PITCH:
			Serial.println("ROLL SET");
			mode = ROLL;
			delay(MODE_SWITCH_DELAY);
			break;
		case ROLL:
			Serial.println("YAW SET");
			mode = YAW;
			delay(MODE_SWITCH_DELAY);
			break;
		case YAW:
			Serial.println("PITCH SET");
			mode = PITCH;
			delay(MODE_SWITCH_DELAY);
			break;
		default:
			delay(MODE_SWITCH_DELAY);
			break;
		}
		trigger = false;
		trigger2 = false;
	}
	button_a();
	button_b();
	if (mode == PITCH) {
		ledcWrite(PITCH_CHANNEL, pwm);
	}
	else if (mode == ROLL) {
		if (pwm <= 132 && pwm >= 129) {
			ledcWrite(ROLL_CHANNEL, ROLL_MID_PWM);
		}
		else {
			ledcWrite(ROLL_CHANNEL, pwm);
		}
	}
	else if (mode == YAW) {
		ledcWrite(YAW_CHANNEL, pwm);
	}
}