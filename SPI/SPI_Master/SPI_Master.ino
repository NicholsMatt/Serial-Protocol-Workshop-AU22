#include <SPI.h>
#define LED_PIN 4
#define button 3
#define CS_1 10
#define CS_2 9
int button_state;
int x;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  pinMode(button_state, INPUT);
  pinMode(LED_PIN, OUTPUT);

  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);

  digitalWrite(CS_1, HIGH); //Active Low
  digitalWrite(CS_2, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  byte msend, mrcv;
  button_state = digitalRead(button);

  if(button_state == HIGH){
    x = 1;
  }
  else{
    x = 0;
  }

  digitalWrite(CS_1, LOW);
  digitalWrite(CS_2, LOW);
  
  msend = x;
  mrcv = SPI.transfer(msend);

  if(mrcv == 1){
    digitalWrite(LED_PIN, HIGH);
    Serial.println("ON");
  }
  else{
    digitalWrite(LED_PIN, LOW);
    Serial.println("OFF");
  }

  delay(10);
}


