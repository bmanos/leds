/*
 *  ******************************************
 *  ****        Welcome to our led        ****
 *  ****        and motor program         ****
 *  ******************************************
 */
// Declare the switches
int sw2 = 2;  // switch to choose between leds and motor.
int sw1 = 7;  // switch to choose leds direction.
// Declare pin for the potentiometer.
int pot = A0;
// Declare the led pins in an array.
int ledPins[] = {9, 10, 11, 12};
int index;
// Declare the L293D IC motor pins.
int motor_en  = 5;
int motor_in1 = 4;
// Declare speed variables.
int potValue = 0;
int speedValue = 0;
// Declare variable to keep pot speed led value.
int lastLedPotSpeedValue;
// Declare direction state variables to keep track of direction.
int directionState;
int lastDirectionState;

void setup() {
  Serial.begin(9600);
  index;
  for (index = 0; index <= 3; index++)
  {
    pinMode(ledPins[index], OUTPUT);
  }
  pinMode(pot, INPUT);
  pinMode(sw2, INPUT);
  pinMode(sw1, INPUT);
  pinMode(motor_en, OUTPUT);
  pinMode(motor_in1, OUTPUT);
  digitalWrite(motor_in1, LOW); 
}

void loop() {
  
    Serial.print("Η τιμή του ποτενσιόμετρου A0 είναι               : ");
    //Serial.print("The pot value A0 is           : ");
    Serial.println(potValue);
    Serial.print("Η τιμή της map είναι                             : ");
    //Serial.print("The value of map is           : ");
    Serial.println(speedValue);
    Serial.print("Η τιμή του ποτενσιόμετρου για τα λεντ είναι      : ");
    //Serial.print("The pot value for the leds is : ");
    Serial.println(lastLedPotSpeedValue);

    if (digitalRead(sw2) == HIGH && digitalRead(sw1) == HIGH) {
      motorStop();  // Stop motor
      allLedsRight();
      Serial.println("Ο διακόπτης του λεντ switch 2  είναι ανοιχτός το μοτέρ είναι κλειστό, ο διακόπτης swith1 είναι ανοιχτός και τα λεντ αναβοσβσήνουν προς τα δεξιά.");
      Serial.println("**************************************************************************************************************************************************");
      //Serial.println("Led's switch 2 is ON motor is OFF, swith1 is ON and the leds are blinking in the right direction");
      //Serial.println("**************************************************************************************************");
    }
    if (digitalRead(sw2) == HIGH && digitalRead(sw1) == LOW) {
      motorStop();  // Stop motor
      allLedsLeft();
      Serial.println("Ο διακόπτης του λεντ switch 2 είναι ανοιχτός το μοτέρ είναι κλειστό, ο διακόπτης swith1 είναι ανοιχτός και τα λεντ αναβοσβσήνουν προς τα αριστερά.");
      Serial.println("****************************************************************************************************************************************************");
      //Serial.println("Led's switch 2 is ON motor is OFF, swith1 is ON and the leds are blinking in the left direction");
      //Serial.println("*************************************************************************************************");
    }
    if (digitalRead(sw2) == LOW) {
      motorRun();
      keepLedsOn();
      Serial.println("Ο διακόπτης του μοτέρ switch 2 είναι ανοιχτός και τα λεντ συνεχίζουν να αναβοσβήνουν με την ίδια ταχύτητα και κατεύθυνση με πριν.");
      Serial.println("***********************************************************************************************************************************");
      //Serial.println("Motor's switch 2 is ON and the leds are still blinking with the same speed and direction as before.");
      //Serial.println("*****************************************************************************************************");
    }
}
// when sw2 turns the motor on keep leds flashing in same speed and direction as before.
void keepLedsOn()
{
  if (lastDirectionState == 1) {
    index;
    for (index = 0; index <= 3; index++)
    {
      digitalWrite(ledPins[index], HIGH);
      delay(lastLedPotSpeedValue);
      digitalWrite(ledPins[index], LOW);
      delay(lastLedPotSpeedValue);
    }
  }
  else {
    index;
    for (index = 3; index >= 0; index--)
    {
      digitalWrite(ledPins[index], HIGH);
      delay(lastLedPotSpeedValue);
      digitalWrite(ledPins[index], LOW);
      delay(lastLedPotSpeedValue);
    }
  }
}
// move leds in the right direction.
void allLedsRight()
{
  index;
  potValue = analogRead(pot);
  lastLedPotSpeedValue = potValue;

  directionState = digitalRead(sw1);
  lastDirectionState = directionState;
  Serial.print("Η τιμή για το κουμπί κατεύθυνσης είναι (δέξια)   : ");
  //Serial.print("The direction value (right) is : ");
  Serial.println(lastDirectionState);

  for (index = 0; index <= 3; index++)
  {
    digitalWrite(ledPins[index], HIGH);
    delay(potValue);
    digitalWrite(ledPins[index], LOW);
    delay(potValue);
  }
}
// move leds in the left direction.
void allLedsLeft()
{
  index;
  potValue = analogRead(pot);
  lastLedPotSpeedValue = potValue;

  directionState = digitalRead(sw1);
  lastDirectionState = directionState;
  Serial.print("Η τιμή για το κουμπί κατεύθυνσης είναι (αριστερά): ");
  //Serial.print("The direction value (left) is  : ");
  Serial.println(lastDirectionState);

  for (index = 3; index >= 0; index--)
  {
    digitalWrite(ledPins[index], HIGH);
    delay(potValue);
    digitalWrite(ledPins[index], LOW);
    delay(potValue);
  }
}
// motor move.
void motorRun() {
  potValue = analogRead(pot);
  speedValue = map(potValue, 0, 1023, 0, 255);
  analogWrite(motor_en, speedValue);
  digitalWrite(motor_in1, HIGH);   // Motor is ON.
}
// motor brake.
void motorStop() {
  digitalWrite(motor_in1, LOW);  // Motor is OFF.
}