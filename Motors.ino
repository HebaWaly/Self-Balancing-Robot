#define MOTOR_A 0
#define MOTOR_B 1
#define CW  0
#define CCW 1
#define MOTOR_A_MIN_THROTTLE 110
#define MOTOR_B_MIN_THROTTLE 110
#define DESIGN_CORRECTION 0

// Pin Assignments //
const byte PWMA = 3;  // PWM control (speed) for motor A
const byte PWMB = 11; // PWM control (speed) for motor B
const byte DIRA = 12; // Direction control for motor A
const byte DIRB = 13; // Direction control for motor B


void initMotors()
{
  // All pins should be setup as outputs:
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);
  
  // Initialize all pins as low:
  digitalWrite(PWMA, LOW);
  digitalWrite(PWMB, LOW);
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW); 
}

void driveMotors(float output)
{
//  if(debugMode)
//    return;
//    
  //float throttle = abs(output);
//Add min throttle required to move the robot
  float throttle_a = abs(output) + MOTOR_A_MIN_THROTTLE;
  float throttle_b = abs(output) + MOTOR_B_MIN_THROTTLE;

  if(output < 0)
  {
    throttle_a += DESIGN_CORRECTION;
    throttle_b += DESIGN_CORRECTION;  
  }
  if(throttle_a > MAXIMUM_OUTPUT)
    throttle_a = MAXIMUM_OUTPUT;
  if(throttle_b > MAXIMUM_OUTPUT)
    throttle_b = MAXIMUM_OUTPUT;
  if(output >= 0) {    
    driveArdumoto(CCW, throttle_a, throttle_b);
  } else {
    driveArdumoto(CW, throttle_a, throttle_b);
  }
}

void driveArdumoto(byte dir, byte spd_a, byte spd_b)
{
  digitalWrite(DIRA, dir);
  digitalWrite(DIRB, dir);
//  float spdAmplified = spd + 30;
//  if(spdAmplified > 255)
//    spdAmplified = 255;
//  else if(spdAmplified == 40)
//    spdAmplified = 0;
  analogWrite(PWMA, spd_a);
  analogWrite(PWMB, spd_b);
}

void stopMotors()
{
  driveArdumoto(0, 0, 0);  
}
