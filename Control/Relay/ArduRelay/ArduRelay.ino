//This code can recive and send data to several Servos
#include <ax12.h>
#include <arduino.h>

unsigned char buffer[255];
int index=0;
int bytesToRead=0;

void setup()
{
  // start serial port at 115200 bps and wait for port to open for beaglebone
  Serial.begin(115200);
  ax12Init(1000000);
}

void loop()
{
  index=0;
  bytesToRead=0;
  
  // Wait for startByte
  if(Serial.available() > 0){
    buffer[index]=Serial.read();
  }
  if(buffer[0] == 0xFF){
      //Wait for first startByte
      while(Serial.available() < 2){}
      buffer[1]=Serial.read();
      buffer[2]=Serial.read();
      bytesToRead=buffer[2];
      index = 3;
      while(index != bytesToRead){
          //Read the rest of the message
          if(Serial.available() > 0){
              buffer[index]=Serial.read();
              index++;
          }
      }
      
      switch (buffer[1]){
          case 3:
            writeToServo(buffer[3],buffer[4]);
            break;
          case 4:
            //readFromServo(reg,amount,nbrOfServo) 
            readFromServo(buffer[3],buffer[4],buffer[5]);
            break;
          default:
            break;
      }

      //Send respons to BeagleBone used for debuging
      //Serial.write(buffer,bytesToRead);
      Serial.flush();
      //Clear buffert
      for(int i=0;i<bytesToRead;i++){
        buffer[i]=0;
      }
  }
}
//Used for instruction 3
void writeToServo(int reg,int amount) {
  for(int id=1;id<19;id++){
    setTX(id);
    int checksum = id + 3 + amount + AX_WRITE_DATA + reg;
    for (int i = 0;i<amount;i++) {
      checksum = checksum + buffer[(5+(id-1)*amount)+i];//startOffset+i
    }
    checksum = ~(checksum % 256);
    ax12writeB(0xFF);
    ax12writeB(0xFF);
    ax12writeB(id);
    ax12writeB(3 + amount);    // length
    ax12writeB(AX_WRITE_DATA);
    ax12writeB(reg);
    //Data to write to the register
    for (int i=0;i<amount;i++) {
      ax12writeB(buffer[(5+(id-1)*amount)+i]);
    }
    // checksum = 
    ax12writeB(checksum);
    setRX(id);
  }
}
  
void readFromServo(int reg,int amount,int nbrOfServo) {
  int temp;
  //Start byte
  Serial.write(0xFF);
  //amount of data in message to Beaglebone
  Serial.write(amount*nbrOfServo+2);
  for(int i=0;i<nbrOfServo;i++){
    temp=ax12GetRegister(buffer[6+i],reg,amount);
    if(temp!=-1){
      Serial.write(temp & 0xff);//Send low byte
      Serial.write((temp & 0xff00)>>8);//Send high byte
    }
    else{//Error in communication
      Serial.write(0xF0);
      Serial.write(0xFF);//High byte
    }
    Serial.flush();
  }
}
    

