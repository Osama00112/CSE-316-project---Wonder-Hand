#include "Wire.h"
#include <MPU6050_light.h>
MPU6050 mpu(Wire);

long timer = 0;
int n =0;
float x, y, z;
void setup() {
  Serial.begin(38400);
  Wire.begin();
  
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ 
    Serial.println("NOT FOUND");
    status = mpu.begin();
    } // stop everything if could not connect to MPU6050
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
  mpu.calcOffsets(true,true); // gyro and accelero
  //Serial.println("Done!\n");
}

void loop() {
//  Serial.println('S');
//  delay(5000);
//  Serial.println('A');
//  delay(5000);
//  Serial.println('M');
//  delay(5000);
//  Serial.println('E');
//  delay(5000);
//  Serial.println('E');
//  delay(5000);
  mpu.update();

  
  x=mpu.getAccX();
  delay(10);  
  y=mpu.getAccY();
  delay(10);
  z=mpu.getAccZ();
  delay(10);
  
  //Serial.print(F("ACCELERO  X: "));Serial.print(x);
  //Serial.print("\tY: ");Serial.print(y);
  //Serial.print("\tZ: ");Serial.println(z);

  if(x<-0.45 & abs(y)<0.1 & z<0.2){
    //Serial.println('C');
    //delay(1000);
    }
  
  else if(x<-0.23 & abs(y)<0.1 & z<0.40){
    //Serial.println('B');
    //delay(1000);
    }
  else if(x<-0.06 & abs(y)<0.2 & z<0.75){
    Serial.println('A');
    //delay(1000);
    }  
    else if(x>0.6 & abs(y)<0.2 & z<0.75){
    Serial.println('T');
    //delay(1000);
    }  
  
  else if(x<-0.2 & abs(y)<0.1 & z>1.7){
    //Serial.println('E');
    //delay(1000);
    } 

  else if(x<-0.05 & abs(y)<0.1 & z>1.35){
    //Serial.println('D');
    //delay(1000);
    }
  
  else if(x<-0.05 & y>0.3 & z<1.2){
    Serial.println('R');
    //delay(1000);
    }

  
  else if(x<-0.05 & y<-0.3 & z<1.2){
    Serial.println('L');
    //delay(1000);
    }
  
  else if(abs(x)<0.1 & abs(y)<0.1 & abs(z-1)<0.1){
    Serial.println('p');
    //delay(1000);
    }
    else{
      Serial.println('z');
    }
 
  delay(200);

  
}
