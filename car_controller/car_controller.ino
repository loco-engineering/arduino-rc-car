#include <esp_now.h>
#include <WiFi.h>
#include <ESP32Servo.h>

Servo myservo;  // create servo object to control a servo
// 16 servo objects can be created on the ESP32

int pos = 0;  // variable to store the servo position
int servoPin = 6;

//DC motor
const int DC_MOTOR_1_PWM_PIN = 2;
const int DC_MOTOR_1_FORWARD_PIN = 12;
const int DC_MOTOR_1_BACK_PIN = 13;
const int DC_MOTOR_1_STANDBY_PIN = 11;

int current_steering_angle = 90;

const int freq = 3000;
const int pwmChannel = 0;
const int resolution = 8;
int dutyCycle = 200;

void i_received_data_from_remote(const uint8_t *mac, const uint8_t *incomingData, int len) {

      digitalWrite(38, 1);  //standby direction

  /*Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Message type: ");
  Serial.println(incomingData[0]);
  Serial.print("X: ");
  Serial.println(incomingData[1]);
  Serial.print("Y: ");
  Serial.println(incomingData[2]);*/
  if (incomingData[1] > 130) {
    int pwm = (double)(255.0 / 70.0) * (double)(incomingData[1] - 130);
    if (pwm > 240){
      pwm = 240;
    }
    Serial.print("Back: ");
    Serial.println(pwm);

    analogWrite(DC_MOTOR_1_FORWARD_PIN, 0);  //set forward direction
    analogWrite(DC_MOTOR_1_BACK_PIN, pwm);     // back for a motor
    digitalWrite(DC_MOTOR_1_STANDBY_PIN, 1);  //standby direction
    //analogWrite(DC_MOTOR_1_PWM_PIN, pwm);     //LPWM L motor

  } else if (incomingData[1] < 100) {
    int pwm = (double)(255.0 / 100.0) * (double)((-1) * (incomingData[1] - 100));

    if (pwm > 240){
      pwm = 240;
    }

    Serial.print("FWD ");
    Serial.println(pwm);

    analogWrite(DC_MOTOR_1_FORWARD_PIN, pwm);  //set forward direction
    analogWrite(DC_MOTOR_1_BACK_PIN, 0);     // back for a motor
    digitalWrite(DC_MOTOR_1_STANDBY_PIN, 1);  //standby direction
    //analogWrite(DC_MOTOR_1_PWM_PIN, pwm);     //LPWM L motor

  } else if (incomingData[1] > 100 && incomingData[1] < 130) {
        digitalWrite(DC_MOTOR_1_STANDBY_PIN, 0);  //standby direction
            analogWrite(DC_MOTOR_1_BACK_PIN, 255);     // back for a motor
        analogWrite(DC_MOTOR_1_FORWARD_PIN, 255);     // back for a motor

  }

  if (incomingData[2] > 130) {
    current_steering_angle = (double)(255.0 / 70.0) * (double)(incomingData[2] - 130);
        current_steering_angle = current_steering_angle/2;

    if (current_steering_angle > 90){
      current_steering_angle = 90;
    }

    current_steering_angle = 90 - current_steering_angle;

    //Serial.print("LEFT: ");
    //Serial.println(current_steering_angle);
    

  } else if (incomingData[2] < 100) {
    current_steering_angle = (double)(255.0 / 100.0) * (double)( (-1)* (incomingData[2] - 100));
    current_steering_angle = current_steering_angle/2;
    //Serial.print("RIGHT: ");
    //Serial.println(current_steering_angle);

        if (current_steering_angle > 90){
      current_steering_angle = 90;
    }

    current_steering_angle = 90 + current_steering_angle;


  } else if (incomingData[2] > 100 && incomingData[2] < 130) {
    current_steering_angle = 90;

  }
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  //pinMode(DC_MOTOR_1_PWM_PIN, OUTPUT);
  pinMode(DC_MOTOR_1_FORWARD_PIN, OUTPUT);
  pinMode(DC_MOTOR_1_BACK_PIN, OUTPUT);
  pinMode(DC_MOTOR_1_STANDBY_PIN, OUTPUT);
  pinMode(38, OUTPUT);

  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);           // standard 50 hz servo
  myservo.attach(servoPin, 500, 2400);  // attaches the servo on pin 18 to the servo object
                                        // using default min/max of 1000us and 2000us
                                        // different servos may require different min/max settings
                                        // for an accurate 0 to 180 sweep


    analogWrite(DC_MOTOR_1_BACK_PIN, 255);     // back for a motor
    analogWrite(DC_MOTOR_1_FORWARD_PIN, 255);     // back for a motor

  esp_now_register_recv_cb(i_received_data_from_remote);
}

void loop() {

		myservo.write(current_steering_angle);    // tell servo to go to position in variable 'pos'

  /*for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
		// in steps of 1 degree
		myservo.write(pos);    // tell servo to go to position in variable 'pos'
		delay(5);             // waits 15ms for the servo to reach the position
	}
	for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degreves
		myservo.write(pos);    // tell servo to go to position in variable 'pos'
		delay(5);             // waits 15ms for the servo to reach the position
	}*/
}
