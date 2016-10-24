void initSerial()
{
  Serial.begin(9600);
  while (!Serial);
}

void troubleshoot(float theta, float output)
{
  Serial.print("Kp = ");
  Serial.print(kp);
  Serial.print(" Kd = ");
  Serial.print(kd);
  Serial.print(" Ki = ");
  Serial.print(ki);
  Serial.print(" theta = ");
  Serial.print(theta);
  Serial.print(" output = ");
  Serial.println(output);
}

void printString(char s[])
{
  if(debugMode)
    Serial.println(s);  
   return;
}
