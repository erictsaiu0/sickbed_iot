#include "Arduino.h"
#include "inttypes.h"
#include "stdio.h"

class ESPMaster {
  private:
  uint8_t _ss_pin;

  public:
  ESPMaster(uint8_t pin);
  void begin(void);
  uint32_t readStatus(void);
  void writeStatus(uint32_t status);
  void readData(uint8_t * data);
  void writeData(uint8_t * data, size_t len);
  String readData();
  void writeData(const char * data);
};
  

