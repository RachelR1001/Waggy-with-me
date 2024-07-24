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


int firstLED = 18;
int secondLED = 19;
int thirdLED = 21;
struct MessageValue receivedData;

void setup() {
  pinMode(firstLED, OUTPUT);
  pinMode(secondLED, OUTPUT);
  pinMode(thirdLED, OUTPUT);
  digitalWrite(firstLED, LOW);
  digitalWrite(secondLED, LOW);
  digitalWrite(thirdLED, LOW);

  Serial.begin(9600);
  Serial.setTimeout(10); // Set waiting time for serial data to 10 milliSeconds
}

void loop() {
  while (Serial.available() > 0) { // Take out strings until Serial is empty
    String receivedString = Serial.readStringUntil('\0'); // From 1.9.0 version, We can use '\0' as delimiter in Arduino Serial
    receivedData = getMessage(receivedString);
  }

  if (receivedData.message.equals("turnon")) {  
    digitalWrite(firstLED, HIGH);
    delay(500);
    digitalWrite(secondLED, HIGH);
    delay(500);
    digitalWrite(thirdLED, HIGH);
    delay(500);
  } else if(receivedData.message.equals("turnoff")) {
    
    digitalWrite(firstLED, LOW);
    digitalWrite(secondLED, LOW);
    digitalWrite(thirdLED, LOW);
  }
}