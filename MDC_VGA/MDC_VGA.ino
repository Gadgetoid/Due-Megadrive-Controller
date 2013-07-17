#include <crntsc.h>
#include <crpal.h>
#include <VGA.h>

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

*/

#define DEBUG 1

#define RESX 320
#define RESY 240

const int UP = 2,
          DOWN = 3,
          LEFT = 4,
          RIGHT = 5,
          AB = 6,
          STARTC = 9,
          SELECT = 7;
          
int btn_up = HIGH,
    btn_down = HIGH,
    btn_left = HIGH,
    btn_right = HIGH,
    btn_a = HIGH,
    btn_b = HIGH,
    btn_c = HIGH,
    btn_start = HIGH;
    
int last_up = HIGH,
    last_down = HIGH,
    last_left = HIGH,
    last_right = HIGH,
    last_a = HIGH,
    last_b = HIGH,
    last_c = HIGH,
    last_start = HIGH;
    
int x = 160,
    y = 120,
    last_x = 160,
    last_y = 120,
    last_col = 0b00000000,
    current_col = 1;
          
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  while(!Serial)
    ;
    
  VGA.begin(RESX,RESY,VGA_COLOUR);

  int colx = 0, coly = 0;

  for(int i=0;i<RESX;i++){
    for(int j=0;j<RESY;j++){   
      VGA.drawPixel(i,j,0b00000000);
    }
  }
  
  
  for(int x=0;x < 32;x++){
   for(int y = 0;y < 8;y++){
      VGA.drawPixel(x,y,(y*32) + x);
   } 
  }
  
  VGA.drawPixel(x,y,0b10000010);

  pinMode(UP,INPUT);
  pinMode(DOWN,INPUT);
  pinMode(LEFT,INPUT);
  pinMode(RIGHT,INPUT);
  pinMode(AB,INPUT);
  pinMode(STARTC,INPUT);

  pinMode(SELECT,OUTPUT);
  digitalWrite(SELECT,LOW);
}

void loop() {
  delay(1);
  
  int a_pressed = 0,
      b_pressed = 0,
      c_pressed = 0,
      start_pressed = 0;
  
  last_up = btn_up;
  last_down = btn_down;
  last_left = btn_left;
  last_right = btn_right;
  last_a = btn_a;
  last_b = btn_b;
  last_c = btn_c;
  last_start = btn_start;

  // put your main code here, to run repeatedly: 
  btn_up = digitalRead(UP);
  btn_down = digitalRead(DOWN);
  btn_a = digitalRead(AB);
  btn_start = digitalRead(STARTC);
  
  digitalWrite(SELECT,HIGH);
  
  btn_left = digitalRead(LEFT);
  btn_right = digitalRead(RIGHT);
  btn_b = digitalRead(AB);
  btn_c = digitalRead(STARTC);
  
  digitalWrite(SELECT,LOW); 

  if(btn_up != last_up){
    if(btn_up == LOW){
      Keyboard.press('w');
#ifdef DEBUG
      Serial.println("UP pressed");
#endif
    }else{
      Keyboard.release('w');
#ifdef DEBUG
      Serial.println("UP released");
#endif
    }
  }
  if(btn_down != last_down){
    if(btn_down == LOW){
      Keyboard.press('s');
#ifdef DEBUG
      Serial.println("DOWN pressed");
#endif
    }else{
      Keyboard.release('s');
#ifdef DEBUG
      Serial.println("DOWN released");
#endif
    } 
  }
  if(btn_left != last_left){
    if(btn_left == LOW){
      Keyboard.press('a');
#ifdef DEBUG
      Serial.println("LEFT pressed");
#endif
    }else{
      Keyboard.release('a');
#ifdef DEBUG
      Serial.println("LEFT released");
#endif
    } 
  }
  if(btn_right != last_right){
    if(btn_right == LOW){
      Keyboard.press('d');
#ifdef DEBUG
      Serial.println("RIGHT pressed");
#endif
    }else{
      Keyboard.release('d');
#ifdef DEBUG
      Serial.println("RIGHT released");
#endif
    } 
  }
  if(btn_a != last_a){
    if(btn_a == LOW){
      Keyboard.press('i');
#ifdef DEBUG
      Serial.println("A pressed");
#endif
    }else{
      Keyboard.release('i');
      a_pressed = 1;
#ifdef DEBUG
      Serial.println("A released");
#endif
    } 
  }
  if(btn_b != last_b){
    if(btn_b == LOW){
      Keyboard.press('o');
#ifdef DEBUG
      Serial.println("B pressed");
#endif
    }else{
      Keyboard.release('o');
      b_pressed = 1;
#ifdef DEBUG
      Serial.println("B released");
#endif
    } 
  }
  if(btn_c != last_c){
    if(btn_c == LOW){
      Keyboard.press('c');
#ifdef DEBUG
      Serial.println("C pressed");
#endif
    }else{
      Keyboard.release('c');
      c_pressed = 1;
#ifdef DEBUG
      Serial.println("C released");
#endif
    } 
  }
  if(btn_start != last_start){
    if(btn_start == LOW){
      Keyboard.press('u');
#ifdef DEBUG
      Serial.println("START pressed");
#endif
    }else{
      Keyboard.release('u');
      start_pressed = 1;
#ifdef DEBUG
      Serial.println("START released");
#endif
    } 
  }
  
  if(btn_left == LOW){
    x--;
  }
  if(btn_right == LOW){
    x++;
  }
  if(btn_up == LOW){
    y--;
  }
  if(btn_down == LOW){
    y++;
  }
  
  if(x>320) x=RESX;
  if(x<0) x=0;
  if(y>240) y=RESY;
  if(y<0) y=0;
  
  if(b_pressed) current_col++;
  if(c_pressed) current_col--;  
  
  if(current_col< 1) current_col = 1;
  if(current_col> 7) current_col = 1;
    
  if(btn_a == LOW){
  
    if(current_col == 1)
    {
      VGA.drawPixel(last_x,last_y,0b10000010);
      VGA.drawPixel(last_x-1,last_y,0b01000001);
      VGA.drawPixel(last_x+1,last_y,0b01000001);
    }else if(current_col == 2){
      VGA.drawPixel(last_x,last_y,  0b00010010);
      VGA.drawPixel(last_x-1,last_y,0b00001001);
      VGA.drawPixel(last_x+1,last_y,0b00001001);
    }else if(current_col == 3){
      VGA.drawPixel(last_x,last_y,  0b10010010);
      VGA.drawPixel(last_x-1,last_y,0b01001001);
      VGA.drawPixel(last_x+1,last_y,0b01001001);
    } else if(current_col == 4){
      VGA.drawPixel(last_x,last_y,  0b10010000);
      VGA.drawPixel(last_x-1,last_y,0b01001000);
      VGA.drawPixel(last_x+1,last_y,0b01001000);
    }  else if(current_col == 5){
      VGA.drawPixel(last_x,last_y,  0b10000000);
      VGA.drawPixel(last_x-1,last_y,0b01000000);
      VGA.drawPixel(last_x+1,last_y,0b01000000);
    }  else if(current_col == 6){
      VGA.drawPixel(last_x,last_y,  0b00010000);
      VGA.drawPixel(last_x-1,last_y,0b00001000);
      VGA.drawPixel(last_x+1,last_y,0b00001000);
    }   else if(current_col == 7){
      VGA.drawPixel(last_x,last_y,  0b10000000);
      VGA.drawPixel(last_x-1,last_y,0b00010000);
      VGA.drawPixel(last_x+1,last_y,0b00000010);
    }   
  
  }else{
    VGA.drawPixel(last_x,last_y,  last_col);
  }
  
  last_col = VGA.getCPixelFast(x,y);
  VGA.drawPixel(x,y,0b00010000);
  
  if(start_pressed == 1){
    for(int i=0;i<RESX;i++){
      for(int j=0;j<RESY;j++){   
        VGA.drawPixel(i,j,0b00000000);
      }
    }
  }
  
  
  last_x = x;
  last_y = y;
  delay(20);
}
