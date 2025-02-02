#include <Motoron.h>
#include <Arduino.h>
#include <SoftwareSerial.h>


// https://github.com/pololu/motoron-arduino
SoftwareSerial mcSerial(10, 11);
MotoronSerial mc;

uint16_t productId = 0;
uint16_t firmwareVersion = 0;

void setup() {
    Serial.begin(9600);
    mcSerial.begin(115200);
    mcSerial.setTimeout(20);
    mc.setPort(&mcSerial);

    mc.reinitialize();
    mc.disableCrc();

    mc.clearResetFlag();

    mc.getFirmwareVersion(&productId, &firmwareVersion);

    Serial.print("Product ID: 0x");
    Serial.println(productId, HEX);

    Serial.print("Firmware Version: 0x");
    Serial.println(firmwareVersion, HEX);
}

void loop(){}