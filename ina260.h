/*
 * Datasheet
 *  - https://www.ti.com/lit/ds/symlink/ina260.pdf?ts=1628061860726
 */
#ifndef INA260_H
#define INA260_H

#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define REGISTER_CONFIGURATION 0x00
#define REGISTER_CURRENT 0x01
#define REGISTER_BUS_VOLTAGE 0x02
#define REGISTER_POWER 0x03
#define REGISTER_MASK_ENABLE 0x06
#define REGISTER_ALERT_LIMIT 0x07
#define REGISTER_MANUFACTURER_ID 0xFE
#define REGISTER_DIE_ID 0xFF

#define DEFAULT_i2C_ADDRESS 0x40

class Ina260 {
private:
  uint8_t address;
  i2c_inst_t *i2c;
public:
  Ina260(i2c_inst_t *i2c, uint8_t pin_sda, uint8_t pin_sdl, uint8_t address = DEFAULT_i2C_ADDRESS);
  void setAveragingMode();
  uint16_t readConfig();
  float readCurrent();
  float readVoltage();
  float readPower();
};

#endif // INA260_H