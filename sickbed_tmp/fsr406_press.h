#include "Arduino.h"
#include "inttypes.h"
#include "stdio.h"

class fsr406_press{
  private:

  public:
    uint8_t datapin;
    float press_data = 0;
    float data_array[];
    float trigger_value;

    fsr406_press(void);
    void fsr406_initial(uint8_t datapin_in, float trigger_value_in);
    void fsr406_read(void);
    void save_array(float data1,float data2,float data3,float data4,float data5,float data6);
    void print_array(void);
    bool press_trig_solo(float data);
    char press_trig_total(float data_array[]);
    void print_trig_data(void);
    void wait(int interval);
    void analog_mux(int pin);
  };

