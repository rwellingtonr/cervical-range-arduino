
#include <MPU6050_tockn.h>
#include <Wire.h>
// Leds
#define pinLedRed 13
#define pinLedYellow 12
#define pinLedGreen 11

// valor do ângulo, alterar para o eixo a ser utilizado
float initalAngleValue, angleY = 0;

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
  // Pisca led para demonstrar final da calibração
  // Envia evento para informar o final da calibração
  tare();
  setIntialValue();
}

void loop() {
  mpu6050.update();
  
  Serial.print("angleX : ");
  Serial.print(mpu6050.getAngleX());
  Serial.print("\tangleY : ");
  Serial.print(mpu6050.getAngleY());
  Serial.print("\tangleZ : ");
  Serial.println(mpu6050.getAngleZ());
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
  Serial.print(event)
}
void setIntialValue(){
    mpu6050.update();
    initalAngleValue = mpu6050.getAngleY();
} 
