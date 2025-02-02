#include "motoron.h"

uint8_t Mototron::calculateCrc(const uint8_t *buffer, uint8_t length) {
    uint8_t crc = 0;
    for (uint8_t i = 0; i < length; i++)
        crc = crcTable[crc ^ buffer[i]];
    return crc;
}


void Mototron::setup() {
    uart.begin(MOTORON_BAUDRATE);

    uint8_t responseBuffer[8];
    executeCommand(Mototron::Command::REINITIALIZE, responseBuffer);
    executeCommand(Mototron::Command::CLEAR_RESET_FLAGS, responseBuffer);
}

void Mototron::executeCommand(Mototron::Command command, uint8_t *responseBuffer) {
    // TODO add proper error handling
    uint8_t commandBuffer[8];

    memset(commandBuffer, 0, 8);
    memset(responseBuffer, 0, 8);

    uint16_t flags = 0x200;

    switch (command) {
        case Mototron::Command::REINITIALIZE:
            commandBuffer[0] = 0x96;
            commandBuffer[1] = calculateCrc(commandBuffer, 1);
            uart.write(commandBuffer, 2);
            return;

        case Mototron::Command::CLEAR_RESET_FLAGS:
            commandBuffer[0] = 0xA9;
            commandBuffer[1] = (uint8_t) (flags & 0x7F);
            commandBuffer[2] = (uint8_t) (flags >> 7 & 0x7F);
            commandBuffer[3] = calculateCrc(commandBuffer, 3);
            uart.write(commandBuffer, 4);
            return;

        case Mototron::Command::GET_FIRMWARE_VERSION:
            commandBuffer[0] = 0x87;
            commandBuffer[1] = calculateCrc(commandBuffer, 1);
            uart.write(commandBuffer, 2);
            uart.flush();
            uart.readBytes(responseBuffer, 4);
            return;
    }
}


void Mototron::getFirmwareVersion(uint16_t *productId, uint16_t *firmwareVersion) {
    uint8_t responseBuffer[8];

    executeCommand(Mototron::Command::GET_FIRMWARE_VERSION, responseBuffer);

    *productId = responseBuffer[0] | (responseBuffer[1] << 8);
    *firmwareVersion = responseBuffer[2] | (responseBuffer[3] << 8);
}
