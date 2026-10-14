#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

// YOUR MOTOR PINS
int motor1Pin1 = 7; int motor1Pin2 = 6; int pwm1Pin = 5;
int motor2Pin1 = 4; int motor2Pin2 = 3; int pwm2Pin = 9;

// PROVEN PID VALUES
double Kp = 22; double Ki = 0.8; double Kd = 8;
double zeroOffset = 0;

// ASYMMETRY COMPENSATION (battery fix)
double deadbandLeft = -0.5;  
double deadbandRight = 3.5;

double previousError = 0, integral = 0;
unsigned long previousTime = 0;

void setup() {
  Serial.begin(9600);
  
  // MOTOR PINS
  pinMode(motor1Pin1, OUTPUT); pinMode(motor1Pin2, OUTPUT); pinMode(pwm1Pin, OUTPUT);
  pinMode(motor2Pin1, OUTPUT); pinMode(motor2Pin2, OUTPUT); pinMode(pwm2Pin, OUTPUT);
  
  Wire.begin();
  mpu.initialize();
  
  // AUTO-CALIBRATE (KEEP ROBOT FLAT 3 seconds)
  Serial.println("🔧 CALIBRATING - KEEP FLAT!");
  float sum = 0;
  for(int i = 0; i < 150; i++) {
    int16_t ax, ay, az, gx, gy, gz;
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    sum += atan2(ax, az) * 180 / PI;
    delay(5
    );
  }
  zeroOffset = sum / 150.0;
  
  Serial.println("✅ READY TO BALANCE!");
  Serial.print("Zero offset: "); Serial.println(zeroOffset, 2);
  Serial.print("Deadband: "); Serial.print(deadbandLeft,1); 
  Serial.print("° to "); Serial.print(deadbandRight,1); Serial.println("°");
}

void loop() {
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  
  double pitch = atan2(ax, az) * 180 / PI;
  
  // ASYMMETRIC DEADZONE (your battery compensation)
  if (pitch > deadbandLeft && pitch < deadbandRight) {
    stopMotors();
    integral = 0;
    return;
  }
  
  double error = zeroOffset - pitch;  // Positive = falling FORWARD
  
  // PID CALC
  unsigned long now = millis();
  double deltaTime = (now - previousTime) / 1000.0;
  if (deltaTime < 0.01) deltaTime = 0.01;
  previousTime = now;
  
  double P = Kp * error;
  integral += Ki * error * deltaTime;
  if (integral > 25) integral = 25;
  if (integral < -25) integral = -25;
  double D = Kd * (error - previousError) / deltaTime;
  previousError = error;
  
  int output = constrain(P + integral + D, -110, 110);  // 9V safe
  
  driveMotors(output);
  
  // DEBUG
  Serial.print("Pitch:"); Serial.print(pitch,1);
  Serial.print("° Err:"); Serial.print(error,2);
  Serial.print(" PWM:"); Serial.println(output);
  
  delay(10);
}

void driveMotors(int speed) {
  int pwm = abs(speed);
  if (pwm > 255) pwm = 255;
  
  if (speed > 0) {  // FALLING FORWARD → BACKWARD MOTORS
    digitalWrite(motor1Pin1, LOW);  digitalWrite(motor1Pin2, HIGH);
    digitalWrite(motor2Pin1, LOW);  digitalWrite(motor2Pin2, HIGH);
  } else {  // FALLING BACKWARD → FORWARD MOTORS
    digitalWrite(motor1Pin1, HIGH); digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, HIGH); digitalWrite(motor2Pin2, LOW);
  }
  analogWrite(pwm1Pin, pwm);
  analogWrite(pwm2Pin, pwm);
}

void stopMotors() {
  analogWrite(pwm1Pin, 0);
  analogWrite(pwm2Pin, 0);
}
