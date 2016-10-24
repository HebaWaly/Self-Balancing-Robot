#include "PID_v1.h"

#define USE_POTENTIOMETERS false
#define USE_PID_LIB false
#define MAXIMUM_OUTPUT 255
#define MINIMUM_OUTPUT -255
#define INITIAL_INCLINATION 0

int potPin0, potPin1;
double kp, kd, ki;
float lastInput = 0;
double iTerm = 0;
double setpoint = 0;

//PID pid(&theta,&output,&setpoint,kp,ki,kd,DIRECT);

void initControl()
{
  if(USE_POTENTIOMETERS)
  {
    potPin1 = 1;
    potPin0 = 0;
  }
  else
  {
    kp = 112;
    kd = 19;
    ki = 6;   
  }
}

void setControlConstants()
{
  if(USE_POTENTIOMETERS)
  {
    kp = 3 * analogRead(potPin0);    // read values from the potentiometers
    kd = 2 * analogRead(potPin1);  
    ki = 0;  
  }
  if(USE_PID_LIB)
  {
//    pid.SetMode(AUTOMATIC);                  //For info about these,see Arduino PID library
//    pid.SetOutputLimits(-210, 210);
//    pid.SetSampleTime(10);
//    pid.SetTunings(kp,ki,kd);
  }
}

float getOutputThrottle(float theta)
{
  setControlConstants();    
  double error = theta - INITIAL_INCLINATION;
  //integral
  iTerm+= (ki * error);
  if(iTerm > MAXIMUM_OUTPUT)
    iTerm= MAXIMUM_OUTPUT;
  else if(iTerm < MINIMUM_OUTPUT)
    iTerm= MINIMUM_OUTPUT;
  //derivative  
  double dInput = (theta - lastInput);

  // Compute PID Output
  double output = kp * error + iTerm + kd * dInput;
  
  if(output > MAXIMUM_OUTPUT)
    output = MAXIMUM_OUTPUT;
  else if(output < MINIMUM_OUTPUT)
    output = MINIMUM_OUTPUT;

  // Remember some variables for next time
  lastInput = theta;
  return output;
}

//void pid_Compute()
//{
//  printString("output before = ");
//  Serial.print(output);
//  troubleshoot(theta, output);
//  bool computed = pid.Compute();
//  Serial.print("Computed = ");
//  Serial.println(computed);  
//  printString("output after = ");
//  Serial.print(output);
//  troubleshoot(theta, output);
//  
//}
