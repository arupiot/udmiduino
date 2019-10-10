#include <SoftwareSerial.h>
#define RxD 7
#define TxD 6

SoftwareSerial BlueToothSerial(RxD,TxD); 
char flag=1; 

void Test_BlueTooth() {

  unsigned char t=0;
  String RXD = "";
  Serial.println("Test BlueTooth ...");
  BlueToothSerial.print("AT\r\n");  
  delay(100);
  while(BlueToothSerial.available()>0)
  {    
     RXD +=  char( BlueToothSerial.read() );
     delay(1);
  } 
  do{
    t++;
    delay(400);
    Serial.println("Test Failed ! Retrying ...");
  }while( ((RXD[0]!='O')&&(RXD[1]!='K'))&&(t<5));  
  if(t<5) Serial.println("Test Successful !\r\n");
  else { Serial.println("Retry Failed !"); while(1); }
}

void sendBlueToothCommand(char *Command) {

 BlueToothSerial.print(Command);
 Serial.print(Command); 
 delay(100);
 while(BlueToothSerial.available())
 {    
    Serial.print(char(BlueToothSerial.read())); 
 }
}

void setupBlueTooth() {

 Serial.println("Bluetooth Initialization ...");      
 sendBlueToothCommand("AT+NAME=LinkSprite\r\n");
 sendBlueToothCommand("AT+ROLE=0\r\n");
 sendBlueToothCommand("AT+CMODE=0\r\n");
 sendBlueToothCommand("AT+PSWD=1234\r\n");
 sendBlueToothCommand("AT+UART=38400,0,0\r\n");
 delay(500);
 Serial.println("Bluetooth Initialized Successfully !\r\n");
 do{
   if(Serial.available())
   {
     if( Serial.read() == 'S')
     {
       sendBlueToothCommand("AT+RESET\r\n");
       flag = 0;
     }
   }
 }while(flag);
}

void setup() {

  Serial.begin(38400);     
  BlueToothSerial.begin(38400); 
  delay(500);
  Test_BlueTooth();  
  setupBlueTooth();
}

void loop() {

   if(BlueToothSerial.available())
   {
     Serial.print(char(BlueToothSerial.read()));
   }
   if(Serial.available())
   {
     BlueToothSerial.print(char(Serial.read()));
   }      
}
