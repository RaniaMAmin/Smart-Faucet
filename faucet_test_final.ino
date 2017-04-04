#include <sevenSegmentDisplay.h>

byte seven_seg_digits[10][7] = { 
  {
    1,1,1,1,1,1,0  }
  ,  // = 0
  {
    0,1,1,0,0,0,0  }
  ,  // = 1
  {
    1,1,0,1,1,0,1  }
  ,  // = 2
  {
    1,1,1,1,0,0,1  }
  ,  // = 3
  {
    0,1,1,0,0,1,1  }
  ,  // = 4
  {
    1,0,1,1,0,1,1  }
  ,  // = 5
  {
    1,0,1,1,1,1,1  }
  ,  // = 6
  {
    1,1,1,0,0,0,0  }
  ,  // = 7
  {
    1,1,1,1,1,1,1  }
  ,  // = 8
  {
    1,1,1,1,0,1,1  }   // = 9
};
#define threshold 200
#define norm 40
float cold =255;
float hot=255;
float temp=40;
const int firstDigit = 3;
const int secondDigit=4;
const int pinA = 6;
const int pinB = A1;
const int pinC = A2;
const int pinD = A3;
const int pinE = A4;
const int pinF = A5;
const int pinG = 2;
const int buttonUp=8;
const int buttonDown=9;
const int relayHot=10;
const int relayCold=11;
const int IR=A0;



void setup()
{
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  Serial.begin(9600);

}

void loop()
{
  digitalWrite(12, HIGH);
  int sens = irDetect();
  if(sens)
  {
    relayOut(temp);
  }
  else
  {
    analogWrite(relayCold,0);
    analogWrite(relayHot,0);
  }
  int sens2=checkButtons();
  //delay(20);
  if(sens2==1)
  {
    temp+=5;
  }
  else if(sens2==2)
  {
    temp-=5;
  }
  int fDigit = int(int(temp) % 10);
  int sDigit=int(temp/10.0);
  displayNum(fDigit, 1);
  delayMicroseconds(5);
  //delay(20);
  displayNum(sDigit, 2);
  delayMicroseconds(5);
  //delayMicroseconds(1);
  //delay(100);
  Serial.print("Temp ");
  Serial.println(temp);
//displayNum(4,1);
}

void displayNum (int num, int digit)
{
  Serial.print("IN ");
  Serial.print(num);
  Serial.print("  ");
  Serial.println(digit);
  
  if (digit==1)
  {
    digitalWrite(firstDigit, LOW);
    digitalWrite(secondDigit, HIGH);
  }
  else
  {
    digitalWrite(firstDigit, HIGH);
    digitalWrite(secondDigit, LOW);
  }
  analogWrite(pinA,seven_seg_digits[num][0]*255);
  analogWrite(pinB,seven_seg_digits[num][1]*255);
  analogWrite(pinC,seven_seg_digits[num][2]*255);
  analogWrite(pinD,seven_seg_digits[num][3]*255);
  analogWrite(pinE,seven_seg_digits[num][4]*255);
  analogWrite(pinF,seven_seg_digits[num][5]*255);
  digitalWrite(pinG,seven_seg_digits[num][6]*255);
  
}

int irDetect()
{
  int val=analogRead(IR);
  if (val<=threshold)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

int checkButtons()
{
  if(digitalRead(buttonUp)==1)
  {
    return 1;
  }
  else if(digitalRead(buttonDown)==1)
  {
    return 2;
  }
  else
  {
    return 0;
  }
}

void relayOut(int temp)
{
  float val = (temp - norm);
  if (val >=0)
  {
    cold-=(val/5)*42.5;
  }
  else
  {
    hot+=(val/5)*42.5;
  }
  analogWrite(relayHot, hot);
  analogWrite(relayCold, cold);
}

