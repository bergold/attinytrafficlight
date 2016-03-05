#define REDPIN 0
#define YELLOWPIN 1
#define GREENPIN 4
#define BUTTONPIN 2

// We will start with red in the "on" state, which will be represented by a 0.
// 1 is "red-yellow", 2 is "green" and 3 is "yellow".
int lightState = 0;

// We'll need some variables to monitor the button.
int buttonState = LOW;
int lastButtonReading = LOW;
int lastButtonState=LOW;
long lastDebounceTime = 0;
long debounceDelay = 50;

/*
  Set the pinMode for each of the ATTiny's pins.
*/
void setup() {
  pinMode(REDPIN, OUTPUT); 
  pinMode(YELLOWPIN, OUTPUT); 
  pinMode(GREENPIN, OUTPUT);
  pinMode(BUTTONPIN, INPUT);
  
  digitalWrite(REDPIN, HIGH);
  digitalWrite(YELLOWPIN, LOW);
  digitalWrite(GREENPIN, LOW);
}

/*
  Each time we loop through the program we should check the state of our pushbutton, then
  fade the lights.
*/
void loop() {
  monitorButton();
}

/*
  Each time we loop through the program, we check to see if the state (pressed or not pressed)
  of our pushbutton has changed. If it has changed, we call the buttonStateChanged() function.
*/
void monitorButton() {
  //Read the current state of the button.
  int reading = digitalRead(BUTTONPIN);

  if (reading != lastButtonReading) {
    lastDebounceTime = millis();
  } 
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    buttonState = reading;
    
    if (lastButtonState!=buttonState) {
       buttonStateChanged();
    }
    
    lastButtonState = buttonState;
  }
  
  lastButtonReading = reading;
}

/*
  If the button state has changed to "not pressed", we want to advance the light state.
  Said a different way, we don't care when the user presses down on the button. We care
  when the user releases the button.
*/
void buttonStateChanged() {
  if (buttonState==LOW) { 
    advanceLightState();
  } 
}

/*
  This function simply advances from red to green, from green to yellow, and finally from
  yellow to red.
*/
void advanceLightState() {
  //If red is on, light up yellow.
  if (lightState==0) {
   	
    lightState=1;
    
    digitalWrite(YELLOWPIN, HIGH);
    
    return; 
  }
  
  //If red and yellow is on, turn it off and light up green.
  if (lightState==1) {
   	
    lightState=2;
    
    digitalWrite(REDPIN,   LOW);
    digitalWrite(YELLOWPIN, LOW);
    digitalWrite(GREENPIN, HIGH);
    
    return; 
  }
  
  //If green is on, turn it off and light up yellow.
  if (lightState==2) {
   	
    lightState=3;
    
    digitalWrite(YELLOWPIN, HIGH);
    digitalWrite(GREENPIN, LOW);
    
    return; 
  }
  
  //If yellow is on, turn it off and light up red.
  if (lightState==3) {
   	
    lightState=0;
    
    digitalWrite(REDPIN,   HIGH);
    digitalWrite(YELLOWPIN, LOW);
    
    return; 
  }
}
