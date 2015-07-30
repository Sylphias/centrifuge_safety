#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin
int safepin = 12;
int offpin = 13;
int switchpin = 8;
int oldState = 0;
int buttonState = 0; 
int systemMode = 0;
// System mode 0 = Safety Off
// System mode 1 = Safety on
void setup()
{
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  //myservo.write(180);
  pinMode(safepin, OUTPUT);
  pinMode(offpin,OUTPUT);
  pinMode(switchpin,INPUT);
  digitalWrite(offpin,HIGH);
}

void loop() 
{ 
  buttonState = digitalRead(switchpin);
  //Serial.println(buttonState);
  if(oldState == LOW && buttonState == HIGH) {
    systemMode = 1;
    oldState = HIGH;
    digitalWrite(safepin,HIGH);
    digitalWrite(offpin,LOW);
    delay(1000);
    Serial.println("Safety On");
  }
  else if(oldState == HIGH && buttonState == HIGH)
  {
    systemMode = 0;
    oldState = LOW;
    delay(1000);
    digitalWrite(offpin,HIGH);
    digitalWrite(safepin,LOW);
    Serial.println("Safety Off"); 
  }

  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023) 
  val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180) 
    
  switch(systemMode){
    case 0:
      //Safety Off
      myservo.write(val);// sets the servo position according to the scaled value 
      Serial.println(val);
  
    break; 
    case 1:
      //Safety On
      int testval = safety_function(val, 80);
      Serial.println(testval);
      
    break;
  }
  //delay(1000);                           // waits for the servo to get there 
} 
int safety_function(int val, int limit){
  if(val < limit){
    myservo.write(val);
    return val;
  }
  else{
    myservo.write(limit);
    return  limit;
  }

}
