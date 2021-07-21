//7seg+remote

#include <IRremote.h>
#include <SoftwareSerial.h>
int RECV_PIN = 11; //define input pin on Arduino
IRrecv irrecv(RECV_PIN);
decode_results results;
SoftwareSerial a1(12,13);// 
int active = 0;

const unsigned int led[7] = {2,3,4,5,6,7,8};

const unsigned int num[4][7] = {
  {0,0,0,0,1,1,0},
  {1,0,1,1,0,1,1},
  {1,0,0,1,1,1,1},
  {1,1,0,0,1,1,0}
};

void display_init()
{
  for(int x=0; x<7; x++)
  {
    pinMode(led[x], OUTPUT);
  }
}

void display_clear()
{
  for(int x=0; x<7; x++)
  {
    digitalWrite(led[x], LOW);
  }
}

void display_number(int n)
{
  if(0<=n&&n<=9)
  {
    for(int x=0; x<7; x++)
    {
      digitalWrite(led[x], num[n][x]==1?HIGH:LOW);
    }
  }
}

void setup()
{
  Serial.begin(9600);
  a1.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  display_init();
}

void loop() {
  //a1.listen();
  if(a1.available()){
    char a = a1.read();
    Serial.print(a);
    if(a == '9'){
      if(active == 0){
        active = 1;
      }
      else if(active == 1){
        active = 0;
      }
    }
  }
  if (irrecv.decode(&results) && active == 1) {
      switch (results.value) {
      case 0xFF30CF: digitalWrite(6, HIGH); //1번 ON
        digitalWrite(7, HIGH);
        Serial.write("1");
        a1.write("1");
        delay(2000);
        
        digitalWrite(6, LOW); //1번 OFF
        digitalWrite(7, LOW);
        break;//1버튼이 눌리면 LED OFF
   
      case 0xFF18E7: digitalWrite(8, HIGH); //2번 ON
        digitalWrite(7, HIGH);
        digitalWrite(2, HIGH);
        digitalWrite(4, HIGH);
        digitalWrite(5, HIGH);
        Serial.write("2");
        a1.write("2");
        delay(2000);
        
        digitalWrite(8, LOW); //2번 OFF
        digitalWrite(7, LOW);
        digitalWrite(2, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        break;

      case 0xFF7A85: digitalWrite(8, HIGH); //3번 ON
        digitalWrite(7, HIGH);
        digitalWrite(6, HIGH);
        digitalWrite(5, HIGH);
        digitalWrite(2, HIGH);
        Serial.write("3");
        a1.write("3");
        delay(2000);
      
        digitalWrite(8, LOW); //3버튼 OFF
        digitalWrite(7, LOW);
        digitalWrite(6, LOW);
        digitalWrite(5, LOW);
        digitalWrite(2, LOW);
        break;
      
      case 0xFF10EF: digitalWrite(7, HIGH);  //4번 ON
      digitalWrite(6, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(2, HIGH);
      Serial.write("4");
      a1.write("4");
      delay(2000);
      
      digitalWrite(7, LOW); //4버튼 OFF
      digitalWrite(6, LOW);
      digitalWrite(3, LOW);
      digitalWrite(2, LOW);
      break;
    }
    irrecv.resume(); // Receive the next value
  }
}
