// Bibliotecas

#include <MPU6050_tockn.h>
#include <Wire.h>
// LEDS
#define pinLedRed 12
#define pinLedYellow 11
#define pinLedGreen 10

// Pre loads
float angleY, sensorFlex = 0;
const int updateTime = 300;
int timesToRepeat = 1;
int repeated = 0;
String sessionStatus;

unsigned long timeControl;

MPU6050 mpu6050(Wire);

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(200);
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
  angleY = mpu6050.getAngleY();

  if(Serial.available() > 0){
    sessionStatus = Serial.readString();
    Serial.println("Received " + sessionStatus + sessionStatus.compareTo("abort"));
    if(sessionStatus.compareTo("start") == 10){
      maxTimesToRepeat();
    }

    delay(500);
  }
  if(repeated == timesToRepeat){
    sessionStatus = "end";
    emmitString("end");
    repeated = 0;
  }
  if(sessionStatus.compareTo("start") == 10){    
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
  Serial.print(payload);
}
 
float calculateSensorFlex(){
  // aqui vai alguma função matemática
  return 3.1415;
}
// Retorna a quantidade de vezes que irá repetir
// até que para e o programa
void maxTimesToRepeat(){
  int tenSeconds = 10 * 1000;
  float times = tenSeconds / updateTime;
  timesToRepeat = round(times);
}
