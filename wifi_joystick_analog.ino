#include <ESP8266WiFi.h> 
#include <BlynkSimpleEsp8266.h>


char auth[] = "56c04f149b4946718b44b41a56a635e1";


char ssid[] = "RT-GPON-41F6";
char pass[] = "tbt4QxRE";

// L298

// Мотор вперед назад
#define MOTORA_1 D7 //IN1
#define MOTORA_2 D6 //IN2
#define ENA D8      //ENA
// Мотор право лево
#define ENB D3      //ENB
#define MOTORB_1 D4 //IN3
#define MOTORB_2 D5 //IN4
#define LED1 D0 //LED1 IN
#define LED2 D1 //LED2 IN

int motor_FB = 0;
int motor_LR = 0;


void setup()
{

  pinMode(ENA, OUTPUT);
  pinMode(MOTORA_1, OUTPUT);
  pinMode(MOTORA_2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(MOTORB_1, OUTPUT);
  pinMode(MOTORB_2, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  
  digitalWrite(ENA,LOW);
  digitalWrite(ENB,LOW);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  
  Serial.begin(9600);
    
 
  Blynk.begin(auth, ssid, pass);
}


BLYNK_WRITE(V0) {
  int nJoyY = map(param[0].asInt(), 0, 1024, 0, 252);
  int nJoyX = map(param[1].asInt(), 0, 1024, 0, 252);
  Serial.print("X = ");
  Serial.print(nJoyX);
  Serial.print("; Y = ");
  Serial.println(nJoyY);

  

  int motor_FB; 
  int motor_LR; 

  int MotorSpeed = map(nJoyX, 0, 255, 0, 800); //скорость вперед

  Serial.print("MotorSpeed = ");
  Serial.println(MotorSpeed);


  motor_FB = nJoyX;
  motor_LR = nJoyY;



  if (motor_FB > 140) {
    digitalWrite(MOTORA_1,HIGH);
    digitalWrite(MOTORA_2,LOW);
    analogWrite(ENA,MotorSpeed);
	digitalWrite(LED1, HIGH);
	digitalWrite(LED2, LOW);
    Serial.println("Двигаюсь вперед");
  }
  else if (motor_FB < 100) {
    digitalWrite(MOTORA_1,LOW);
    digitalWrite(MOTORA_2, HIGH);
    analogWrite(ENA,600); //скорость назад
	digitalWrite(LED1, LOW);
	digitalWrite(LED2, HIGH);
    Serial.println("Двигаюсь назад");
  }
  else  {
    digitalWrite(MOTORA_1, LOW);
    digitalWrite(MOTORA_2, LOW);
	digitalWrite(LED1, LOW);
	digitalWrite(LED2, LOW);
    Serial.println("Стоп");
  }
  if (motor_LR > 140) {
    digitalWrite(MOTORB_1, LOW);
    digitalWrite(MOTORB_2, HIGH);
    digitalWrite(ENB,HIGH);
    Serial.println("Двигаюсь вправо");
  }
  else if (motor_LR < 90) {
    digitalWrite(MOTORB_1, HIGH);
    digitalWrite(MOTORB_2, LOW);
    digitalWrite(ENB,HIGH);
    Serial.println("Двигаюсь влево");
  }
  else  {
    digitalWrite(MOTORB_1, LOW);
    digitalWrite(MOTORB_2, LOW);
    Serial.println("Прямо");
  }

}


void loop()
{
  Blynk.run();
}
