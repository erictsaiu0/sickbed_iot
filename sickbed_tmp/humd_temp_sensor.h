#include "Arduino.h"

#include "inttypes.h"
#include "stdio.h"
#include "SparkFunHTU21D.h"
#include <Wire.h>

//extern "C" { 
//#include "utility/twi.h"  }

#define TCAADDR1 0x71
#define TCAADDR2 0x70

class humd_temp_sensor{
	private:

	public:
		float hmd1,hmd2,hmd3,hmd4,hmd5,hmd6,hmd7,hmd8,hmd9,hmd10,hmd11,hmd12;
		float tmp1,tmp2,tmp3,tmp4,tmp5,tmp6,tmp7,tmp8,tmp9,tmp10,tmp11,tmp12;

 	  HTU21D myHnm1,myHnm2,myHnm3,myHnm4,myHnm5,myHnm6,myHnm7,myHnm8,myHnm9,myHnm10,myHnm11,myHnm12;

		//float tmp_data_array[3][6];
  	float data_array[6];
		float tmp_data_array[6];
   	float hmd_data_array[6];
		int data_flag=0;

		humd_temp_sensor(void);
		char data_avail(float data);
		void data_filter_6(float data1, float data2 ,float data3, float data4, float data5, float data6);
		//void scan(void);
		void tcaselect(int i);
		void tca_initial(void);
  	void data_read(void);

    byte hnt_trig_solo(float humd,float temp);
    char hnt_trig_total(float hmd_data_array[],float tmp_data_array[]);
};

