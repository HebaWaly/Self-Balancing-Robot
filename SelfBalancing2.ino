
// Rutine for repeat part of the code every X miliseconds
#define runEvery(t) for (static long _lasttime;\
                         (uint16_t)((uint16_t)millis() - _lasttime) >= (t);\
                         _lasttime += (t))

bool debugMode = false;                         
double theta = 0, output = 0; 
                         
void setup() {
  initSerial();
  initMpu();
  initMotors();
  delay(1000);    // Wait until sensors are ready
  initControl();
}

void loop() {
  if(!mpuReady())
  {
    printString("mpu not ready! returning ..");
    return;
  }
  printString("Get theta");
  theta = getInclinationAngle(); 
  printString("Got theta");
  
  //runEvery(50){
    if (abs(theta) > 0.7) 
    { 
      //printString("Stop Motors");
      stopMotors();
    }
    else
    {
      //printString("Calculate Control Output");
      output = getOutputThrottle(abs(theta));
      //pid_Compute();
      //printString("Drive Motors");
      
      if(theta >= 0)
        driveMotors(output);
      else
        driveMotors(output* -1);
      
    }
    if(debugMode)
    {
      troubleshoot(theta, output);  
    }
  //}
}
