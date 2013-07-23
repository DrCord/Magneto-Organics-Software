/*
 *  Magneto Organics Electromagnetic Particle Controller Software
 *  For controlling 4 electromagnetic coils
 *  By Cord Slatton-Valle
 *  Version 0.2.1
 */
<<<<<<< HEAD
 
int switchRun = 2;
int switchMode[3] = {3, 4, 5};
int currentMode;
int isRunning;                        // is the machine running a pattern?
int pulseLength;                    // pulse length in milliseconds
int pulsePins[4] = {8, 9, 10, 11}; // output pulses connected to pins 8-11
int runLED = 13;
int numOutput = 4;
=======
int numInput = 5;                          //number of input channels
int numOutput = 4;                            //number of output channels
int switchPins[5] = {2, 3, 4, 5, 6};       // switches connected to pins 2-6
int switchRead;                            // for reading switch status, HIGH == Depressed == On
int switchReadVerify;                      // for reading the delayed/debounced status
int buttonState[5];                        // holds each button state
int isRunning = 0;                         // is the machine running a pattern?
int pulseLength = 1000;                    // pulse length in milliseconds
int pulsePins[5] = {8, 9, 10, 11, 12}; // output pulses connected to pins 8-12
int readLED = 13;
>>>>>>> 528ade6fa94195f6d8d4c242ec7a0ad561a71166

void setup() {
  pinMode(switchRun, INPUT);          // Set the switchRun as input
    digitalWrite(switchRun, HIGH);
  
  for(int i=0; i < 3; i++){
    pinMode(switchMode[i], INPUT);          // Set the switchMode pins as inputs
    digitalWrite(switchMode[i], HIGH);      // turn on pullup resistors
  }
  for(int i=0; i < numOutput; i++){
    pinMode(pulsePins[i], OUTPUT);          // Set the pulse pins as outputs
    //digitalWrite(pulsePins[i], LOW);        // initialize all pulsePins to off
  }
  pinMode(runLED, OUTPUT);                 //set onboard led as output
  digitalWrite(runLED, LOW);               //make sure LED is off to start
  
  //set the initial mode
  currentMode = checkMode();
  setPulse(); //set pulse length
  
  Serial.begin(9600);                       // Set up serial communication at 9600bps
  Serial.println("Serial Initialized.");
  delay(1000);
}

void loop(){  
  //read the Run switch
  isRunning = checkSwitch(switchRun);
  //execute the run switch if needed
  if(isRunning == LOW){
    digitalWrite(runLED, HIGH);
    outputPulsePattern();
    digitalWrite(runLED, LOW);
  }
  
  //read the mode switch
  currentMode = checkMode();
  setPulse(); //set pulse length
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
  Serial.println("Starting pulse pattern.");
  //cycle each pulse pin
  for(int i=0; i < numOutput; i++){
    outputSinglePulse(pulsePins[i]);
  }
}
