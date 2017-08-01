#include <SPI.h>
#include <RF24.h>

RF24 radio(9, 10);
byte addresses[][6] = {"14136", "17176"};
bool radioNumber = 1;
bool role = 1;

int flexsensor1 = A0;
int flexsensor2 = A1;
int flexsensor3 = A2;
int flexsensor4 = A3;
const int  button = 7;

struct test {
  int flexsensor1_val;
  int flexsensor2_val;
  int flexsensor3_val;
  int flexsensor4_val;
  int button_val;
} go;

boolean bu = 0;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1, addresses[0]);
  radio.setPayloadSize(32);
  pinMode(button, INPUT);
}

void loop() {

  flexsensor1 = analogRead(A0);
  flexsensor2 = analogRead(A1);
  flexsensor3 = analogRead(A2);
  flexsensor4 = analogRead(A3);
  bu = digitalRead(button);

  go.flexsensor1_val = map(flexsensor1, 200, 395, 100, 0);
  go.flexsensor2_val = map(flexsensor2, 240, 470, 100, 0);
  go.flexsensor3_val = map(flexsensor3, 190, 490, 100, 0);
  go.flexsensor4_val = map(flexsensor4, 100, 280, 100, 0);
  if (bu == 0) {
    go.button_val = 0;
  }
  if (bu == 1) {
    go.button_val = 1;
  }

  Serial.println(go.flexsensor1_val);
  Serial.println(go.flexsensor2_val);
  Serial.println(go.flexsensor3_val);
  Serial.println(go.flexsensor4_val);
  Serial.println(go.button_val);

  radio.stopListening();
  delay(50);

  radio.write(&go, sizeof(go));

  radio.startListening();
}
