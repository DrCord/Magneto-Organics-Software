/*
 *  Magneto Organics Electromagnetic Particle Controller Software
 *  For controlling 4-5 electromagnetic coils
 *  By Cord Slatton-Valle
 *  Version 0.1.0
 */


void setup() {
    //pinMode(switchPin, INPUT);          // Set the switch pins as inputs
    //digitalWrite(switchPin, HIGH);      // turn on pullup resistors
    
  Serial.begin(9600);                       // Set up serial communication at 9600bps
}

void loop(){
    Serial.println("Loop Initialized");
  //read the switch   
    //switchRead = digitalRead(switchPin);           // read input value and store it in switchRead
    //delay(100);                                         // 10 milliseconds is a good amount of time
    //switchReadVerify = digitalRead(switchPin);     // read the input again to check for bounces
    //if (switchRead == switchReadVerify) {              // make sure we got 2 consistant readings!
    //Serial.println('Readings match');
      //if (switchRead == LOW) {                        // check if the button is pressed
            // has the button state changed
          //Serial.println('Switch triggered.');                         // set the switch as being triggered
      //}
    //}
    
    delay(1000);
}
