#include <SoftwareSerial.h>
//SoftwareSerial se2(0, 1);
#define d 100
int pins[17] = { -1, 10, 11, 12, 13, 14, 15, 16, 17, 2, 3, 4, 5, 6, 7, 8, 9};
int cols[8] = {pins[13], pins[3], pins[4], pins[10], pins[6], pins[11], pins[15], pins[16]};
int rows[8] = {pins[9], pins[14], pins[8], pins[12], pins[1], pins[7], pins[2], pins[5]};
int pre = 0;
char data;
void setup()
{
  // 1~16번 까지의 핀을 출력으로 설정
  for (int i = 1; i <= 16; i++) {
    pinMode(pins[i], OUTPUT);
  }
  for (int i = 0; i < 8; i++) {
    digitalWrite(cols[i], HIGH );
    digitalWrite(rows[i], HIGH);
  }
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available()) {
    data = Serial.read();
    Serial.print(data);
    switch (data)
    {
      case '1' : {
          clear();
          if (pre > 1) {
            for (int i = (pre * 2) - 1; i >= 0; i--) {
              digitalWrite(cols[i], LOW);
              delay(d);
            }
            clear();
            delay(d);
            digitalWrite(cols[0], LOW);
            digitalWrite(cols[1], LOW);
          } else
          {
            digitalWrite(cols[0], LOW);
            digitalWrite(cols[1], LOW);
          }
          pre = 1;
          break;

        }
      case '2' : {
          clear();
          if (pre>2)
          {
            for (int i =(pre*2-1); i > 1; i--) {
              digitalWrite(cols[i], LOW);
              delay(d);
            }
            clear();
            delay(d);
            digitalWrite(cols[2], LOW);
            digitalWrite(cols[3], LOW);
          }else if (pre == 1)
          {
            for (int i = 0; i < 4; i++) {
              digitalWrite(cols[i], LOW);
              delay(d);
            }
            clear();
            delay(d);
            digitalWrite(cols[2], LOW);
            digitalWrite(cols[3], LOW);
          } else if (pre == 2)
          {
            digitalWrite(cols[2], LOW);
            digitalWrite(cols[3], LOW);
          }
          pre = 2;
          break;
        }
      case '3' : {
          clear();
          if (pre == 4)
          {
            for (int i = 7; i > 3; i--) {
              digitalWrite(cols[i], LOW);
              delay(d);
            }
            clear();
            delay(d);
            digitalWrite(cols[4], LOW);
            digitalWrite(cols[5], LOW);
          } else if (pre == 2)
          {
            for (int i = 2; i < 6; i++) {
              digitalWrite(cols[i], LOW);
              delay(d);
            }
            clear();
            delay(d);
            digitalWrite(cols[4], LOW);
            digitalWrite(cols[5], LOW);
          } else if (pre == 1)
          {
            for (int i = 0; i < 6; i++) {
              digitalWrite(cols[i], LOW);
              delay(d);
            }
            clear();
            delay(d);
            digitalWrite(cols[4], LOW);
            digitalWrite(cols[5], LOW);
          } else if (pre == 3)
          {
            digitalWrite(cols[4], LOW);
            digitalWrite(cols[5], LOW);
          }
          pre = 3;
          break;
        }

      case '4' : {
          clear();
          if (pre == 1)
          {
            for (int i = 0; i < 8; i++) {
              digitalWrite(cols[i], LOW);
              delay(d);
            }
            clear();
            delay(d);
            digitalWrite(cols[6], LOW);
            digitalWrite(cols[7], LOW);
          }
          else if (pre == 2)
          {
            for (int i = 2; i < 8; i++) {
              digitalWrite(cols[i], LOW);
              delay(d);
            }
            clear();
            delay(d);
            digitalWrite(cols[6], LOW);
            digitalWrite(cols[7], LOW);
          }
          else if (pre == 3)
          {
            for (int i = 4; i < 8; i++) {
              digitalWrite(cols[i], LOW);
              delay(d);
            }
            clear();
            delay(d);
            digitalWrite(cols[6], LOW);
            digitalWrite(cols[7], LOW);
          } else if (pre == 4)
          {
            digitalWrite(cols[6], LOW);
            digitalWrite(cols[7], LOW);
          }
          pre = 4;
          break;
        }

    }
  }
}
void clear() // 사용자 정의함수 clear 선언
{
  for (int i = 1; i < 9 ; i++) // LED 초기화 for문
  {
    digitalWrite(rows[i], HIGH);
    digitalWrite(cols[i], HIGH);
  }
}
