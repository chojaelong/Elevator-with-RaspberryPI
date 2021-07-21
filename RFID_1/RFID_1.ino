#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
SoftwareSerial a1(2,3);// 
int PIN_PIEZO = 7;  // 피에조 스피커의 변수 선언
int Pin = A0;
int flame = 0;

int melody[] = {  262,  // 도, 주파수: 262Hz~370
                  294,  // 레, 294Hz
                  330,  // 미, 330Hz
                  349,  // 파, 349Hz
                  392,  // 솔, 392Hz
                  440,  // 라, 440Hz
                  494,  // 시, 494Hz
                  523,   // 도, 523Hz
                  370   // 파#, 370Hz
};
void yes(){           
    tone(PIN_PIEZO, melody[0], 250);
    delay(250);
    tone(PIN_PIEZO, melody[2], 250);
    delay(250);
    tone(PIN_PIEZO, melody[4], 250);
}
void no(){
  for (int i=0; i<2; i++) {           // for 반복문을 통해 melody 배열에 있는 주파수를 한번씩 호출
    tone(PIN_PIEZO, melody[7], 500);  // 7번 핀에 0.5초 동안 특정 주파수의 소리가 발생하도록 전압을 인가함
    delay(1000);                      // 1초간 지연
  }
}
void fire(){
  for(int i = 400; i <= 660; i++){
    tone(PIN_PIEZO, i, 10);
    delay(10);
  }
  for(int i = 660; i >= 400; i--){
    tone(PIN_PIEZO, i, 10);
    delay(10);
  }
}
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  a1.begin(9600);
 
}
void loop() 
{
  if(a1.available()){
    char a = a1.read();
    Serial.print(a);
  }
  flame = analogRead(Pin);
  if(flame > 500){
    fire();
  }
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  //카드 : 23 7A E5 02
  //토큰 : F9 B0 8D C2
  content.toUpperCase();
  if (content.substring(1) == "F9 B0 8D C2") //change here the UID of the card/cards that you want to give access
  {
    Serial.print("9");
    a1.print("9");
    yes();
    delay(1000);
  }
 
 else   {
    //Serial.print("0");
    no();
    delay(1000);
  }
} 
