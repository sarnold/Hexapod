
#include <ax12.h>
#include <arduino.h>

#define DATA_SIZE      600
#define SAMPLE_TIME    4

int16_t time[DATA_SIZE];
int16_t data[DATA_SIZE];
int16_t torque[DATA_SIZE];

int8_t initVoltage = 100;
int16_t maxTorque = 1023;
int8_t zero = 0x00;
int16_t mSpeed = 0;

uint8_t temp = 0;

int16_t startPos = 0;
int16_t stopPos = 0;
int8_t id = 1;

int8_t count = 0;
int8_t rdyForTest = 0;
int8_t done = 0;


void setup() {
  Serial.begin(115200);
}

void loop() {
  delay(1000);
  SetMovingSpeed(id, 0);
  if (rdyForTest == 1 && done == 0) {
    test();
    printData();
    done = 1;
  }
  maxTorque = GetMaxTorque(id);
  initVoltage = ax12GetRegister(id, 42, 1);  
}

void test() {
  SetPosition(id, 800);
  delay(7000);
  unsigned int timestamp = millis();
  SetMovingSpeed(id, 0);
  SetPosition(id,800);
//  SetMovingSpeed(id, mSpeed);
//  SetPosition(id,stopPos + 1);
  int pos;
  int i = 0;
//  SetMovingSpeed(id, mSpeed);
  while(i < DATA_SIZE) {
    if(millis()-timestamp >= i*SAMPLE_TIME) {
      time[i] = millis() - timestamp;
      pos = GetPosition(id);
      if (i == 0 && pos == -1) {
        data[i] = startPos;
      } else if (pos == -1) {
        data[i] = data[i-1];
      } else {
        data[i] = pos;
      }
      if(i == 25){
        SetMovingSpeed(id, 100);
        SetPosition(id, 777);
      }
      if(i == 50){
        SetMovingSpeed(id, 100);
        SetPosition(id, 754);
      }
      if(i == 75){
        SetMovingSpeed(id, 100);
        SetPosition(id, 731);
      }
      if(i == 100){
        SetMovingSpeed(id, 100);
        SetPosition(id, 708);
      }
      if(i == 125){
        SetMovingSpeed(id, 100);
        SetPosition(id, 685);
      }
      if(i == 150){
        SetMovingSpeed(id, 100);
        SetPosition(id, 662);
      }
      
      //torque[i] = ax12GetRegister(id, 0x28, 2);
      i++;
    }
  }
  torque[0] = 0;
  data[0] = startPos;
  return;
}

void printData() {
  for (int i = 0;i < DATA_SIZE;i++) {
    Serial.write(time[i]);
    Serial.write(time[i]>>8);

    Serial.write(data[i]);
    Serial.write(data[i]>>8);
    
    Serial.write(torque[i]);
    Serial.write(torque[i]>>8);
  }
  Serial.write(initVoltage);
  Serial.write(zero);
  
  Serial.write(0x01);
  Serial.write(zero);
  
  Serial.write(maxTorque);
  Serial.write(maxTorque>>8);
  
  return;
}

void serialEvent() {
  while (Serial.available()) {
    temp = (uint8_t)Serial.read();
    if (count == 0) {
      id = 1;
      count++;
    } else if (count == 1) {
      startPos = 0 + (((int16_t)temp)<<8);
      count++;
    } else if (count == 2) {
      startPos = startPos + (int16_t)temp;
      count++;
    } else if (count == 3) {
      stopPos = 0 + (((int16_t)temp)<<8);
      count++;
    } else if (count == 4) {
      stopPos = stopPos + (int16_t)temp;
      count++;
    }else if (count == 5) {
      mSpeed = 0 + (((int16_t)temp)<<8);
      count++;
    } else if (count == 6) {
      mSpeed = mSpeed + (int16_t)temp;
      count++;
    } else if (count == 7 && temp == 255) {
      rdyForTest = 1;
      count = 0;
    }
  }
}

