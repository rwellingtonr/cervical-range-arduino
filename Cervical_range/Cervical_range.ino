// Bibliotecas
#include <MPU6050_tockn.h>
#include <Wire.h>
// LEDS
#define pinLedYellow 6
#define pinLedGreen 5
#define pinBuzzer 3

// I2C
#define MPU6050_ADDR         0x68 
// Pre loads
// Constatantes
const int updateTime = 300;
// Variáveis
float flexion, lateral = 0;
String sessionStatus;
int ledYellowState = LOW; 
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
  // Função vem aqui!!

  // Inicializa o giroscópio
  Wire.begin();
  mpu6050.begin();
  // Log do estado inicial do sendor, caso verdadeiro
  mpu6050.calcGyroOffsets(false); 
  
  // Pisca led para demonstrar final da calibração
  // Envia evento para informar o final da calibração
  // tare();
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
    // Delay para tomada de ação
    blinkLED(500);
  }

  // Verifica se deve processar as leituras
  if(sessionStatus.equals("flexion")){  
   // envia os dados a cada Xms
    sendAnglePosition(flexion);
  }
  if(sessionStatus.equals("lateral-left") || sessionStatus.equals("lateral-right")){
      sendAnglePosition(lateral);
  }
  if(sessionStatus.equals("end") || sessionStatus.equals("abort")){
      ledsOFF();
  }
}
void sendAnglePosition(float angle){
  if(millis() - timeControl > updateTime)
  {
    int roundedAngle = round(angle);
    switchBlink();
    emmiter(roundedAngle);
    timeControl = millis();
  }
}
// Função após calibrar o sensor giroscópio - nessa funcao o paciente deve estar na posicao inicial da medicao. Acredito que na maioria dos casos deitada. Dai atraves de um botao no supervisorio faz o zeramento.
void tare(){
  blinkLED(800); //ms
  emmitString("tare");
}
//Pisca o led de acordo com o estado anterior
void switchBlink(){
  int ledGreenState = LOW;
  if(ledYellowState == LOW){
    ledYellowState = HIGH;
  }
  else{
    ledGreenState = HIGH;
    ledYellowState = LOW;
  }
  digitalWrite(pinLedYellow,ledYellowState);
  digitalWrite(pinLedGreen,ledGreenState);
}
// Pisca os leds de acordo com o delay
void blinkLED(int time){
  ledsON();
  delay(time);
  ledsOFF();
}
// Liga os leds
void ledsON(){
  digitalWrite(pinLedYellow,HIGH);
  digitalWrite(pinLedGreen,HIGH);
}
// Desliga os leds
void ledsOFF(){
    digitalWrite(pinLedYellow,LOW);
  digitalWrite(pinLedGreen,LOW);
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
// sistema visual de calibração
void statingTare(){
  digitalWrite(pinLedYellow, HIGH)
  int ms = 300
  tone(pinBuzzer,294, ms); //RE
}