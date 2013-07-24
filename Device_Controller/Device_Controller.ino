/*
 *  Magneto Organics Electromagnetic Particle Controller Software
 *  For controlling 4 electromagnetic coils
 *  By Cord Slatton-Valle
 *  Version 0.3
 */
 
int switchRun = 2;
int switchMode[3] = {3, 4, 5};        // low, medium, high
int currentMode;
int isRunning;                        // is the machine running a pattern?
int pulseLength;                    // pulse length in milliseconds
int pulsePins[4] = {8, 9, 10, 11}; // output pulses connected to pins 8-11
int numOutput = 4;
int runLED = 13;

void setup() {
  pinMode(switchRun, INPUT);          // Set the switchRun as input
  digitalWrite(switchRun, HIGH);      // turn on pullup resistors
  
  for(int i=0; i < 3; i++){
    pinMode(switchMode[i], INPUT);          // Set the switchMode pins as inputs
    digitalWrite(switchMode[i], HIGH);      // turn on pullup resistors
  }
  for(int i=0; i < numOutput; i++){
    pinMode(pulsePins[i], OUTPUT);          // Set the pulse pins as outputs
    digitalWrite(pulsePins[i], LOW);        // initialize all pulsePins to off
  }
  pinMode(runLED, OUTPUT);                 //set onboard led as output
  digitalWrite(runLED, LOW);               //make sure LED is off to start
  
  Serial.begin(9600);                       // Set up serial communication at 9600bps
  Serial.println("Serial Initialized.");
  delay(1000);
}

void loop(){  
  //read the mode switch
  currentMode = checkMode();
  //set pulse length
  setPulse();  
  //read the Run switch
  isRunning = checkSwitch(switchRun);
  //execute the run switch if needed
  if(isRunning == LOW){
    outputPulsePattern();
  }
}

int checkSwitch(int pin){  
  if (digitalRead(pin) == LOW){
      Serial.print("Switch ");
      Serial.print(pin);
      Serial.println(" Activated.");
      return digitalRead(pin);
    }
    else{
      return HIGH;
    }
}

int checkMode(){
  for(int i=0; i < 3; i++){
    return checkSwitch(switchMode[i]);
  }
}

void setPulse(){
  switch (currentMode) {
    case 3:
      pulseLength = 500;
      break;
    case 4:
      pulseLength = 750;
      break;
    case 5:
      pulseLength = 1000;
      break;
  }
}

int outputSinglePulse(int pin){  
  Serial.print("Pulsing pin #");
  Serial.println(pin);
  digitalWrite(pin, HIGH);
  delay(pulseLength);
  digitalWrite(pin, LOW);
}

void outputPulsePattern(){
  digitalWrite(runLED, HIGH);
  Serial.println("Starting pulse pattern.");
  //cycle each pulse pin
  for(int i=0; i < numOutput; i++){
    outputSinglePulse(pulsePins[i]);
  }
  digitalWrite(runLED, LOW);
}
