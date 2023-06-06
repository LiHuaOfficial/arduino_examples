#ifndef SLOW_SOFT_I2C_MASTER_H
#define SLOW_SOFT_I2C_MASTER_H

#include <Arduino.h>
#include <inttypes.h>

#define I2C_READ 1
#define I2C_WRITE 0
#define DELAY 4 // usec delay
#define BUFFER_LENGTH 32
#define I2C_MAXWAIT 5000

/*这是一个用于I2C通信的类*/
class SlowSoftI2CMaster {
 public:
 SlowSoftI2CMaster();
  SlowSoftI2CMaster(unsigned char sda,unsigned char scl);
  SlowSoftI2CMaster(unsigned char sda,unsigned char scl, bool internal_pullup);
  bool i2c_init(void);
  bool i2c_start(unsigned char addr);
  bool i2c_start_wait(unsigned char addr);
  bool i2c_rep_start(unsigned char addr);
  void i2c_stop(void);
  bool i2c_write(unsigned char value);
  unsigned char i2c_read(bool last);
  bool error;
  
 private:
  void setHigh(unsigned char pin);
  void setLow(unsigned char pin);
  unsigned char _sda;
  unsigned char _scl;
  bool _pullup;
};

#endif
