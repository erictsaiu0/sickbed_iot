//#include "inttypes.h"
//#include "stdio.h"
//
//class sb_motor{
//  private:
//
//  public:
//    int stepPin; 
//    int dirPin;
//    //int sleepPin;
//    //int resetPin;
//    int btn;
//    int up_signal;
//    const int testled = 13;
//    uint32_t mstime ;
//    uint32_t worktime;
//    uint32_t time_now;
//    uint32_t sp;
//    bool flag;
//    char motor_running;
//    bool reset_ready;
//    bool work_done;
//
//    int motor_state = 0 ; //0: 未校正, 1: 次校正, 2: 已校正
//    bool reset_done = 0;
//    uint32_t i = 0 ; 
//    uint32_t j = 0 ;
//
//    int work_state = 0;
//
//
//    unsigned long oneshot_oldtime = 0;
//    unsigned long oneshot_newtime;
//    unsigned long oneshot_interval = 300;
//    bool up_trig,down_trig,return_trig;
//    char action_signal;
//    char action_array[6];
//    char position_state;
//
//    sb_motor(void);
//    void motor_initial(int stepPin_in, int dirPin_in, int btn_in);
//    void motor_setup(uint32_t worktime_in, uint32_t sp_in);
//    void motor_reset_single(int stepPin, int dirPin,int btn);
//    void motor_up(int stepPin, int dirPin, char up_signal);
//    void motor_action(int stepPin, int dirPin, char action_signal);
//    void motor_down(int stepPin, int dirPin, char down_signal);
//    bool oneshot(int btn);
//    void motor_action_decode(char instr);
//  };
//#include "inttypes.h"
//#include "stdio.h"
//
//class sb_motor{
//  private:
//
//  public:
//    int stepPin; 
//    int dirPin;
//    //int sleepPin;
//    //int resetPin;
//    int btn;
//    int up_signal;
//    const int testled = 13;
//    uint32_t mstime = 0;
//    uint32_t worktime;
//    uint32_t time_now;
//    int sp;
//    bool flag;
//    char motor_running;
//    bool reset_ready;
//
//    int motor_state = 0 ; //0: 未校正, 1: 次校正, 2: 已校正
//    bool reset_done = 0;
//    uint32_t i = 0 ; 
//    uint32_t j = 0 ;
//
//    int work_state = 0;
//
//
//    unsigned long oneshot_oldtime = 0;
//    unsigned long oneshot_newtime;
//    unsigned long oneshot_interval = 300;
//    bool up_trig,down_trig;
//    char action_signal;
//
//    sb_motor(void);
//    void motor_initial(int stepPin_in, int dirPin_in, int btn_in);
//    void motor_setup(uint32_t worktime_in, int sp_in);
//    void motor_reset_single(int stepPin, int dirPin,int btn);
//    void motor_up(int stepPin, int dirPin, char up_signal);
//    void motor_action(int stepPin, int dirPin, char action_signal);
//    void motor_down(int stepPin, int dirPin, char down_signal);
//    bool oneshot(int btn);
//  
//  };
#include "inttypes.h"
#include "stdio.h"

class sb_motor{
  private:

  public:
    int stepPin; 
    int dirPin;
    //int sleepPin;
    //int resetPin;
    int btn;
    int up_signal;
    const int testled = 13;
    uint32_t mstime ;
    uint32_t worktime;
    uint32_t time_now;
    uint32_t sp;
    bool flag;
    char motor_running;
    bool reset_ready;
    bool work_done;

    int motor_state = 0 ; //0: 未校正, 1: 次校正, 2: 已校正
    bool reset_done = 0;
    uint32_t i = 0 ; 
    uint32_t j = 0 ;

    int work_state = 0;


    unsigned long oneshot_oldtime = 0;
    unsigned long oneshot_newtime;
    unsigned long oneshot_interval = 300;
    bool up_trig,down_trig,return_trig;
    char action_signal;
    char action_array[6];
    char position_state = 'N';

    char current_cmd,old_cmd;

    sb_motor(void);
    void motor_initial(int stepPin_in, int dirPin_in, int btn_in);
    void motor_setup(uint32_t worktime_in, int sp_in);
    void motor_reset_single(int stepPin, int dirPin,int btn);
    void motor_up(void);
    void motor_action(int stepPin, int dirPin, char action_signal);
    void motor_down(void);
    bool oneshot(int btn);
    bool oneshot_signal(char sig);
    void motor_action_decode(char instr);
  };

