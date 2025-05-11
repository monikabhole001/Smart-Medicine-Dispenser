#include <Keypad.h>
#include<LiquidCrystal_I2C.h>
#include <Wire.h>
#include "DS1307.h"
#include<Servo.h>

Servo s1, s2,s3;
DS1307 clock;

const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal_I2C lcd(0x27,20,4);
const byte ROWS = 4; //four rows
const byte COLS = 3; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {8, 7, 6, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 3, 2}; //connect to the column pinouts of the keypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
long k = 0;

boolean clean = false;
boolean enter = false;
int ir = 9;

class Time
{
  public:
      int hour_tens, hour_ones, min_tens, min_ones;
      String current_time = "";
      boolean setted,done ;
      Time(int a, int b, int c, int d, boolean e)
      {
        hour_tens = a;
        hour_ones = b;
        min_tens = c;
        min_ones = d;
        setted = e;
        done = false;
      }
      Time()
      {
        hour_tens = 0;
        hour_ones = 0;
        min_tens = 0;
        min_ones = 0;
        setted = false;
        done = false;
      }
      String getTime()
      {
        current_time = String(hour_tens) + String(hour_ones) + ":" + String(min_tens) + String(min_ones);
        return(current_time);
      }
};

Time current;
int count = 3;
Time alarms[3][3] = {{Time(),Time(),Time()},{Time(),Time(),Time()},{Time(),Time(),Time()}};
int AlarmCount[3] = {0,0,0};

void CurrentTime(Time *temp)
{
  int time_temp;
  clock.getTime();
  time_temp = clock.hour;
  temp->hour_tens = time_temp/10;
  temp->hour_ones = time_temp%10;
  time_temp = clock.minute;
  temp->min_tens = time_temp/10;
  temp->min_ones = time_temp%10;
}

void PrintTimeTopRight(Time temp)
{
  lcd.setCursor(15,0);
  lcd.print(temp.hour_tens);
  lcd.setCursor(16,0);
  lcd.print(temp.hour_ones);
  lcd.setCursor(17,0);
  lcd.print(":");
  lcd.setCursor(18,0);
  lcd.print(temp.min_tens);
  lcd.setCursor(19,0);
  lcd.print(temp.min_ones);  
}

void PrintDateTopLeft()
{
  int Date = clock.dayOfMonth;
  int Month = clock.month;
  int Year = clock.year + 2000;
  lcd.setCursor(0,0);
  if(Date < 10)
  { 
    lcd.print("0");
    lcd.setCursor(1,0);
    lcd.print(Date);
  }
  else
  {
    lcd.print(Date/10);
    lcd.setCursor(1,0);
    lcd.print(Date%10);
  }
  lcd.setCursor(2,0);
  lcd.print(":");
  lcd.setCursor(3,0);
  if(Month < 10)
  {
    lcd.print("0");
    lcd.setCursor(4,0);
    lcd.print(Month);
  }
  else
  {
    lcd.print(Month/10);
    lcd.setCursor(4,0);
    lcd.print(Month%10);
  }
  lcd.setCursor(5,0);
  lcd.print(":");
  lcd.setCursor(6,0);
  lcd.print(Year);
}

void PrintDayTopMid()
{
  lcd.setCursor(11,0);
  int dayint = clock.dayOfWeek;
  Serial.println(dayint);
  switch (clock.dayOfWeek)
  {
    case 1:
      lcd.print("MON");
      break;
    case 2:
      lcd.print("TUE");
      break;
    case 3:
      lcd.print("WED");
      break;
    case 4:
      lcd.print("THU");
      break;
    case 5:
      lcd.print("FRI");
      break;
    case 6:
      lcd.print("SAT");
      break;
    case 7:
      lcd.print("SUN");
      break;
  }
}

void getPassword()
{
  lcd.clear();
  lcd.print("Enter the password");
  char key;
  String pass = "";
  int count = 0;
  while(1)
  {
    if(count == 4 && pass == "9876")
    {
      break;
    }
    else if(count < 4)
    {
      key = customKeypad.waitForKey();
      pass = pass + key;
      lcd.setCursor(0,0);
      lcd.print("Enter the password");
      lcd.setCursor(0,1);
      lcd.print(pass);
    }
    else
    {
      lcd.clear();
      lcd.print("INCORRECT PASSWORD");
      delay(1000);
      count = -1;
      pass = "";
      lcd.clear();
      lcd.print("Enter the password");
    }
    count++;
  }
  lcd.clear();
  lcd.print("PASSWORD ACCEPTED");
  delay(1000);
  lcd.clear();
}

void setAlarm()
{
  lcd.clear();
  lcd.print("How many types of");
  lcd.setCursor(0,1);
  lcd.print("pills?");
  count = customKeypad.waitForKey()-48;
  lcd.setCursor(0,2);
  lcd.print(count);
  delay(1000);
  int ht,ho,mt,mo;
  
  for(int i=0;i<count;i++)
  {
    lcd.clear();
    lcd.print("For pill ");
    lcd.setCursor(10,0);
    lcd.print(i+1);
    delay(1000);
    AlarmCount[i] = customKeypad.waitForKey()-48;
    lcd.setCursor(0,1);
    lcd.print(AlarmCount[i]);
    delay(1000);
    if(AlarmCount[i] >=1 && AlarmCount[i] <=3)
    { for(int j=0; j<AlarmCount[i];j++)
      {
        while(1)
        {
          lcd.clear();
          lcd.setCursor(0,i);
          lcd.print("Alarm");
          lcd.setCursor(6,i);
          lcd.print(j+1);
          lcd.setCursor(7,i);
          lcd.print("=> ");
          lcd.setCursor(12,i);
          lcd.print(":");
          ht = customKeypad.waitForKey()-48;
          lcd.setCursor(10,i);
          lcd.print(ht);
          ho = customKeypad.waitForKey()-48;
          lcd.setCursor(11,i);
          lcd.print(ho);
          mt = customKeypad.waitForKey()-48;
          lcd.setCursor(13,i);
          lcd.print(mt);
          mo = customKeypad.waitForKey()-48;
          lcd.setCursor(14,i);
          lcd.print(mo);
          if(ht == 0 or ht == 1)
          {
            if(0 <= ho and ho<= 9)
            {
              if(0 <= mt and mt <=5)
              {
                if(0 <= mo and mo <= 9)
                {
                  alarms[i][j] = Time(ht,ho,mt,mo,true);
                  lcd.setCursor(0,3);
                  lcd.print("alarm accepted");
                  delay(1500);
                  lcd.clear();
                  break;
                }
              }
              else
              {
                lcd.clear();
                lcd.print("INVALID ALARM");
                lcd.setCursor(0,3);
                lcd.print("Please enter again");
                delay(1500);
              }
            }
          }
          else if(ht == 2)
          {
            if(0 <= ho and ho <= 4)
            {
              if(0 <= mt and mt <=5)
              {
                if(0 <= mo and mo <= 9)
                {
                  alarms[i][j] = Time(ht,ho,mt,mo,true);
                  lcd.setCursor(0,3);
                  lcd.print("alarm accepted");
                  delay(1500);
                  lcd.clear();
                  break;
                }
              }
              else
              {
                lcd.clear();
                lcd.print("INVALID ALARM");
                lcd.setCursor(0,3);
                lcd.print("Please enter again");
                delay(1500);
              }
            }
            else
            {
               lcd.clear();
               lcd.print("INVALID ALARM");
               lcd.setCursor(0,3);
               lcd.print("Please enter again");
               delay(1500);
            }
          }
          else
          {
            lcd.clear();
            lcd.print("INVALID ALARM");
            lcd.setCursor(0,3);
            lcd.print("Please enter again");
            delay(1500);
          }
        }
      }
    }
    else
    {
      lcd.clear();
      lcd.print("INVALID ALARM");
      delay(1500);
    }
  }
  clean = false;
}

void checkAlarm()
{
  Time temp;
  String str;
  int reading,kount = 0;
  for(int i=0;i<count;i++)
  {
    for(int j=0;j<AlarmCount[i];j++)
    {
      temp = alarms[i][j];
      boolean b1 = current.hour_tens == temp.hour_tens;
      boolean b2 = current.hour_ones == temp.hour_ones;
      boolean b3 = current.min_tens == temp.min_tens;
      boolean b4 = current.min_ones == temp.min_ones;
      if(b1 and b2 and b3 and b4 and temp.setted and !temp.done)
      {
        alarms[i][j].done = true;
        lcd.clear();
        str = "For pill " + String(i+1);
        lcd.print(str);
        str = "Alarm " + String(j+1);
        lcd.setCursor(0,1);
        lcd.print(str);
        lcd.setCursor(0,2);
        lcd.print("Put your hand below");
        lcd.setCursor(0,3);
        lcd.print("to get the pill");
        while(kount < 28)
        {
          reading = digitalRead(ir);
          if(reading == 0)
          {
            kount = 0;
            servo(i+1);
            delay(5000);
            break;     
          }
          buzzer();
          kount++;
        }
        lcd.clear();
      }
    }
  }
}

void servo(int i)
{
  if(i == 1)
  {
    for(int i=0; i<110; i+= 10)
    {
      s1.write(i);
      delay(20);
    }
    delay(2000);
    for(int i=100; i>=0; i-= 10)
    {
      s1.write(i);
      delay(20);
    }
  }

  if(i == 2)
  {
    for(int i=0; i<110; i+= 10)
    {
       s2.write(i);
       delay(20);
    }
    delay(2000);
    for(int i=100; i>=0; i-= 10)
    {
      s2.write(i);
      delay(20);
    }
  }

  if(i == 3)
  {
    for(int i=0; i<110; i+= 10)
    {
      s3.write(i);
      delay(20);
    }
    delay(2000);
    for(int i=100; i>=0; i-= 10)
    {
      s3.write(i);
      delay(20);
    }
  }
}

void buzzer()
{
  digitalWrite(11,HIGH);
  delay(1000);
  digitalWrite(11,LOW);
  delay(100);
   digitalWrite(11,HIGH);
  delay(500);
  digitalWrite(11,LOW);
  delay(100);
   digitalWrite(11,HIGH);
  delay(500);
  digitalWrite(11,LOW);
}

void setup() {
  // put your setup code here, to run once:
  lcd.begin(20,4);
  lcd.backlight();
  lcd.clear();
  CurrentTime(&current);
  lcd.clear();
  clean =  false;
  
  clock.begin();
  
  s1.attach(13);  s1.write(0);
  s2.attach(12);  s2.write(0);
  s3.attach(10);  s3.write(0);

  pinMode(ir,INPUT);
  pinMode(11,OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(k % 96 == 0)
  {
    lcd.clear();
    k = 0;
  }
  k++;
  CurrentTime(&current);
  PrintDateTopLeft();
  PrintDayTopMid();
  PrintTimeTopRight(current);
  lcd.setCursor(0,1);
  lcd.print("Have a nice day ^_^");
  lcd.setCursor(0,3);
  lcd.print("press # for alarm");
  lcd.noCursor();
  char input = customKeypad.getKey();
  if(input == '#')
  {
    getPassword();
    setAlarm();
    clean = false;
  }
  checkAlarm();
}
