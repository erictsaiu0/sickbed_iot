
#include "sb_motor.h"
#include "humd_temp_sensor.h"

//define mtr pin
#define mtr1_step  2
#define mtr2_step 3
#define mtr3_step 4
#define mtr4_step 5
#define mtr5_step 6
#define mtr6_step 7
#define mtr1_dir  22
#define mtr2_dir  23
#define mtr3_dir  24
#define mtr4_dir  25
#define mtr5_dir  26
#define mtr6_dir  27
#define mtr1_btn  13
#define mtr2_btn  12
#define mtr3_btn  11
#define mtr4_btn  10
#define mtr5_btn  9
#define mtr6_btn  8

//define press sensor pin
#define press1    A0
#define press2    A1
#define press3    A2
#define press4    A3
#define press5    A4
#define press6    A5
//define ultrasonic sensor pin
#define us_trig1  32
#define us_echo1  33
#define us_trig2  34
#define us_echo2  35
#define us_trig3  36
#define us_echo3  37
#define us_trig4  38
#define us_echo4  39
//define on-bed controller pin
#define ctrl_up   42
#define ctrl_re   43
#define ctrl_down 44
//define vibrator pin   
#define vib_data  28

//define motor parameters
#define mtr_worktime  200000    //每次收到上下指令轉的時間
#define mtr_step_time 1500    //步階馬達每步的時間
//declaration of motor functions
sb_motor mtr1,mtr2,mtr3,mtr4,mtr5,mtr6,mtr_t;
humd_temp_sensor hnt;

int mtr_work_state = 0;

void setup(){
  mtr1.motor_initial(mtr1_step,mtr1_dir,mtr1_btn);
  mtr2.motor_initial(mtr2_step,mtr2_dir,mtr2_btn);
  mtr3.motor_initial(mtr3_step,mtr3_dir,mtr3_btn);
  mtr4.motor_initial(mtr4_step,mtr4_dir,mtr4_btn);
  mtr5.motor_initial(mtr5_step,mtr5_dir,mtr5_btn);
  mtr6.motor_initial(mtr6_step,mtr6_dir,mtr6_btn);

  mtr1.motor_setup(mtr_worktime,mtr_step_time);
  mtr2.motor_setup(mtr_worktime,mtr_step_time);
  mtr3.motor_setup(mtr_worktime,mtr_step_time);
  mtr4.motor_setup(mtr_worktime,mtr_step_time);
  mtr5.motor_setup(mtr_worktime,mtr_step_time);
  mtr6.motor_setup(mtr_worktime,mtr_step_time);
//Serial.begin(9600);
  //hnt.tca_initial();
}

void loop(){
  switch(mtr_work_state)
  {
    case 0:
    {
      mtr1.motor_reset_single(mtr1.stepPin,mtr1.dirPin,mtr1.btn);
      mtr2.motor_reset_single(mtr2.stepPin,mtr2.dirPin,mtr2.btn);
      mtr3.motor_reset_single(mtr3.stepPin,mtr3.dirPin,mtr3.btn);
      mtr4.motor_reset_single(mtr4.stepPin,mtr4.dirPin,mtr4.btn);
      mtr5.motor_reset_single(mtr5.stepPin,mtr5.dirPin,mtr5.btn);
      mtr6.motor_reset_single(mtr6.stepPin,mtr6.dirPin,mtr6.btn);
      mtr_work_state = (mtr1.reset_done && mtr2.reset_done && mtr3.reset_done && mtr4.reset_done && mtr5.reset_done && mtr6.reset_done)?1:0;
      break;
    }
    case 1:
    {
      mtr1.motor_action(mtr1.stepPin,mtr1.dirPin,mtr1.action_signal);
      mtr2.motor_action(mtr2.stepPin,mtr2.dirPin,mtr2.action_signal);
      mtr3.motor_action(mtr3.stepPin,mtr3.dirPin,mtr3.action_signal);
      mtr4.motor_action(mtr4.stepPin,mtr4.dirPin,mtr4.action_signal);
      mtr5.motor_action(mtr5.stepPin,mtr5.dirPin,mtr5.action_signal);
      mtr6.motor_action(mtr6.stepPin,mtr6.dirPin,mtr6.action_signal);
      mtr_work_state = mtr_work_state;
      break;
    }
  }
}
