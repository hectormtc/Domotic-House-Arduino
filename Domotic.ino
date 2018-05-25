int redLed = 13;
int lightLed = 12;
int smokeA0 = A5;
int sensorThres = 90;
int EP = 7;//Vibration
int greenLED = 11;
int lightSensor = A0;
int rainPin = A2;
int sensorPin = A1; // Flame
int sensorValue = 0; // Flame
int fan = A3;
int pirSensor = 10;
unsigned int light;

// DECLARACION DE VARIABLES PARA PINES
const int pinecho = 6;
const int pintrigger = A4;

// VARIABLES PARA CALCULOS
unsigned int tiempo, distancia;

#include <LiquidCrystal.h>

const int rs = 9, en = 8, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Science Fair");
  pinMode(pirSensor, INPUT);
  pinMode(fan, OUTPUT);
  pinMode(rainPin, INPUT);
  pinMode(EP, INPUT); //set EP input for measurment
  pinMode(redLed, OUTPUT);
  pinMode(smokeA0, INPUT);//Smoke
  pinMode(greenLED, OUTPUT);
  pinMode(lightLed, OUTPUT);
  pinMode(pinecho, INPUT);
  pinMode(pintrigger, OUTPUT);
}

void loop() {
/******************************************************************************/
  digitalWrite(pintrigger, LOW); //Ultrasonico
  delayMicroseconds(2);
  digitalWrite(pintrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pintrigger, LOW);

  tiempo = pulseIn(pinecho, HIGH);
  distancia = tiempo / 58;

  Serial.print(distancia);
  Serial.println(" cm");
  delay(200);
  if (distancia <= 15) {
    lcd.setCursor(0,1);
    lcd.print("Bienvenido!");
    delay(1000);
  }
  else if (distancia > 15) {
    lcd.setCursor(0,1);
    lcd.print("           ");
} //Ultrasonico
/******************************************************************************/
int sensorValue = digitalRead(pirSensor); //Movimiento
  if (sensorValue == 1) {
    digitalWrite(fan, HIGH); // The Relay Input works Inversly
  }
  else if(sensorValue != 1){
      digitalWrite(fan, LOW);
  } //Movimiento

/******************************************************************************/

sensorValue = analogRead(sensorPin); //Flame

Serial.println(sensorValue);
if(sensorValue < 100){
    Serial.println("Fire Detected");
    digitalWrite(redLed, HIGH);
    delay(100);
    digitalWrite(redLed, LOW);
} else if (sensorValue > 100){
    delay(sensorValue);
} //Flame

/******************************************************************************/
  int analogSensor = analogRead(smokeA0);//Smoke

  if (analogSensor > sensorThres) {
    digitalWrite(redLed, HIGH);
    delay(100);
    digitalWrite(redLed, LOW);
    delay(100);
  } else {
    digitalWrite(redLed, LOW);
}//Smoke
/******************************************************************************/

light = analogRead(lightSensor);//light

delay(100);

if(light > 850){
  digitalWrite(lightLed, HIGH);
}
else if (light <= 850) {
  digitalWrite(lightLed, LOW);
} //light
/******************************************************************************/

long measurement = TP_init();//Vibration
if (measurement > 50000){
    for(int i=1;i<=100;i++){
        digitalWrite(redLed, HIGH);
        delay(50);
        digitalWrite(redLed, LOW);
        delay(50);
    }
} else {
  digitalWrite(redLed, LOW);
}//Vibration

/******************************************************************************/

int sensorWater = analogRead(rainPin); //Water

if(sensorWater < 70){
  digitalWrite(redLed, HIGH);
  delay(100);
  digitalWrite(redLed, LOW);
  delay(100);
} else if(sensorWater >= 70) {
    digitalWrite(greenLED, HIGH);
    delay(100);
    digitalWrite(greenLED, LOW);
    delay(100);
}
  delay(100);
}//Water

/******************************************************************************/

long TP_init(){ //Funtion Vibration
    delay(10);
    long measurement=pulseIn (EP, HIGH);
    return measurement;
}
