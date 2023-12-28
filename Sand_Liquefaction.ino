/*Code for paper rocket launcher SXSW
 * 2/27/23
 * By Ronan Valadez
 */

//pin numbers representing rgb button colors
int red = 19;
int green = 18;
int blue = 17;

int buttonPin = 3; //pin number for rgb button
int buttonState = 0;  //state of RGB button
int driver = 10; //pin number for driver
long redInterval = 60000; // delay time for cooldown period
long driverInterval = 60000; // length of time driver is on
int potPin = A6; //pin number for potentiometer
int potValue = 0; // potentiometer value

void setup() {
  // put your setup code here, to run once:
  //set color pins to OUTPUT
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  // set driver pin to OUTPUT
  pinMode(driver, OUTPUT);

  // turn rgb pins to HIGH
  digitalWrite(blue, HIGH);
  digitalWrite(green, HIGH);
  digitalWrite(red, HIGH);

  //set driver to HIGH
  digitalWrite(driver, LOW);

  //set button to input
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  turnOnGreen();

}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(buttonPin);
  Serial.println( digitalRead(buttonPin));

  potValue = analogRead(potPin);  // read in potentiometer's value, pass it as an argument to turnOnDriver and turnOnRead
  
  /*if button is pressed, turn off green light
    activate driver
    turn on red after driver is finished
    turn on green once cooldown is finished*/
  if (buttonState == LOW) {
    turnOffGreen();
    turnOnDriver(potValue);
    turnOnRed(potValue);
    turnOnGreen();
  }
}



void turnOnGreen() { //turn on green light. Symbolizes ready to launch
  digitalWrite(green, LOW);
  

}

void turnOffGreen() { //turns off green light
  digitalWrite(green, HIGH);
  
}

void turnOnRed(int potentiometerValue) { //function to turn on red light, takes in potentiometer's value and maps it between 30 seconds and 2 minutes for its cooldown timer, symbolizes cooldown period
  digitalWrite(red, LOW);
  redInterval = map(potentiometerValue, 0, 1023, 30000, 120000);
  delay(redInterval);
  digitalWrite(red, HIGH);
 
}

void turnOnDriver(int potentiometerValue) { //activates driver, changes color to yellow to represent firing, takes in potentiometer's value, and maps it between 30 seconds and 2 minutes for its cooldown timer
  digitalWrite(driver, HIGH);
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  driverInterval = map(potentiometerValue, 0, 1023, 30000, 120000);
  delay(driverInterval);
  digitalWrite(green, HIGH);
  digitalWrite(red, HIGH);
  digitalWrite(driver, LOW);
  

}
