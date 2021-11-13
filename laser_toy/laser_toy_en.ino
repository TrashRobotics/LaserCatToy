#include <Servo.h>

#define FIRST_LINK_SERVO_PIN  9   // пин сервопривода первого звена
#define SECOND_LINK_SERVO_PIN 10  // пин сервопривода второго звена
#define LASER_PIN             11  // пин лазера

#define BASE_FIRST_LINK_SERVO_POS   90  // базовое положение сервоприводов (в градусах)
#define BASE_SECOND_LINK_SERVO_POS  90

#define MIN_FIRST_LINK_SERVO_POS    45  // минимальный угол, который может занять первый сервопривод
#define MAX_FIRST_LINK_SERVO_POS    135 // максимальный угол, который может занять первый сервопривод

#define MIN_SECOND_LINK_SERVO_POS    80  // минимальный угол, который может занять первый сервопривод
#define MAX_SECOND_LINK_SERVO_POS    150  // максимальный угол, который может занять первый сервопривод

#define LASER_BRIGHTNESS  200 // яркость свечения лазера
#define SERVO_DELAY       6

Servo firstLinkServo;   // сервопривод первого звена
Servo secondLinkServo;  // сервопривод второго звена


void setup() {
  pinMode(LASER_PIN, OUTPUT);
  analogWrite(LASER_PIN, LOW);
  
  firstLinkServo.attach(FIRST_LINK_SERVO_PIN);      // привязываем приводы к портам
  secondLinkServo.attach(SECOND_LINK_SERVO_PIN);    //
  
  firstLinkServo.write(BASE_FIRST_LINK_SERVO_POS);  // ставим в базовое положение
  delay(200);
  secondLinkServo.write(BASE_SECOND_LINK_SERVO_POS); // ставим в базовое положение
  delay(200);
  
  analogWrite(LASER_PIN, LASER_BRIGHTNESS);  // запускаем лазер
}


void loop() {
  uint8_t fsp = random(MIN_FIRST_LINK_SERVO_POS, MAX_FIRST_LINK_SERVO_POS);     // выставляем первую серву в рандомную позицию
  uint8_t ssp = random(MIN_SECOND_LINK_SERVO_POS, MAX_SECOND_LINK_SERVO_POS);   // выставляем вторую серву в рандомную позицию 
  slowSetServosPos(fsp, ssp, 100, SERVO_DELAY);   // медленное изменение позиций серв (блокирующее)
  //delay(500);
}


void slowSetServosPos(uint8_t flsPos, uint8_t slsPos, uint8_t steps, uint8_t dt)
{
  static uint8_t flsLastPos = BASE_FIRST_LINK_SERVO_POS;    // предыдущиие позиции сервоприводов (начальное значение по центру)
  static uint8_t slsLastPos = BASE_SECOND_LINK_SERVO_POS;   //
  
  for(uint8_t i = 0; i < steps; i++) {      // каждый шаг прибавляем немного к текущим позициям
    firstLinkServo.write(flsLastPos + i*(flsPos-flsLastPos)/steps); 
    secondLinkServo.write(slsLastPos + i*(slsPos-slsLastPos)/steps);
    delay(dt);  
  }
  flsLastPos = flsPos;  // обновляем прошлые позиции
  slsLastPos = slsPos;
}
