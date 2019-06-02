#include <SoftwareSerial.h>
SoftwareSerial SerialGSM( 3, 2); // RX, TX pin for gsm module
int outAlarm = 12;
int ledProtect = 6;
int inSensor = 10;
int buttonState1 = HIGH;
int buttonState2 = 0;
int button = 9;
boolean w = false;
boolean b = false;
boolean tact = true;
int timer = 15;
int a = 0;
char* phone[] = {"+79992011725","+79119570218"};
int phoneNubmber = 2;

void setup() {
  delay(2000); // wait for module initialization
  pinMode(outAlarm, OUTPUT);
  digitalWrite(outAlarm, LOW);
  pinMode(ledProtect, OUTPUT);
  digitalWrite(ledProtect, LOW);
  pinMode(inSensor, INPUT);
  pinMode(button, INPUT);
  Serial.begin(9600);
  SerialGSM.begin(9600);
  SerialGSM.println("AT+CLIP=1");//caller number
  delay(100);
  SerialGSM.println("AT+CMGF=1");
  delay(100);
  SerialGSM.println("AT+CSCS=\"GSM\"");
  delay(100);
  
}

void loop() {
  buttonState1 = digitalRead(inSensor);
  if( w == true){
     Serial.println("protected");
     digitalWrite(ledProtect, HIGH);
     }
     else{
      Serial.println("unprotected");
      digitalWrite(ledProtect, LOW);
     }
  if (buttonState1 == HIGH){
    if(w == true) {
      for(a = 0; a <=  timer; a++){
        delay(1000);
        Serial.println(a);
         buttonState2 = digitalRead(button);
        if(buttonState2 == LOW){
          w = false;
          break;
        }
        }
      if(w == true){
        digitalWrite(outAlarm, HIGH);
        Serial.println("ALARM!!!");
        for(int i = 0; i < phoneNubmber ; i++){
        sms(String("ALARM!!!"), phone[i]);
        Serial.println(phone [i]);
        delay(2000);
        }
        w = false;
        }
      }
    }    
  buttonState2 = digitalRead(button);
  if(buttonState2 == LOW){
    if(tact == true){
      b =  !b; 
      if (b == false){
        w = false;
        digitalWrite(outAlarm, LOW);     
       }
      else{
        for(a = 0; a <=  timer; a++)
        {
        Serial.println(a);
        delay(1000);
         }
       w = true;
      }
     } 
   tact = false;
   
  }
  else{
    tact = true;
  }
 
}
void sms(String text, String phone)  //процедура отправки СМС
{
  Serial.println("SMS send started");
  SerialGSM.println("AT+CMGS=\"" + phone + "\"");
  delay(500);
  SerialGSM.print(text);
  delay(500);
  SerialGSM.print((char)26);
  delay(500);
  Serial.println("SMS send complete");
  delay(2000);
}
