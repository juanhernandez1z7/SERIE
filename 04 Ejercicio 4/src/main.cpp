#include <Arduino.h>

#define salida_A 15
#define salida_B 16
#define salida_C 17
#define salida_D 26

#define entrada_INT 25


int8_t cuenta = 0;


uint8_t estado[4] = {0, 0, 0, 0};
uint8_t salida[4] = { salida_A, salida_B, salida_C, salida_D};

void mostrarCuenta(){  
 for(uint8_t i = 0; i<sizeof(estado)/sizeof(estado[i]); i++){
      estado[i] = 0;
  }

  uint8_t dato = cuenta;
  uint8_t residuo = 0;
  uint8_t i = 1;

  while(dato>0){
    residuo = dato%2;
    dato= dato/2;
    estado[4-i] = residuo;
    i++;
  } 

  Serial.print("cuenta: ");
  Serial.println(cuenta);

  for(uint8_t i = 0; i<sizeof(estado)/sizeof(estado[i]); i++){
      digitalWrite(salida[i], estado[i]);
  }
  
}

void setup() {
  //Configuración de terminales
 
  pinMode(salida_A, OUTPUT);
  pinMode(salida_B, OUTPUT);
  pinMode(salida_C, OUTPUT);
  pinMode(salida_D, OUTPUT);

  pinMode(entrada_INT, INPUT_PULLUP);  

  Serial.begin(115200);

  
}

void loop() {
  if(digitalRead(entrada_INT)){
    cuenta++;
    if(cuenta>10){
      cuenta = 0;
    }
    mostrarCuenta();
  }else {
    cuenta--;
    if(cuenta<0){
      cuenta = 10;
    }
    mostrarCuenta();
  }
  delay(500);
  
}

