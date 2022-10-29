// Bibliotecas
#include <MPU6050_tockn.h>
#include <Wire.h>
// LEDS
#define pinLedYellow 5
#define pinLedGreen 6
#define pinBuzzer 3

// I2C
#define MPU6050_ADDR         0x68 
// Pre loads
// Constatantes
const int updateTime = 300;
// Variáveis
float flexion, lateral = 0;
String sessionStatus;
int ledGreenStatus = LOW; 
// Variável de controle de atualização
unsigned long timeControl;

// Definições da biblioteca do giroscópio
MPU6050 mpu6050(Wire);

void setup() {
  // Inicializa a porta serial
  Serial.begin(9600);
  Serial.setTimeout(300);
  // Define pinos de saída
  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinLedYellow, OUTPUT);
  pinMode(pinLedGreen, OUTPUT);
  // Função que informa o início da calibração
  statingTare(400);
  // Inicializa o giroscópio
  Wire.begin();
  mpu6050.begin();
  // Log do estado inicial do sendor, caso verdadeiro
  mpu6050.calcGyroOffsets(false); 
  
  // Informação visual que a calibração finalizou
  endingTare(400);
  // Informa o supervisório que a calibração acabou
  emmitString("tare");
}

void loop() {
  // Atualiza o giroscópio
  mpu6050.update();
  // pega os valores dos eixos X e Y
  flexion = mpu6050.getAngleY();
  lateral = mpu6050.getAngleX();

  // Verifica porta analógica
  if(Serial.available() > 0){
    sessionStatus = Serial.readString();
    Serial.print("Received ");
    Serial.println(sessionStatus);
   
  }

  // Verifica se deve processar as leituras
  if(sessionStatus.equals("flexion")){  
   // envia os dados a cada Xms
    startProcess(400);
    sendAnglePosition(flexion);
  }
  if(sessionStatus.equals("lateral-left") || sessionStatus.equals("lateral-right")){
      sendAnglePosition(lateral);
  }
  if(sessionStatus.equals("end") || sessionStatus.equals("abort")){
    endProcess(400);
  }
}
void sendAnglePosition(float angle){
  if(millis() - timeControl > updateTime)
  {
    int roundedAngle = round(angle);
    emmiter(roundedAngle);
    timeControl = millis();
  }
}

// Recebe um número para ser enivado na porta serial
void emmiter(int payload){
  Serial.print("Value: "); // Value: 800
  Serial.println(payload);
}
// Recebe uma palavra para ser enivada na porta serial
void emmitString(String payload){
  Serial.println(payload);
}
// Sistema visual de calibração
// Liga o led amarelo e emite um som
void statingTare(int ms){
  digitalWrite(pinLedYellow, HIGH);
  tone(pinBuzzer,294, ms); //RE
}
// Sistema visual de calibração
// Desliga o led amarelo e emite um som
void endingTare(int ms){
  digitalWrite(pinLedYellow, LOW);
  tone(pinBuzzer,294, ms); //RE
}

// Informa visualmente o inicio do processo
void startProcess(int ms){
  if(ledGreenStatus == LOW)
  {
    ledGreenStatus = HIGH;
    digitalWrite(pinLedGreen, ledGreenStatus); 
    tone(pinBuzzer, 294, ms); //RE
  }
}
// Informa visualmente o fim do processo
void endProcess(int ms){
    digitalWrite(pinLedGreen, LOW); 
    tone(pinBuzzer, 294, ms); //RE
    delay(ms/2);
    tone(pinBuzzer,349,ms); //FA
}
