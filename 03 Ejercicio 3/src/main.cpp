#include <Arduino.h>
#define entrada_A 25
#define entrada_B 26
#define entrada_C 27

#define salida_A 15
#define salida_B 16
#define salida_C 17

#define INTERRUPCION 32

volatile boolean bandera = false;


uint8_t entrada[3] = { entrada_A, entrada_B, entrada_C};
uint8_t salida[3] = { salida_A, salida_B, salida_C};

void IRAM_ATTR ISR_INT(){
  bandera = true;
}

void setup() {
  //Configuración de terminales
  pinMode(entrada_A, INPUT_PULLUP);
  pinMode(entrada_B, INPUT_PULLUP);
  pinMode(entrada_C, INPUT_PULLUP);
  pinMode(salida_A, OUTPUT);
  pinMode(salida_B, OUTPUT);
  pinMode(salida_C, OUTPUT);
  pinMode(INTERRUPCION, INPUT_PULLUP);  

  //Configuración de interrupciones Externas
  attachInterrupt(digitalPinToInterrupt(INTERRUPCION), ISR_INT, RISING);

}

void loop() {
  if(bandera){
    for(uint8_t i = 0; i<sizeof(entrada)/sizeof(entrada[i]); i++){
      digitalWrite(salida[i], digitalRead(entrada[i]));
    }
    bandera = false;
  }
  
}

