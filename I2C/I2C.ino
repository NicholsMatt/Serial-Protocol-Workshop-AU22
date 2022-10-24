#include <Wire.h>

String myData = "ID:2 Hi Back!";

String allData = "";

void setup() {
  Serial.begin(115200);
  Wire.begin(10);
  Wire.onReceive(recieveHandler);
}

void recieveHandler(int bytes) {
  String message = "";
  while(bytes > 0) {
    message += (char)(Wire.read());
    bytes--;
  }
  const int index = allData.indexOf(message.substring(0,4));
  if(index >= 0) {
    allData.replace(allData.substring(index, allData.indexOf(',') + 2), message);
  } else {
    allData += message;
  }
}

void loop() {
  Wire.beginTransmission(10);
  Wire.print(myData + ", ");
  Wire.endTransmission();
  delay(1);

  Serial.println(allData + myData);
}
