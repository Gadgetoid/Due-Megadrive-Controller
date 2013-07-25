/*
  Megadrive Controller Bridge
  for the Arduino Due

  Fudged together by Phil: github.com/gadgetoid

  This is a simple application to map
  a 3-button Megadrive (Genesis) controller
  to USB HID keyboard events.
  
  For best performance, you should turn off
  the serial debugging.
  
  This is the Megadrive controller pinout
  as seen from the front and back of a 
  9-pin d-sub connector.
  
  --- FRONT ---   ---- BACK ----
  
    1 2 3 4 5       5 4 3 2 1
  _____________   _____________
  \ 0 0 0 0 0 /   \ 0 0 0 0 0 /
   \_0_0_0_0_/     \_0_0_0_0_/
   
     6 7 8 9         9 8 7 6
     
  Use the right/back view when soldering,
  if you hold a 9-pin d-sub up and look at it
  from the side you solder to, this will be the
  pinout. It probably has numbers written on it anyway!
     
  Pin | Select == LOW | Select == HIGH
  1   | Up            | Up
  2   | Down          | Down
  3   | -             | Left
  4   | -             | Right
  5   | +5VDC         | +5VDC
  6   | Button A      | Button B
  7   | Select        | Select
  8   | Ground        | Ground
  9   | Start         | Button C
   
  Megadrive controller pinout:
  http://pinouts.ru/Game/genesiscontroller_pinout.shtml

  Library usage:

  Mdc player1(pin_up,pin_down,pin_left,pin_right,pin_ab,pin_startc,pin_select);

  void loop(){
    player1.poll();

    if( player1.pressed(BTN_A) ){
      // Jump!
    }

    if( player1.released(BTN_B) ){
      // Pow!
    }

    if( player1.down(BTN_RIGHT) ){
      // Whee!
    }
  }

*/

#include "Arduino.h"
#include "MDC.h"

Mdc::Mdc(int up, int down, int left, int right, int ab, int startc, int select){
  pin_up = up;
  pin_down = down;
  pin_left = left;
  pin_right = right;
  pin_ab = ab;
  pin_startc = startc;
  pin_select = select;
    
  pinMode(pin_up,INPUT);
  pinMode(pin_down,INPUT);
  pinMode(pin_left,INPUT);
  pinMode(pin_right,INPUT);
  pinMode(pin_ab,INPUT);
  pinMode(pin_startc,INPUT);

  pinMode(pin_select,OUTPUT);
  digitalWrite(pin_select,LOW);

  pressed_up    = false;
  pressed_down  = false;
  pressed_left  = false;
  pressed_right = false;
  pressed_a     = false;
  pressed_b     = false;
  pressed_c     = false;
  pressed_start = false;

  released_up    = false;
  released_down  = false;
  released_left  = false;
  released_right = false;
  released_a     = false;
  released_b     = false;
  released_c     = false;
  released_start = false;

  btn_up    = HIGH;
  btn_down  = HIGH;
  btn_left  = HIGH;
  btn_right = HIGH;
  btn_a     = HIGH;
  btn_b     = HIGH;
  btn_c     = HIGH;
  btn_start = HIGH;
  
  last_up    = HIGH;
  last_down  = HIGH;
  last_left  = HIGH;
  last_right = HIGH;
  last_a     = HIGH;
  last_b     = HIGH;
  last_c     = HIGH;
  last_start = HIGH;
};
boolean Mdc::down(char btn){
  switch(btn){
    case BTN_UP:
      return btn_up == LOW;
      break;
    case BTN_DOWN:
      return btn_down == LOW;
      break;
    case BTN_LEFT:
      return btn_left == LOW;
      break;
    case BTN_RIGHT:
      return btn_right == LOW;
      break;
    case BTN_A:
      return btn_a == LOW;
      break;
    case BTN_B:
      return btn_b == LOW;
      break;
    case BTN_C:
      return btn_c == LOW;
      break;
    case BTN_START:
      return btn_start == LOW;
      break;
  }
};
boolean Mdc::released(char btn){
  boolean state = false;
  switch(btn){
    case BTN_UP:
      state = released_up;
      released_up = false;
      break;
    case BTN_DOWN:
      state = released_down;
      released_down = false;
      break;
    case BTN_LEFT:
      state = released_left;
      released_left = false;
      break;
    case BTN_RIGHT:
      state = released_right;
      released_right = false;
      break;
    case BTN_A:
      state = released_a;
      released_a = false;
      break;
    case BTN_B:
      state = released_b;
      released_b = false;
      break;
    case BTN_C:
      state = released_c;
      released_c = false;
      break;
    case BTN_START:
      state = released_start;
      released_start = false;
      break;
  }
  return state;
}
boolean Mdc::pressed(char btn){
  boolean state = false;
  switch(btn){
    case BTN_UP:
      state = pressed_up;
      pressed_up = false;
      break;
    case BTN_DOWN:
      state = pressed_down;
      pressed_down = false;
      break;
    case BTN_LEFT:
      state = pressed_left;
      pressed_left = false;
      break;
    case BTN_RIGHT:
      state = pressed_right;
      pressed_right = false;
      break;
    case BTN_A:
      state = pressed_a;
      pressed_a = false;
      break;
    case BTN_B:
      state = pressed_b;
      pressed_b = false;
      break;
    case BTN_C:
      state = pressed_c;
      pressed_c = false;
      break;
    case BTN_START:
      state = pressed_start;
      pressed_start = false;
      break;
  }
  return state;
}
void Mdc::poll(){
  last_up    = btn_up;
  last_down  = btn_down;
  last_left  = btn_left;
  last_right = btn_right;
  last_a     = btn_a;
  last_b     = btn_b;
  last_c     = btn_c;
  last_start = btn_start;

  btn_up    = digitalRead(pin_up);
  btn_down  = digitalRead(pin_down);
  btn_a     = digitalRead(pin_ab);
  btn_start = digitalRead(pin_startc);
  
  digitalWrite(pin_select,HIGH);
  
  btn_left  = digitalRead(pin_left);
  btn_right = digitalRead(pin_right);
  btn_b     = digitalRead(pin_ab);
  btn_c     = digitalRead(pin_startc);
  
  digitalWrite(pin_select,LOW); 

  if(btn_up!=last_up && btn_up==HIGH){
    released_up = true;
  }
  if(btn_down!=last_down && btn_down==HIGH){
    released_down = true;
  }
  if(btn_left!=last_left && btn_left==HIGH){
    released_left = true;
  }
  if(btn_right!=last_right && btn_right==HIGH){
    released_right = true;
  }
  if(btn_a!=last_a && btn_a==HIGH){
    released_a = true;
  }
  if(btn_b!=last_b && btn_b==HIGH){
    released_b = true;
  }
  if(btn_c!=last_c && btn_c==HIGH){
    released_c = true;
  }
  if(btn_start!=last_start && btn_start==HIGH){
    released_start = true;
  }

  if(btn_up!=last_up && btn_up==LOW){
    pressed_up = true;
  }
  if(btn_down!=last_down && btn_down==LOW){
    pressed_down = true;
  }
  if(btn_left!=last_left && btn_left==LOW){
    pressed_left = true;
  }
  if(btn_right!=last_right && btn_right==LOW){
    pressed_right = true;
  }
  if(btn_a!=last_a && btn_a==LOW){
    pressed_a = true;
  }
  if(btn_b!=last_b && btn_b==LOW){
    pressed_b = true;
  }
  if(btn_c!=last_c && btn_c==LOW){
    pressed_c = true;
  }
  if(btn_start!=last_start && btn_start==LOW){
    pressed_start = true;
  }
}
