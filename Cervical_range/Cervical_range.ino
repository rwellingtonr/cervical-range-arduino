
#include <MPU6050_tockn.h>
#include <Wire.h>
// Leds
#define pinLedRed 12
#define pinLedYellow 11
#define pinLedGreen 10

// valor do ângulo, alterar para o eixo a ser utilizado
float initalAngleValue, angleY = 0;
float sensorFlex = 0;

MPU6050 mpu6050(Wire);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(false); // remove logs de calibração
  
  // define pinos de saída
  pinMode(pinLedRed, OUTPUT);
  pinMode(pinLedYellow, OUTPUT);
  pinMode(pinLedGreen, OUTPUT);
  // Inicializar sensor flexível

  // Pisca led para demonstrar final da calibração
  // Envia evento para informar o final da calibração
  tare(500);
  // defini valor inicial do sensor giroscópio
  setIntialValue();
}

void loop() {
  mpu6050.update();
  angleY = mpu6050.getAngleY()

  /* TO DO
   [] Se menor/maior (TBD) finaliza as medições
   [] Ler o valor das coletas do sensor flexível
   [] Criar função aritimética do valor coletado
   [] Envia a cada 200ms o valor coletado do sensor flexível
  */
  
}

void tare(int time){
  digitalWrite(pinLedRed,HIGH);
  digitalWrite(pinLedYellow,HIGH);
  digitalWrite(pinLedGreen,HIGH);
  delay(time);
  emmiter("tare");
  digitalWrite(pinLedRed,LOW);
  digitalWrite(pinLedYellow,HIGH);
  digitalWrite(pinLedGreen,LOW);
 }

void emmiter(char event){
  Serial.print(event);
}
void setIntialValue(){
    mpu6050.update();
    initalAngleValue = mpu6050.getAngleY();
} 

float calculateSensorFlex(){
  // aqui vai alguma função matemática
  return 3.1415;
}
