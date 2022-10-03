// Bibliotecas
#include <MPU6050_tockn.h>
#include <Wire.h>
// LEDS
#define pinLedRed 12
#define pinLedYellow 11
#define pinLedGreen 10

// Pre loads
// Constatantes
const int updateTime = 300;
// Variáveis
float angleY = 0;
int repeated = 0;
int timesToRepeat = 1;
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
  mpu6050.calcGyroOffsets(true); 
  
  // Define pinos de saída
  pinMode(pinLedRed, OUTPUT);
  pinMode(pinLedYellow, OUTPUT);
  pinMode(pinLedGreen, OUTPUT);
  // Pisca led para demonstrar final da calibração
  // Envia evento para informar o final da calibração
  tare();
}

void loop() {
  mpu6050.update();
  angleY = mpu6050.getAngleY();

  // Verifica porta analógica
  if(Serial.available() > 0){
    sessionStatus = Serial.readString();
    blinkLED(500);
    emmitString(sessionStatus);
    if(sessionStatus.equals("start")){
      maxTimesToRepeat();
    }
    // Delay para tomada de ação
    delay(500);
  }
  // Finaliza a leitura
  if(repeated == timesToRepeat){
    sessionStatus = "end";
    emmitString("end");
    repeated = 0;
  }
  // Verifica se deve processar as leituras
  if(sessionStatus.equals("start")){    
   // envia os dados a cada Xms
    if(millis() - timeControl > updateTime){
        emmiter(angleY);
        timeControl = millis();
        repeated++;
    }
  }
}
// Função após calibrar o sensor giroscópio
void tare(){
  blinkLED(800); 
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
  digitalWrite(pinLedRed,HIGH);
  digitalWrite(pinLedYellow,HIGH);
  digitalWrite(pinLedGreen,HIGH);
}
// Desliga os leds
void ledsOFF(){
  digitalWrite(pinLedRed,LOW);
  digitalWrite(pinLedYellow,LOW);
  digitalWrite(pinLedGreen,LOW);
}
// Recebe um número para ser enivado na porta serial
void emmiter(float payload){
  Serial.print("Value: "); // Value: 800
  Serial.println(payload);
}
// Recebe uma palavra para ser enivada na porta serial
void emmitString(String payload){
  Serial.println(payload);
}

// Retorna a quantidade de vezes que irá repetir
// até que para e o programa
void maxTimesToRepeat(){
  int tenSeconds = 10 * 1000;
  float times = tenSeconds / updateTime;
  timesToRepeat = round(times);
}
