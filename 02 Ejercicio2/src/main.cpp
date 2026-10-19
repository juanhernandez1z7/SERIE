#include <Arduino.h>
#define b0 25
#define b1 26
#define b2 27
#define b3 33
#define b4 32
#define b5 15
#define b6 16
#define b7 17

uint8_t salida [8] = {b7, b6, b5, b4 ,b3, b2, b1, b0};
boolean estados[8] = {0,0, 0 ,0 ,0, 0, 0, 0};
uint8_t cuenta = 0;
boolean banderaTiempo = false;

hw_timer_s *timer0 = NULL;

void IRAM_ATTR ISR_T0(){
  banderaTiempo = true;
}

void mostrarCuenta(){
  Serial.print("cuenta: ");
  Serial.println(cuenta);
  uint8_t dato = cuenta;
  uint8_t residuo = 0;
  uint8_t i = 1;

  for(uint8_t i = 0; i<sizeof(estados)/sizeof(estados[0]); i++){
    estados[i] = 0;
  }
  
  while(dato>0){
    residuo = dato % 2;
    dato = dato/2;
    estados[8-i] = residuo;
    //Serial.print(residuo);
    i++;
  }
  //Serial.println();
  for(uint8_t i = 0; i<sizeof(estados)/sizeof(estados[0]); i++){
    digitalWrite(salida[i], estados[i]);
  } 

}

void setup() {
  //Configuración de puertos
  for(uint8_t i = 0; i<sizeof(salida)/sizeof(salida[0]); i++){
    pinMode(salida[i], OUTPUT);
  }
  //Comunicación Serial
  Serial.begin(115200);
  Serial.print("cuenta: ");
  Serial.println(cuenta);

  //Configuración de T0 
  timer0 = timerBegin(0, 800, true);
  timerAttachInterrupt(timer0, &ISR_T0,true);
  timerAlarmWrite(timer0, 25000, true);
  timerAlarmEnable(timer0);

  mostrarCuenta();  
}

void loop() {
  if(banderaTiempo){
    cuenta++;
    mostrarCuenta();
    banderaTiempo = false;
  }  
 
}

