#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "ina260.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

// Pins for the Power sensor
const uint8_t PIN_I2C_SDA = 8;
const uint8_t PIN_I2C_SCL = 9;
i2c_inst_t *i2c = i2c0;

int main() {
    stdio_init_all();

    Ina260 power = Ina260(i2c, PIN_I2C_SDA, PIN_I2C_SCL);
    power.setAveragingMode();
    while(true) {
        float voltage = power.readVoltage();;
        float current = power.readCurrent();
        float powerValue = power.readPower();
        printf("{\"voltage\": %f, \"current\": %f, \"power\": %f}\n", voltage/1, current/1, powerValue/1);
        sleep_ms(1000);
    }
}



#pragma clang diagnostic pop