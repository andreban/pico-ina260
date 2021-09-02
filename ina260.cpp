#include "ina260.h"
#include <stdio.h>
#include <stdlib.h>

Ina260::Ina260(i2c_inst_t *i2c, uint8_t pin_sda, uint8_t pin_sdl, uint8_t address):
    i2c(i2c), address(address) {
  gpio_set_function(pin_sda, GPIO_FUNC_I2C);
  gpio_set_function(pin_sdl, GPIO_FUNC_I2C);
  i2c_init(i2c, 100000);
}

void Ina260::setAveragingMode() {
    uint8_t configurationRegister = REGISTER_CONFIGURATION;

    uint16_t config = readConfig();

    uint16_t sampleCount = 0b111 << 9;
    config = config | sampleCount;

    uint8_t msb = (config >> 8) & 0xFF;
    uint8_t lsb = config & 0xFF;

    uint8_t value[] = {configurationRegister, msb, lsb};
    i2c_write_blocking(i2c, address, value, 3, false);
}

float Ina260::readCurrent() {
  uint8_t currentRegister = REGISTER_CURRENT;
  // Set register we want to read.
  i2c_write_blocking(i2c, address, &currentRegister, 1, false);

  // Read value.
  uint8_t value[] = {0, 0};
  i2c_read_blocking(i2c, address, value, 2, false);

  int16_t current = (value[0] << 8) | value[1];
  return current * 1.25;
}

float Ina260::readVoltage() {
  uint8_t voltageRegister = REGISTER_BUS_VOLTAGE;
  // Set register we want to read.
  i2c_write_blocking(i2c, address, &voltageRegister, 1, false);

  // Read value.
  uint8_t value[] = {0, 0};
  i2c_read_blocking(i2c, address, value, 2, false);

  int16_t voltage = (value[0] << 8) | value[1];
  return voltage * 1.25;
}

float Ina260::readPower() {
  uint8_t powerRegister = REGISTER_POWER;
  // Set register we want to read.
  i2c_write_blocking(i2c, address, &powerRegister, 1, false);
    // Read value.
  uint8_t value[] = {0, 0};
  i2c_read_blocking(i2c, address, value, 2, false);

  int16_t power = (value[0] << 8) | value[1];
  return power * 10.;
}

uint16_t Ina260::readConfig() {
    uint8_t configurationRegister = REGISTER_CONFIGURATION;
    i2c_write_blocking(i2c, address, &configurationRegister, 1, false);
    uint8_t value[] = {0, 0};
    i2c_read_blocking(i2c, address, value, 2, false);
    return (value[0] << 8) | value[1];
}
