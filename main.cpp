#include <Adafruit_LiquidCrystal.h>
#define buttonPin 12

int MQ2pin = A0;
bool state = false;
bool prevState = false;
bool lastButtonState = HIGH;
float history[3];
int index = 0;

Adafruit_LiquidCrystal lcd_1(0);

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  lcd_1.begin(16, 2);

  lcd_1.print("    Welcome!");
  delay(1000);
  lcd_1.clear();
}

void loop() {
  bool currentButtonState = digitalRead(buttonPin);

  // Detect button press (falling edge)
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    state = !state; // Toggle mode
  }
  
  if (state != prevState) {
    lcd_1.clear();      
    prevState = state;   
  }

  lastButtonState = currentButtonState;

  float sensorValue = analogRead(MQ2pin);
  float voltage = sensorValue * (5.0 / 1023.0);
  float promille = voltage * 0.4;

  lcd_1.setCursor(0, 0);
  if (!state) {
    lcd_1.print("Alcometer:     ");
    lcd_1.setCursor(0, 1);
    lcd_1.print(promille, 2);
    
    history[index] = promille;
    index = (index + 1) % 3;
    
    delay(750);
  } else {
    lcd_1.print("History:       ");
    lcd_1.setCursor(0, 1);
    
    for (int i = 0; i < 3; i++) {
      lcd_1.print(history[i]);
      if (i < 2) lcd_1.print(",");
    }
  }
}
