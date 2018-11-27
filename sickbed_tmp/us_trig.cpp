#include "Ultrasonic.h"
#include "us_trig.h"
#include "Arduino.h"
#include "Ultrasonic.h"

us_trig::us_trig(void)
{

}

void us_trig::us_trig_initial(int echopin_in1, int trigpin_in1,int echopin_in2, int trigpin_in2,int echopin_in3, int trigpin_in3,int echopin_in4, int trigpin_in4)
{
  us1.initial(trigpin_in1, echopin_in1);
  us2.initial(trigpin_in2, echopin_in2);
  us3.initial(trigpin_in3, echopin_in3);
  us4.initial(trigpin_in4, echopin_in4);

}

void us_trig::us_trig_setup(float trigger_value_in)
{
	trigger_value = trigger_value_in;	
}

void us_trig::us_trig_read(void)
{
  delay(800);
	sensor_time1 = us1.timing();
	dist_data1 = us1.convert(sensor_time1,Ultrasonic::CM);
  sensor_time1 = us1.timing();
  dist_data1 = us1.convert(sensor_time1,Ultrasonic::CM);
  sensor_time2 = us2.timing();
  dist_data2 = us2.convert(sensor_time2,Ultrasonic::CM);
  sensor_time3 = us3.timing();
  dist_data3 = us3.convert(sensor_time3,Ultrasonic::CM);
  sensor_time4 = us4.timing();
  dist_data4 = us4.convert(sensor_time4,Ultrasonic::CM);

  data_array[0] = dist_data1;
  data_array[1] = dist_data2;
  data_array[2] = dist_data3;
  data_array[3] = dist_data4;
}

//void us_trig::save_array(float data1, float data2, float data3, float data4)
//{
//	data_array[0] = data1;
//  data_array[1] = data2;
//  data_array[2] = data3;
//  data_array[3] = data4;
//
//  //Serial.println("data saved.");
//}
void us_trig::print_array(void)
{
  Serial.println("US array: ");
  for(int i=0;i<4;i++)
      {
        Serial.print(i+1);
        Serial.print(" sensor's distance: ");
        Serial.print(data_array[i]);
        Serial.println(" ");
      }
  }

bool us_trig::us_trig_solo(float data)
{
  bool trigger;
  trigger = (data<=trigger_value);

  return trigger;
}

char us_trig::us_trig_total(float data_array[])
{
	byte trig_F1, trig_F2, trig_F3, trig_F4;

	trig_F1 = us_trig_solo(data_array[0]);
  trig_F2 = us_trig_solo(data_array[1]);
  trig_F3 = us_trig_solo(data_array[2]);
  trig_F4 = us_trig_solo(data_array[3]);

  	if(trig_F1 + trig_F2 == 2 || trig_F3 + trig_F4 == 2)
  	{
  		return 'F';
  	}
  	else 
  	{
  		return 'D';
  	}
}

void us_trig::print_trig(void)
{
  byte trig_F1, trig_F2, trig_F3, trig_F4;

  trig_F1 = us_trig_solo(data_array[0]);
  trig_F2 = us_trig_solo(data_array[1]);
  trig_F3 = us_trig_solo(data_array[2]);
  trig_F4 = us_trig_solo(data_array[3]);

  
  Serial.println("US_trig data: ");
  Serial.print("F1: ");
  Serial.println(trig_F1);
  Serial.print("F2: ");
  Serial.println(trig_F2);
  Serial.print("F3: ");
  Serial.println(trig_F3);
  Serial.print("F4: ");
  Serial.println(trig_F4);
  }

