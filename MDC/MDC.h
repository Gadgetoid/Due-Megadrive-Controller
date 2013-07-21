#include "Arduino.h"

#ifndef _MDC_H
#define _MDC_H 

/*
const int UP = 2,
          DOWN = 3,
          LEFT = 4,
          RIGHT = 5,
          AB = 6,
          STARTC = 9,
          SELECT = 7;
          
 */

#define BTN_STATE_UP   0
#define BTN_STATE_DOWN 1
#define BTN_UP         0
#define BTN_DOWN       1
#define BTN_LEFT       2
#define BTN_RIGHT      3
#define BTN_A          4
#define BTN_B          5
#define BTN_C          6
#define BTN_START      7

class Mdc
{
  public:
    Mdc(int up, int down, int left, int right, int ab, int startc, int select);
    boolean pressed(int button);
    boolean down(int button);
    void poll(); 
  private:
    int pin_up, pin_down, pin_left, pin_right, pin_ab, pin_startc, pin_select; 
    boolean pressed_up,
        pressed_down,
        pressed_left,
        pressed_right,
        pressed_a,
        pressed_b,
        pressed_c,
        pressed_start;
    int btn_up,
        btn_down,
        btn_left,
        btn_right,
        btn_a,
        btn_b,
        btn_c,
        btn_start;
    int last_up,
        last_down,
        last_left,
        last_right,
        last_a,
        last_b,
        last_c,
        last_start;
};

#endif