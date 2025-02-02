#include "Arduino.h"
#include "motoron.h"


Mototron mototron;

void setup() {
    Serial.begin(9600);

    mototron.setup();

    uint16_t productId = 0;
    uint16_t firmwareVersion = 0;
    mototron.getFirmwareVersion(&productId, &firmwareVersion);

    Serial.print("Product ID: 0x");
    Serial.println(productId, HEX);
    Serial.print("Firmware Version: 0x");
    Serial.println(firmwareVersion, HEX);
}

void loop() {}
