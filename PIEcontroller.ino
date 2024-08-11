#include <ps4.h>
#include <PS4Controller.h>
#include <ps4_int.h>

#define motor1LPWM 2
#define motor1RPWM 4

#define motor2LPWM 13 //mudar para pinos conectados a ponte h
#define motor2RPWM 12

#define macAdd "00:00:00:00:00:00"  //mudar para endereco mac do controle

#define maxDutyCicle 255 //max 255

#define zonaMorta 30 //max 255

void setup() {
  PS4.begin(macAdd);
  Serial.begin(9600);

  while (!PS4.isConnected()) {
    Serial.println("Esperando Conexão");
    delay(250);
  }

  PS4.setLed(100, 0, 0); //muda a cor do led do controle
  PS4.sendToController();

  Serial.println("Conexão Estabelecida");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (PS4.isConnected()) {
    int RStickY = PS4.RStickY();
    int LStickY = PS4.LStickY();

    int Motor1Output = constrain(map(LStickY, -127, 127, -maxDutyCicle, maxDutyCicle), -255, 255);
    int Motor2Output = constrain(map(RStickY, -127, 127, -maxDutyCicle, maxDutyCicle), -255, 255);

    if (Motor1Output > zonaMorta) {
      analogWrite(motor1RPWM, Motor1Output);
      analogWrite(motor1LPWM, 0);
    } else if (Motor2Output < -zonaMorta) {
      analogWrite(motor1LPWM, abs(Motor1Output));
      analogWrite(motor1RPWM, 0);
    } else {
      analogWrite(motor1RPWM, 0);
      analogWrite(motor1LPWM, 0);
    }

    if (Motor2Output > zonaMorta) {
      analogWrite(motor2RPWM, Motor2Output);
      analogWrite(motor2LPWM, 0);
    } else if (Motor2Output < -zonaMorta) {
      analogWrite(motor2LPWM, abs(Motor2Output));
      analogWrite(motor2RPWM, 0);
    } else {
      analogWrite(motor2RPWM, 0);
      analogWrite(motor2LPWM, 0);
    }
  } else {
    analogWrite(motor2LPWM, 0);
    analogWrite(motor1LPWM, 0);
    analogWrite(motor1RPWM, 0);    
    analogWrite(motor2RPWM, 0); 
  }
}
