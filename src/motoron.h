#include "Arduino.h"
#include <SoftwareSerial.h>

#define MOTORON_BAUDRATE 115200


class Mototron {
public:
    Mototron() : uart(10, 11) {
    }

    void setup();

    void getFirmwareVersion(uint16_t *productId, uint16_t *firmwareVersion);

protected:
    enum Command {
        REINITIALIZE,
        CLEAR_RESET_FLAGS,
        GET_FIRMWARE_VERSION
    };

    uint8_t calculateCrc(const uint8_t *buffer, uint8_t length);

    void executeCommand(Mototron::Command command, uint8_t *responseBuffer);

    const uint8_t crcTable[256] = {
            0x00, 0x41, 0x13, 0x52, 0x26, 0x67, 0x35, 0x74,
            0x4c, 0x0d, 0x5f, 0x1e, 0x6a, 0x2b, 0x79, 0x38,
            0x09, 0x48, 0x1a, 0x5b, 0x2f, 0x6e, 0x3c, 0x7d,
            0x45, 0x04, 0x56, 0x17, 0x63, 0x22, 0x70, 0x31,
            0x12, 0x53, 0x01, 0x40, 0x34, 0x75, 0x27, 0x66,
            0x5e, 0x1f, 0x4d, 0x0c, 0x78, 0x39, 0x6b, 0x2a,
            0x1b, 0x5a, 0x08, 0x49, 0x3d, 0x7c, 0x2e, 0x6f,
            0x57, 0x16, 0x44, 0x05, 0x71, 0x30, 0x62, 0x23,
            0x24, 0x65, 0x37, 0x76, 0x02, 0x43, 0x11, 0x50,
            0x68, 0x29, 0x7b, 0x3a, 0x4e, 0x0f, 0x5d, 0x1c,
            0x2d, 0x6c, 0x3e, 0x7f, 0x0b, 0x4a, 0x18, 0x59,
            0x61, 0x20, 0x72, 0x33, 0x47, 0x06, 0x54, 0x15,
            0x36, 0x77, 0x25, 0x64, 0x10, 0x51, 0x03, 0x42,
            0x7a, 0x3b, 0x69, 0x28, 0x5c, 0x1d, 0x4f, 0x0e,
            0x3f, 0x7e, 0x2c, 0x6d, 0x19, 0x58, 0x0a, 0x4b,
            0x73, 0x32, 0x60, 0x21, 0x55, 0x14, 0x46, 0x07,
            0x48, 0x09, 0x5b, 0x1a, 0x6e, 0x2f, 0x7d, 0x3c,
            0x04, 0x45, 0x17, 0x56, 0x22, 0x63, 0x31, 0x70,
            0x41, 0x00, 0x52, 0x13, 0x67, 0x26, 0x74, 0x35,
            0x0d, 0x4c, 0x1e, 0x5f, 0x2b, 0x6a, 0x38, 0x79,
            0x5a, 0x1b, 0x49, 0x08, 0x7c, 0x3d, 0x6f, 0x2e,
            0x16, 0x57, 0x05, 0x44, 0x30, 0x71, 0x23, 0x62,
            0x53, 0x12, 0x40, 0x01, 0x75, 0x34, 0x66, 0x27,
            0x1f, 0x5e, 0x0c, 0x4d, 0x39, 0x78, 0x2a, 0x6b,
            0x6c, 0x2d, 0x7f, 0x3e, 0x4a, 0x0b, 0x59, 0x18,
            0x20, 0x61, 0x33, 0x72, 0x06, 0x47, 0x15, 0x54,
            0x65, 0x24, 0x76, 0x37, 0x43, 0x02, 0x50, 0x11,
            0x29, 0x68, 0x3a, 0x7b, 0x0f, 0x4e, 0x1c, 0x5d,
            0x7e, 0x3f, 0x6d, 0x2c, 0x58, 0x19, 0x4b, 0x0a,
            0x32, 0x73, 0x21, 0x60, 0x14, 0x55, 0x07, 0x46,
            0x77, 0x36, 0x64, 0x25, 0x51, 0x10, 0x42, 0x03,
            0x3b, 0x7a, 0x28, 0x69, 0x1d, 0x5c, 0x0e, 0x4f,
    };

    SoftwareSerial uart;
};
