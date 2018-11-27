#include "Arduino.h"
#include "inttypes.h"
#include "stdio.h"
#include "Ultrasonic.h"

class us_trig{
private:

public:
	int echopin,trigpin;
	float dist_data1,dist_data2,dist_data3,dist_data4;
	float data_array[];
	float trigger_value;
	Ultrasonic us1,us2,us3,us4;
	long sensor_time1,sensor_time2,sensor_time3,sensor_time4;

	us_trig(void);
	void us_trig_initial(int echopin_in1, int trigpin_in1,int echopin_in2, int trigpin_in2,int echopin_in3, int trigpin_in3,int echopin_in4, int trigpin_in4);
	void us_trig_setup(float trigger_value_in);
	void us_trig_read(void);
//	void save_array(float data1, float data2, float data3, float data4);
  void print_array(void);
	bool us_trig_solo(float data);
	char us_trig_total(float data_array[]);
  void print_trig(void);
};

