// Bibliotecas

#include <MPU6050_tockn.h>
#include <Wire.h>
// LEDS
#define pinLedRed 12
#define pinLedYellow 11
#define pinLedGreen 10

// Pre loads
float angleY = 0;
float sensorFlex = 0;
char sessionStatus;
const int updateTime = 500;

unsigned long timeControl;

MPU6050 mpu6050(Wire);

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(300);
  Wire.begin();
  mpu6050.begin();
  // Log do estado inicial do sendor
  mpu6050.calcGyroOffsets(true); 
  
  // define pinos de saída
  pinMode(pinLedRed, OUTPUT);
  pinMode(pinLedYellow, OUTPUT);
  pinMode(pinLedGreen, OUTPUT);
  // Inicializar sensor flexível

  // Pisca led para demonstrar final da calibração
  // Envia evento para informar o final da calibração
  tare();
  
}

void loop() {
  mpu6050.update();
  angleY = mpu6050.getAngleY()
  if(Serial.available()){
    sessionStatus = Serial.readString();

      // Se o valor inicial é maior que zero
      // começa a processar os dados
    if(sessionStatus == "started"){

      // envia os dados a cada 500ms
      if(millis() - timeControl > updateTime){
          emmiter(angleY);
          timeControl = millis();
        }
    }

    if(sessionStatus == "stoped"){

    }
    
  }
  /* TO DO
   [] Se menor/maior (TBD) finaliza as medições
   [] Ler o valor das coletas do sensor flexível
   [] Criar função aritimética do valor coletado
   [x] Envia a cada 500ms o valor coletado do sensor flexível
  */

}

void tare(){
  blinkLED(1500); // 1,5s
  emmiter("tare");
}

void blinkLED(int time){
  ledsON();
  delay(time);
  ledsOFF()
}
void ledsON(){
  digitalWrite(pinLedRed,HIGH);
  digitalWrite(pinLedYellow,HIGH);
  digitalWrite(pinLedGreen,HIGH);
}
void ledsOFF(){
  digitalWrite(pinLedRed,LOW);
  digitalWrite(pinLedYellow,HIGH);
  digitalWrite(pinLedGreen,LOW);
}

void emmiter(float payload){
  Serial.print("Value: ");
  Serial.println(payload);
}
 
float calculateSensorFlex(){
  // aqui vai alguma função matemática
  return 3.1415;
}