
#include <Adafruit_NeoPixel.h>
#include "AccelStepper.h"
#include <FastLED.h>
#include <string.h>

struct MessageValue {
  String message;
  String value;
};

struct MessageValue getMessage(String inputtedStr) {
  struct MessageValue result;

  char charArr[50];
  inputtedStr.toCharArray(charArr, 50);
  char* ptr = strtok(charArr, "||");
  result.message = String(ptr);
  ptr = strtok(NULL, "||");

  if (ptr == NULL) {
    result.value = String("");
    return result;
  }

  result.value = String(ptr);

  return result;
}
// 电机步进方式定义
#define FULLSTEP 4    //全步进参数
#define HALFSTEP 8    //半步进参数
 
// 定义步进电机引脚 
 
#define motor1Pin1  5     // 一号28BYJ48连接的ULN2003电机驱动板引脚 in1
#define motor1Pin2  18     // 一号28BYJ48连接的ULN2003电机驱动板引脚 in2
#define motor1Pin3  19    // 一号28BYJ48连接的ULN2003电机驱动板引脚 in3
#define motor1Pin4  21    // 一号28BYJ48连接的ULN2003电机驱动板引脚 in4
                        
                        
#define motor2Pin1  22     // 二号28BYJ48连接的ULN2003电机驱动板引脚 in1
#define motor2Pin2  23     // 二号28BYJ48连接的ULN2003电机驱动板引脚 in2
#define motor2Pin3  25     // 二号28BYJ48连接的ULN2003电机驱动板引脚 in3
#define motor2Pin4  26     // 二号28BYJ48连接的ULN2003电机驱动板引脚 in4
 
// 定义两个步进电机对象
// 定义中ULN2003驱动板引脚顺序为 in1-in3-in2-in4
// 1号电机设置为全步进运行，2号电机设置为全步进运行
AccelStepper stepper1(FULLSTEP, motor1Pin1, motor1Pin3, motor1Pin2, motor1Pin4);
AccelStepper stepper2(FULLSTEP, motor2Pin1, motor2Pin3, motor2Pin2, motor2Pin4);

#define LED_PIN     2
#define NUM_LEDS    30
CRGB leds[NUM_LEDS];
uint8_t max_bright = 255; 
struct MessageValue receivedData;



void setup() {
  Serial.begin(9600);
  stepper1.setMaxSpeed(800.0);    // 1号电机最大速度500 
  stepper1.setAcceleration(50.0);  // 1号电机加速度50.0
 
  stepper2.setMaxSpeed(800.0);    // 2号电机最大速度500 
  stepper2.setAcceleration(50.0);  // 2号电机加速度50.0
  FastLED.setBrightness(max_bright);
  //灯带
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
   while (Serial.available() > 0) { // Take out strings until Serial is empty
    String receivedString = Serial.readStringUntil('\0'); // From 1.9.0 version, We can use '\0' as delimiter in Arduino Serial
    receivedData = getMessage(receivedString);
  }

//  if (receivedData.message.equals("turnon") && stepper1.currentPosition() == 0 && stepper2.currentPosition() == 0) {
      if (receivedData.message.equals("turnon")) {

     stepper1.moveTo(1000);              
    // 2号电机转动一周
    stepper2.moveTo(1440);  
    FastLED.setBrightness(255);
    leds[0] = CRGB::Red;          // 设置光带中第一个灯珠颜色为红色，leds[0]为第一个灯珠，leds[1]为第二个灯珠
    FastLED.show();                // 更新LED色彩
    delay(500); 
    leds[0] = CRGB::White;          // 设置光带中第一个灯珠颜色为红色，leds[0]为第一个灯珠，leds[1]为第二个灯珠
    FastLED.show();  
    delay(500); 
    // stepper1.run();
    // stepper2.run();   
  // }  else if(receivedData.message.equals("turnoff") && stepper1.currentPosition() == 1000 && stepper2.currentPosition() == 1440) {
  }  else if(receivedData.message.equals("turnoff")) {
   // 1号电机转动半周
   // 1号电机转动半周
    stepper1.moveTo(0);            
    // 2号电机转动一周
    stepper2.moveTo(0);
    FastLED.setBrightness(0);
    FastLED.show(); 
    // stepper1.run();
    // stepper2.run();
  }
  //  for (int i = 0; i <= 29; i++) {
  //   leds[i] = CRGB (0, 0, 255);
  //   FastLED.show();
  //   delay(10);
  // }
  // delay(3000);
  // for (int i = 0; i <= 29; i++) {
  // leds[i] = CRGB ( 0, 0, 0);
  // }
  // FastLED.show();
  stepper1.run();   // 1号电机运行
  stepper2.run();   // 2号电机运行
}
