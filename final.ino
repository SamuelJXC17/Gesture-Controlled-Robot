#include <SPI.h>
#include <RF24.h>
#include <Servo.h>

bool radioNumber = 0;
RF24 radio(A0, A1);
byte addresses[][6] = {"14136", "17176"};
bool role = 0;

int f1_val;
int f2_val;
int f3_val;
int f4_val;
int b_val;

struct test {
  int flexsensor1_val;
  int flexsensor2_val;
  int flexsensor3_val;
  int flexsensor4_val;
  int button_val;
} go;

Servo servopan;
Servo servotilt;
Servo servoclaw;

int pos1 = 0;
int pos2 = 0;
int pos3 = 0;

int dir1PinA = 2;
int dir2PinA = 4;
int speedPinA = 6;

int dir1PinB = 7;
int dir2PinB = 8;
int speedPinB = 5;

int loc1 = 0;
int loc2 = 0;
int loc3 = 0;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1, addresses[1]);
  radio.startListening();

  servoclaw.attach(10);
  servotilt.attach(3);
  servopan.attach(9);

  pinMode(dir1PinA, OUTPUT);
  pinMode(dir2PinA, OUTPUT);
  pinMode(speedPinA, OUTPUT);
  pinMode(dir1PinB, OUTPUT);
  pinMode(dir2PinB, OUTPUT);
  pinMode(speedPinB, OUTPUT);
}

void loop() {
  delay(50);
  if (radio.available()) {
    (radio.read(&go, sizeof(go)));

  } else {
  }
  Serial.print(go.flexsensor1_val);
  Serial.print("\t");
  Serial.print(go.flexsensor2_val);
  Serial.print("\t");
  Serial.print(go.flexsensor3_val);
  Serial.print("\t");
  Serial.print(go.flexsensor4_val);
  Serial.print("\t");
  Serial.print(go.button_val);
  Serial.print("\t");

  f1_val = go.flexsensor1_val;
  f2_val = go.flexsensor2_val;
  f3_val = go.flexsensor3_val;
  f4_val = go.flexsensor4_val;
  b_val = go.button_val;

  servoclaw.write(30);
  servotilt.write(90);
  servopan.write(120);

  if (b_val == 1)
  {
    int (var)  = Serial.read();
    int speed;

    if (f1_val > 70 && f2_val < 70 && f3_val < 70 && f4_val < 70) //1 = Forward
    {
      analogWrite(speedPinA, 255);
      digitalWrite(dir1PinA, LOW);
      digitalWrite(dir2PinA, HIGH);
      Serial.println("Motor 1 Forward");
      Serial.println("   ");
      analogWrite(speedPinB, 255);
      digitalWrite(dir1PinB, LOW);
      digitalWrite(dir2PinB, HIGH);
      Serial.println("Motor 2 Forward");
      Serial.println("   ");
    }

    else if (f1_val < 70 && f2_val < 70 && f3_val < 70 && f4_val < 70) //None = Stop
    {
      analogWrite(speedPinA, 0);
      digitalWrite(dir1PinA, HIGH);
      digitalWrite(dir2PinA, LOW);
      Serial.println("Motor 1 Stop");
      Serial.println("   ");
      analogWrite(speedPinB, 0);
      digitalWrite(dir1PinB, HIGH);
      digitalWrite(dir2PinB, LOW);
      Serial.println("Motor 2 Stop");
      Serial.println("   ");
    }

     else if (f1_val < 70 && f2_val > 70 && f3_val < 70 && f4_val < 70) // 2 = reverse
    {
      analogWrite(speedPinA, 255);
      digitalWrite(dir1PinA, HIGH);
      digitalWrite(dir2PinA, LOW);
      Serial.println("Motor 1 Reverse");
      Serial.println("   ");
      analogWrite(speedPinB, 255);
      digitalWrite(dir1PinB, HIGH);
      digitalWrite(dir2PinB, LOW);
      Serial.println("Motor 2 Reverse");
      Serial.println("   ");
    }

    else if (f1_val < 70 && f2_val < 70 && f3_val > 70 && f4_val < 70) //  3 = Forward Turn A
    {
      analogWrite(speedPinB, 255);
      digitalWrite(dir1PinB, HIGH);
      digitalWrite(dir2PinB, LOW);
      Serial.println("Motor 2 Forward");
      Serial.println("   ");
      analogWrite(speedPinA, 255);
      digitalWrite(dir1PinA, LOW);
      digitalWrite(dir2PinA, HIGH);
      Serial.println("Motor 1 Reverse");
      Serial.println("   ");
    }

    else if (f1_val < 70 && f2_val < 70 && f3_val < 70 && f4_val > 70) // 4 = Forward Turn B
    {
      analogWrite(speedPinA, 255);
      digitalWrite(dir1PinA, LOW);
      digitalWrite(dir2PinA, HIGH);
      Serial.println("Motor 1 Forward");
      Serial.println("   ");
      analogWrite(speedPinB, 255);
      digitalWrite(dir1PinB, HIGH);
      digitalWrite(dir2PinB, LOW);
      Serial.println("Motor 2 Reverse");
      Serial.println("   ");
    }
  }
  if (b_val == 0)
  {
    if (f1_val > 0)
    {
      loc1 = map(f1_val, 0, 100, 30, 90);
      servoclaw.write (loc1);
    }

    if (f2_val > 0)
    {
      loc2 = map(f2_val, 0, 100, 90, 180);
      servotilt.write (loc2);
    }


    if (f3_val > 0)
    {
      loc3 = map(f3_val, 0, 100, 0, 175);
      servopan.write (loc3);
    }
  }
}

