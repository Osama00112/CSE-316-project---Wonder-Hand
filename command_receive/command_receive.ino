#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,16,2); //0x27 or 0x3F

char comm;
int mpuState = 0;
int state = 0;
char currentCommand;
int component[2] = {0,0};

void initialDisplay(){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("State:");
    lcd.print(state);
    if(component[state] == 0)
      lcd.print(" OFF");
    else
      lcd.print(" ON");
    lcd.setCursor(0,1);
}

void setup() {
  Serial.begin(38400);      // Serial communication is activated at 38400 baud/s.
  lcd.begin();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("State:");
  lcd.setCursor(0,1);  
}

void decision(int state){
  initialDisplay();
  if(state == 0){
    lcd.print("Fan");
  }else if(state == 1){
    lcd.print("Light");
  }
}

void loop() {
  if (Serial.available()) {   // Witing for data incoming from the other XBee module
    
    comm = Serial.read();
    //currentCommand = comm;
    Serial.print(currentCommand);
    Serial.print(" comm: ");
    Serial.println(comm);
    if(comm == 'p')
    {
      currentCommand = 'p';
      Serial.println(comm);
    }else if(comm == 'A'){
      if(currentCommand == 'p'){
      component[state] ^= 1;  
      currentCommand = 'A';
      decision(state);
      }
      Serial.println(comm);
    }else if(comm == 'B'){
      Serial.println(comm);
    }else if(comm == 'C'){
      Serial.println(comm);
    }else if(comm == 'L'){
      if(currentCommand == 'p'){
        state++;
      if(state > 1)
        state = 0;
      Serial.println(comm);
      decision(state);
      currentCommand = 'L';
      }
    }else if(comm == 'R'){
      Serial.println(comm);
      if(currentCommand == 'p'){
        state++;
      if(state > 1)
        state = 0;
      Serial.println(comm);
      decision(state);
      currentCommand = 'R';
      }
//      initialDisplay();
//      lcd.print("Light");
    }else{
      Serial.println("not found...");
    }
    //delay(2000);
  }
}
