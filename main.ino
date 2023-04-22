Arduino Nano code

// 5 seeding
// 9 Water Plant
// 3 Digging
// 12 WaterPump
// 13 PesticidesPump
// 6 MSpeed
// 2 M1
// 4 M2
// 7 M3
// 8 M4

#include <SoftwareSerial.h>
SoftwareSerial BT(10, 11);  // tx rx

#include <Servo.h>

#define WaterPump 12
#define PesticidesPump 13

#define motorPin1  2
#define motorPin2  4
#define motorPin3  7
#define motorPin4  8
#define speedPin   6
#define ModePin    A0

Servo WaterPlant9;
Servo Seeding5;
Servo Digging3;

int pos = 0;
int Mode;
char BTin;

void setup()
{
  BT.begin(9600);
  Serial.begin(115200);

  WaterPlant9.attach(9);
  Seeding5.attach(5);
  Digging3.attach(3);

  pinMode(WaterPump, OUTPUT);
  pinMode(PesticidesPump, OUTPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(speedPin, OUTPUT);
  analogWrite(speedPin, 255);

  digitalWrite(WaterPump, HIGH);
  digitalWrite(PesticidesPump, HIGH);
  Digging3.write(150);
  delay(1000);
  Seeding5.write(0);
  delay(1000);
}

void WaterPlant()
{
  for (pos = 55; pos <= 120; pos += 5)
  {
    WaterPlant9.write(pos);
    delay(15);
  }
  for (pos = 120; pos >= 55; pos -= 5)
  {
    WaterPlant9.write(pos);
    delay(15);
  }
}

void DiggingDown()
{
  Digging3.write(90);
  delay(2000);
}
void DiggingUP()
{
  Digging3.write(150);
  delay(500);
}
void SeedingPlant()
{
  Seeding5.write(90);
  delay(500);
  Seeding5.write(0);
  delay(2000);
}
void PumpON()
{
  digitalWrite(WaterPump, LOW);
  delay(500);
}
void PumpOFF()
{
  delay(500);
  digitalWrite(WaterPump, HIGH);
  delay(500);
}

void RobotMoveFront()
{
  //Serial.println("F");
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
}
void RobotMoveBack()
{
  //Serial.println("B");
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
}
void RobotMoveRight()
{
  //Serial.println("R");
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
}
void RobotMoveLeft()
{
  //Serial.println("L");
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
}
void RobotMoveStop()
{
  //Serial.println("S");
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
}


void loop()
{
  Mode = analogRead(ModePin);
  delay(100);
  //  Serial.println(Mode);
  //  delay(1000);

  if (Mode == 0)
  {
    // full digging process
    RobotMoveFront();
    delay(750);
    RobotMoveStop();
    delay(1000);
    DiggingDown();
    delay(1000);
    RobotMoveBack();
    delay(200);
    RobotMoveStop();
    delay(1000);
    DiggingUP();
    delay(1000);
    RobotMoveFront();
    delay(200);

    // full seeding process
    RobotMoveFront();
    delay(500);
    RobotMoveStop();
    delay(1000);
    SeedingPlant();
    delay(1000);

    // full watering process
    RobotMoveFront();
    delay(300);
    RobotMoveStop();
    delay(1000);
    PumpON();
    WaterPlant();
    WaterPlant();
    WaterPlant();
    PumpOFF();
    delay(1000);

    RobotMoveFront();
    delay(1250);
    RobotMoveStop();
  }
  else if (Mode > 1000)
  {
    if (BT.available() )       // If anything comes in Serial (USB),
    {
      BTin = BT.read();
      Serial.println(BTin);

      if (BTin == 'F')
      {
        RobotMoveFront();
      }
      else if (BTin == 'S')
      {
        RobotMoveStop();
      }
      else if (BTin == 'G')
      {
        RobotMoveBack();
      }
      else if (BTin == 'R')
      {
        RobotMoveRight();
      }
      else if (BTin == 'L')
      {
        RobotMoveLeft();
      }


      else if (BTin == 'M')
      {
        SeedingPlant();
        delay(1000);
      }
      else if (BTin == 'N')
      {
        digitalWrite(PesticidesPump, LOW);
        delay(2000);
        digitalWrite(PesticidesPump, HIGH);
      }
      else if (BTin == 'X')
      {
        delay(1000);
        DiggingDown();
        delay(1000);
        RobotMoveBack();
        delay(200);
        RobotMoveStop();
        delay(1000);
        DiggingUP();
        delay(1000);
      }
      else if (BTin == 'Y')
      {
        PumpON();
        WaterPlant();
        WaterPlant();
        WaterPlant();
        PumpOFF();
      }
    }
  }
}
