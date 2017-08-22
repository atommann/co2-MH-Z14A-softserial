// modified from https://github.com/mars1980/C02_UART
// This program is used to test the MH-Z14A CO2 sensor

#include <SoftwareSerial.h>

// using softserial to send/recieve data over analog pins 0 & 1
SoftwareSerial mySerial(A0, A1); // RX, TX respectively
// CO2 sensor pin 24 RXD yellow
// CO2 sensor pin 25 TXD white

byte cmd[9] = {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79}; 
byte response[9]; 
int calibrationTime = 10; //warm up time for C02 sensor (3min = 180sec)


void setup() 
{
  Serial.begin(9600);
  mySerial.begin(9600);

  // give the sensor some time to calibrate/pre-heat?
  // 3 min. is a long time, here we do 10 seconds :)
  Serial.print("calibrating sensor (3min) ");
  for(int i = 0; i < calibrationTime; i++){
    Serial.print(".");
    delay(1000);
  }
  Serial.println(" done");
  Serial.println("SENSOR ACTIVE");
  delay(50);
}
////////////////////////////////////////////////////////////END SETUP


void loop() 
{
  // PING CO2, READ RESPONSE, GET READINGS AND CONVERT TO PPM
  mySerial.write(cmd, 9);
  mySerial.readBytes(response, 9);
  uint16_t responseHigh = response[2];
  uint16_t responseLow = response[3];
  uint16_t ppm = (256*responseHigh) + responseLow;

  // print CO2 out onto the serial
  Serial.println(ppm);
  
  delay(1000);
}


