#include <Arduino.h>
#define b7 33
#define b6 32
#define b5 25
#define b4 19
#define b3 18
#define b2 17
#define b1 16
#define b0 15

#define CUENTA_2 25
#define CUENTA_1 26


int8_t cuenta = 0;


uint8_t estado[8] = {0, 0, 0, 0, 0, 0, 0, 0};
uint8_t salida[8] = { b0, b1, b2, b3, b4, b5, b6, b7};

hw_timer_s *timer1 = NULL;

volatile uint8_t incremento = 1;

volatile boolean banderaTiempo = false;

void IRAM_ATTR ISR_CUENTA_1(){
  incremento = 1;
}

void IRAM_ATTR ISR_CUENTA_2(){
  incremento = 2;
}

void IRAM_ATTR Timer1(){
  banderaTiempo = false;
}




void setup() {
  for(uint8_t i = 0; i<sizeof(salida)/sizeof(salida[i]); i++){
      pinMode(salida[i], OUTPUT);
  }
  pinMode(CUENTA_1, INPUT_PULLUP);
  pinMode(CUENTA_2, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(CUENTA_1), ISR_CUENTA_1, RISING);
  attachInterrupt(digitalPinToInterrupt(CUENTA_2), ISR_CUENTA_2, RISING);


  timer1 = timerBegin(1, 80, true);
  timerAttachInterrupt(timer1, &Timer1, true);
  timerAlarmWrite(timer1, 500000,true);
  timerAlarmEnable(timer1);
}



void loop() {
  if(banderaTiempo){
    cuenta = cuenta + incremento;
    banderaTiempo = false;
  }
 
}

