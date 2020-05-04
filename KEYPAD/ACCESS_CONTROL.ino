/*
With this program we can control an actuator, such as a LED for example, using an alphanumeric password.
To validate the password we will use " * "
To clear the password entered we will use " # "
If the password is correct, a green LED lights up, but if It´s incorrect, a red LED lights up.
*/

//Include the necessary libraries
#include <Password.h>   //Password library
#include <Keypad.h>     //Keypad library

//Define the desired password
Password password = Password ( "0000" ); //Define the password

//Include actuators
int R_LED = 11; //Red LED attach to digital pin 11
int G_LED = 12; //Green LED attach to digital pin 12

//Define Keypad number of ROWS and COLUMS
const byte ROWS = 4; //Four rows
const byte COLS = 4; //Four colums

//Define Keypad KEYMAP
char keys[ROWS][COLS] ={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

//Define Keypad connections
byte rowPins[ROWS] = {9,8,7,6}; //Row1 attach to digital pin 9, Row2 attach to digital pin 8 [...]
byte colPins[COLS] = {5,4,3,2}; //Colum1 attach to digital pin 5, Colum2 attach to digital pin 4 [...]

//Create the Keypad variable
Keypad keypad = Keypad (makeKeymap (keys), rowPins, colPins, ROWS, COLS);

//FUNCTIONS
void setup(){

  Serial.begin (9600);
  keypad.addEventListener (keypadEvent); //Keypad listener
  
  pinMode (R_LED, OUTPUT); //Set pin 11 as an output 
  pinMode (G_LED, OUTPUT); //Set pin 12 as an output
} 

//Turn Off both LEDs
void forceOff(){  
  digitalWrite (R_LED, LOW); 
  digitalWrite (G_LED, LOW); 
}

void loop(){
  keypad.getKey();
}

void keypadEvent(KeypadEvent eKey){
  switch (keypad.getState()){
    
    case PRESSED:
      Serial.print("Pressed: ");
      Serial.println(eKey);
      
  switch (eKey){
    
    case '*':
      checkPassword();
    break;
    
    case '#':
      password.reset();
    break;
    
    default: password.append(eKey);
  }
 }
}

//Checking the password
void checkPassword(){

//Password correct

  if (password.evaluate()) {
    
    Serial.println("Success");
     
    digitalWrite(R_LED, LOW);
    digitalWrite(G_LED, HIGH);  
      
//Password incorrect  

  } else {
    
    Serial.println("Wrong");
    
    digitalWrite(R_LED, HIGH);
    digitalWrite(G_LED, LOW);
  }

//Wait 2 seconds
delay(2000);

//Turn off both LEDs
forceOff();

}