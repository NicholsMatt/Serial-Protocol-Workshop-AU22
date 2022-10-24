#include <SPI.h>
#define LED_PIN 4
#define BUTTON_PIN 3
volatile boolean rcv;
volatile byte ppherrcv, pphersend;
int button_state;
int x;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(MISO, OUTPUT);
  SPCR |= _BV(SPE);
  rcv = false;
  SPI.attachInterrupt();
}

ISR (SPI_STC_vect){
  ppherrcv = SPDR;
  rcv = true;
}

void loop() {
  // put your main code here, to run repeatedly:
  if(rcv){
    if(ppherrcv == 1){
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED ON");
    }
    else{
      digitalWrite(LED_PIN, LOW);
      Serial.println("LED OFF");
    }
  }

  button_state = digitalRead(BUTTON_PIN);

  if(button_state == HIGH){
    x = 1;
  }
  else{
    x = 0;
  }

  pphersend = x;
  SPDR = pphersend;
  delay(10);
}
