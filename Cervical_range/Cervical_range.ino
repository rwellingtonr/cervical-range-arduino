// Bibliotecas
#include <MPU6050_tockn.h>
#include <Wire.h>
// LEDS
#define pinLedYellow 6
#define pinLedGreen 5

// I2C
#define MPU6050_ADDR         0x68 
// Pre loads
// Constatantes
const int updateTime = 300;
// Variáveis
float flexion, lateral = 0;
String sessionStatus;

// Variável de controle de atualização
unsigned long timeControl;

// Definições da biblioteca do giroscópio
MPU6050 mpu6050(Wire);

void setup() {
  // Inicializa a porta serial
  Serial.begin(9600);
  Serial.setTimeout(300);
  // Inicializa o giroscópio
  Wire.begin();
  mpu6050.begin();
  // Log do estado inicial do sendor, caso verdadeiro
  mpu6050.calcGyroOffsets(false); 
  
  // Define pinos de saída
  pinMode(pinLedYellow, OUTPUT);
  pinMode(pinLedGreen, OUTPUT);
  // Pisca led para demonstrar final da calibração
  // Envia evento para informar o final da calibração
  tare();
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
  if(sessionStatus.equals("lateral")){
      sendAnglePosition(lateral);
  }
}
void sendAnglePosition(float angle){
  if(millis() - timeControl > updateTime)
  {
    int roundedAngle = round(angle);
    int absoluteValue = abs(roundedAngle);
    emmiter(roundedAngle);
    timeControl = millis();
  }
}
// Função após calibrar o sensor giroscópio - nessa funcao o paciente deve estar na posicao inicial da medicao. Acredito que na maioria dos casos deitada. Dai atraves de um botao no supervisorio faz o zeramento.
void tare(){
  blinkLED(800); //ms
  emmitString("tare");
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