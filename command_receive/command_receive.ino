#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,16,2); //0x27 or 0x3F

char comm;
int UNOpin1 = 5;
int UNOpin2 = 6;
int UNOpin3 = 7;
int UNOpin4 = 8;


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

//  lcd.setCursor(0,0);
//  lcd.print("State:");
//  lcd.setCursor(0,1);  
  initialDisplay();


  pinMode(UNOpin1, OUTPUT);
  pinMode(UNOpin2, OUTPUT);
  pinMode(UNOpin3, OUTPUT);
  pinMode(UNOpin4, OUTPUT);
//
//  pinMode(enA, OUTPUT);
//  pinMode(enB, OUTPUT);

  // analogWrite(enA, spd);
  // analogWrite(enB, spd);

  digitalWrite(UNOpin1, HIGH);
  digitalWrite(UNOpin2, HIGH);
  digitalWrite(UNOpin3, HIGH);
  digitalWrite(UNOpin4, HIGH);

}

void decision(int state){
  initialDisplay();
  if(state == 0){
    lcd.print("Fan");
  }else if(state == 1){
    lcd.print("Light");
  }
}

void checker(int state, int voltage){
  if(state == 0){
    if(voltage == 0){
      digitalWrite(UNOpin1, HIGH);
    }else{
      digitalWrite(UNOpin1, LOW);
    }
  }else{
     if(voltage == 0){
      digitalWrite(UNOpin2, HIGH);
    }else{
      digitalWrite(UNOpin2, LOW);
    }
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
      checker(state,component[state]);
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
