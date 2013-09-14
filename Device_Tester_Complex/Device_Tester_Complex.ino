/*
 *  Magneto Organics Electromagnetic Particle Controller Software
 *  For controlling 4 electromagnetic coils
 *  By Cord Slatton-Valle
 *  Version 0.3
 */
int numInput = 5;                          //number of input channels
int numOutput = 4;                            //number of output channels
int switchPins[5] = {2, 3, 4, 5, 6};       // switches connected to pins 2-6
int switchRead;                            // for reading switch status, HIGH == Depressed == On
int switchReadVerify;                      // for reading the delayed/debounced status
int buttonState[5];                        // holds each button state
int isRunning = 0;                         // is the machine running a pattern?
int pulseLength = 400;                    // pulse length in milliseconds
int pulsePins[5] = {8, 9, 10, 11, 12}; // output pulses connected to pins 8-12
int readLED = 13;

void setup() {
  for(int i=0; i < numInput; i++){
    pinMode(switchPins[i], INPUT);          // Set the switch pins as inputs
    digitalWrite(switchPins[i], HIGH);      // turn on pullup resistors
  }
  for(int i=0; i < numOutput; i++){
    pinMode(pulsePins[i], OUTPUT);          // Set the pulse pins as outputs
    //digitalWrite(pulsePins[i], LOW);        // initialize all pulsePins to off
  }
  pinMode(readLED, OUTPUT);                 //set onboard led as output
  digitalWrite(readLED, LOW);                //make sure LED is off to start
  for(int i=0; i < numInput; i++){
    buttonState[i] = 0;                     // Set the initial button states as off
  }
  Serial.begin(9600);                       // Set up serial communication at 9600bps
  Serial.println("Serial Initialized.");
  delay(1000);
}

void loop(){
  //read the switches
  digitalWrite(readLED, HIGH);
  delay(000);
  for(int i=0; i < numInput; i++){
    Serial.print("switch ");
    Serial.print(i+1);
    Serial.println(" read");    
    switchRead = digitalRead(switchPins[i]);           // read input value and store it in switchRead
    delay(20);                                         // 10 milliseconds is a good amount of time
    switchReadVerify = digitalRead(switchPins[i]);     // read the input again to check for bounces
    if (switchRead == switchReadVerify) {              // make sure we got 2 consistant readings!
      if (switchRead == 0) {                        // check if the button is pressed
        //Serial.println("switchRead == 0");
        //if (switchRead != buttonState[i]) {            // has the button state changed
          Serial.print("Switch ");
          Serial.print(i+1);
          Serial.println(" triggered.");
          buttonState[i] = 1;                          // set the switch as being triggered
        //}
      }
      else{
        buttonState[i] = 0;
      }
    }
    digitalWrite(readLED, LOW);
    Serial.print("\n");
    delay(00);
  }
  //activate each triggered switch
  for(int j=0; j < numInput; j++){
    Serial.print("Pulse ");
    Serial.print(j+1);
    Serial.println(" for loop entry");
    // TODO: pattern switch(es) will certainly change
    if(buttonState[j] == 1){
      if(j != 4){                                      // not the pattern switch      
        outputSinglePulse(pulsePins[j]);             // output pulse
      }
      else{
        isRunning = 1;
        outputPulsePattern();                         //output pulse program
        outputPulsePatternReverse();
        isRunning = 0;
      }     
      buttonState[j] == 0;                            // set switch as not pressed
    }
    Serial.print("\n");
  }
  Serial.print("\n");
  delay(000);
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

void outputPulsePatternReverse(){
  Serial.println("Starting reverse pulse pattern.");
  //cycle each pulse pin
  for(int i=numOutput-1; i >=   0; i--){
    outputSinglePulse(pulsePins[i]);
  }
}
