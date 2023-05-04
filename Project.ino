#define pedgreen 2
#define pedred 3
#define cargreen 4
#define caryellow 5
#define carred 6
#define st_cp 7
#define ds 8
#define sh_cp 9
#define led_1 11
#define led_2 10
#define button_auto 12
#define button_manual 1
#define button_change 13
int mode;
int temp1=0;
int temp2=0;
int button_state1=0;
int button_state3=0;
int button_state2;
int button_prev1 = 0;
int button_prev2 = 0;
//byte a[] = {0xF6,0xFE,0xE0,0xBE,0xB6,0x66,0xF2,0xDA,0x60,0xFC};
byte b[] = {0x6F,0x7F,0x07,0x7D,0x6D,0x66,0x4F,0x5B,0x06,0x3F};
void setup() 
{
  for (int i = 0; i<12; i++)
  {
    pinMode(i, OUTPUT);
  }
  pinMode(12, INPUT);
  pinMode(13, INPUT);
}
void cargreentoyellow()
{
  digitalWrite(cargreen, LOW);
  digitalWrite(caryellow, HIGH);
}
void caryellowtored()
{
  digitalWrite(pedred, LOW);
  digitalWrite(caryellow, LOW);
  digitalWrite(carred,HIGH);
  digitalWrite(pedgreen, HIGH);
}
void blinklight()
{
    digitalWrite(pedgreen, HIGH);
    delay(200);
    digitalWrite(pedgreen, LOW);
    delay(200);
}
void timecount(int second)
{
   for (int j=99-second; j<100;j++)
  {
    for (int i=0; i< 370;i++) {
    digitalWrite(led_1, 1);
    digitalWrite(st_cp, LOW);
    shiftOut(ds, sh_cp, MSBFIRST, b[j%10]);
    digitalWrite(st_cp, HIGH);
    digitalWrite(led_2, 0);
    delay(1);
    digitalWrite(led_2, 1);
    digitalWrite(st_cp, LOW);
    shiftOut(ds, sh_cp, MSBFIRST, b[j/10]);
    digitalWrite(st_cp, HIGH);
    digitalWrite(led_1, 0);
    delay(1);
    /*if (carred == HIGH && j >96)
    {
      blinklight();
    }*/
    }
  }
}
void nonecrowd()
{
  digitalWrite(carred, LOW);
  digitalWrite(pedgreen, LOW);
  digitalWrite(cargreen, HIGH);
  digitalWrite(pedred, HIGH);
  timecount(2);
  cargreentoyellow();
  timecount(1);
  caryellowtored();
  timecount(2);
  digitalWrite(carred, LOW);
  digitalWrite(pedgreen,LOW);
}
void crowd()
{
  
  button_state2=digitalRead(button_change);
  if(button_state2==HIGH && button_prev2==LOW)
  {
    if (temp2==0)
    {
      digitalWrite(cargreen, HIGH);
      digitalWrite(pedred, HIGH);
      digitalWrite(carred, LOW);
      digitalWrite(pedgreen, LOW);
      temp2=1;
    }
    else
    {
      digitalWrite(cargreen, LOW);
      digitalWrite(pedred, LOW);
      digitalWrite(carred, HIGH);
      digitalWrite(pedgreen, HIGH);
      temp2=0;
    }
  }
  button_prev2=button_state2;
  
}
void loop()
{
  button_state1 = 0;
  button_state3 = 0;
  button_state1 = digitalRead(button_auto);
  button_state3 = digitalRead(button_manual);
  if(button_state1==HIGH)
  {
    mode=1;
  }
  if(button_state3==HIGH)
  {
    mode=2;
  }
  if(mode==1)
  {
    nonecrowd();
  }
  else
  {
    crowd();
  }
}
