
int i;
float voltajeTurbidad;
float NTU;


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  
  int sensorValue = analogRead(A0);

  for (i=0; i<800; i++){
    voltajeTurbiedad +=((float)sensorValue/1023)*5;
    
  }

  float valorTurbiedad=map(sensorValue, 0, 1023, 100, 0);
  // print out the value you read:
  
  Serial.println(valorTurbiedad);
  delay(10);        // delay in between reads for stability
}
