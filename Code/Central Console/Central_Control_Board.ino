const int resetButton = 2; // Reset Button in digital pin 2
const int playerOne = 11; // Player one signal from digital pin 11
const int playerTwo = 12; // Player two signal from digital pin 12
const int playerThree = 13; // Player three signal from digital pin 13

int resetVal = 0; // to store on or off value of the button 

void setup()
{ pinMode(resetButton, INPUT); //Input for reading the switch state of pressed or not pressed (1 or 0)
  pinMode(playerOne, OUTPUT); //Output to the player one controller
  pinMode(playerTwo, OUTPUT); //Output to the player two controller
  pinMode(playerThree, OUTPUT); //Output to the player three controller

}
void loop()
{
  resetVal = digitalRead(resetButton); //read the input of the button and assign to resetVal
  if (resetVal == 0) 
  //if the resetVal is pressed (any value that is not 0), send a signal to all player boards
  {
    digitalWrite(playerOne, HIGH);
    digitalWrite(playerTwo, HIGH);
    digitalWrite(playerThree, HIGH);
  }
  else 
  // Else, if resetVal is 0 (not pressed), do not send a signal (HIGH) to the player boards.
  {
    digitalWrite(playerOne, LOW);
    digitalWrite(playerTwo, LOW);
    digitalWrite(playerThree, LOW);
  }
}
