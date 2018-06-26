#include "AIS_NB_BC95.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

String apnName = "devkit.nb";

String serverIP = "xxx.xxx.xxx.xxx"; // Your Server IP
String serverPort = "xxx"; // Your Server Port

String udpData = "HelloWorld";

AIS_NB_BC95 AISnb;

const long interval = 10000;  //millisecond
unsigned long previousMillis = 0;

long cnt = 0;
void setup()
{ 
  AISnb.debug = true;
  
  Serial.begin(9600);
  lcd.begin();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Connect network");
  
  AISnb.setupDevice(serverPort);

  String ip1 = AISnb.getDeviceIP();  
   lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("IP: "+ip1);
  delay(1000);
  
  pingRESP pingR = AISnb.pingIP(serverIP);
  previousMillis = millis();

}
void loop()
{ 
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
    {
      cnt++;     
           
      // Send data in String 
      UDPSend udp = AISnb.sendUDPmsgStr(serverIP, serverPort, udpData+String(cnt));
   
      //Send data in HexString     
      //udpDataHEX = AISnb.str2HexStr(udpData);
      //UDPSend udp = AISnb.sendUDPmsg(serverIP, serverPort, udpDataHEX);
      previousMillis = currentMillis;
  
    }
  UDPReceive resp = AISnb.waitResponse();
  if(resp.data.length()>0)
  {
    String udpdata =  AISnb.toString(resp.data);
    Serial.println(udpdata);
    lcd.setCursor(0,1);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print(udpdata);
  }
     
}



