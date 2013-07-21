#include <crntsc.h>
#include <crpal.h>
#include <VGA.h>
#include <MDC.h>
#include "Sprites.h"

#define DEBUG 1

#define RESX 320
#define RESY 240

Mdc player1(2,3,4,5,6,9,7);
    
int x = 160,
    y = 120,
    last_x = 160,
    last_y = 120,
    last_col = 0b00000000,
    current_col = 1;
    
int current_frame = 0;
int o_left = 0;
int o_top = RESY - sonic[1];

unsigned char *character;

int get_frame_count(unsigned char sprite[])
{
  return sprite[2];
}
int get_width(unsigned char sprite[])
{
  return sprite[0];
}

void draw_sprite_at_frame(unsigned char sprite[],int current_frame,int o_left,int o_top){
  
  int w = sprite[0];
  int h = sprite[1];
  int count = sprite[2];
  
  int frame_offset = (w*h) * current_frame;

  for(int x = 0;x<w;x++){
   
     for(int y = 0;y<h;y++){
       
       int pixel_offset = (w * y) + x;
       int unpacked_pixel = 0;
       int packed_pixel = 0;
       int offset = frame_offset + pixel_offset;
       
       packed_pixel = sprite[3+(int)floor(offset/2)];
       
       if(offset % 2){
          unpacked_pixel = packed_pixel & 0xf;
       }
       else
       {
          unpacked_pixel = (packed_pixel >> 4) & 0xf;
       }

       if( unpacked_pixel != 0 ){
         VGA.putCPixelFast(o_left+x,o_top+y,sonic_palette[unpacked_pixel-1]);
       }
       else
       {
       int i = x+o_left;
       int j = y+o_top;
        //VGA.putCPixelFast(i,j,cat[(j*320) + i]);
        VGA.putCPixelFast(i,j,0);
       }
       
     } 
    
  }
}

void draw_color_table(){
    // Horizontal block of 4*8 pixels
  for(int c = 0;c < 8;c++){
    // 8 down
    for(int d = 0;d < 8;d++){
      // 4 across
      for(int a = 0;a < 4;a++){
         int x = (c*4) + a;
         int y = d;
         
         int offset = c*32;
        
         VGA.putCPixelFast(20+x,20+y,offset + (4*d) + a);
      }
    }
  }
}

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  while(!Serial)
    ;
    
    Serial.println("Hello World");
    
  //player1 =  Mdc(2,3,4,5,6,9,7);
    
    character = sonic;
    
  VGA.begin(RESX,RESY,VGA_COLOUR);

  for(int x = 0;x<RESX;x++){
   for(int y = 0;y<RESY;y++){
    VGA.putCPixelFast(x,y,backdrop[y*RESX + x]);
   } 
  }

  int colx = 0, coly = 0;
    
  VGA.drawPixel(x,y,0b10000010);
}

void loop(){

  player1.poll();
  
  if(player1.down(BTN_LEFT)){
    o_left--;
    character = sonic_left;
    if(o_left % 10 == 0){
      current_frame++;
    }  
  }
  if(player1.down(BTN_RIGHT)){
    o_left++;
    character = sonic;
    if(o_left % 10 == 0){
      current_frame++;
    }  
  }
  
  
  if( o_left > RESX+get_width(sonic) )
   {
     o_left = get_width(sonic);
   } 
  if( o_left < 0` ){
     o_left = RESX+get_width(sonic);
  }
  
  if(current_frame >= get_frame_count(sonic)){
    current_frame = 0; 
  }
  if(current_frame < 0){
    current_frame = get_frame_count(sonic);
  }
  
  draw_sprite_at_frame(character,current_frame,o_left,o_top);
  
  
  
  //delay(10);

  
  if(player1.down(BTN_UP)){
    y--;
  }
  if(player1.down(BTN_DOWN)){
    y++;
  }
  
  
  if(x>320) x=RESX;
  if(x<0) x=0;
  if(y>240) y=RESY;
  if(y<0) y=0;
  
  if(player1.pressed(BTN_B)) current_col++;
  if(player1.pressed(BTN_C)) current_col--;  
  
  if(current_col< 1) current_col = 1;
  if(current_col> 7) current_col = 1;
    
  if(player1.down(BTN_A)){
  
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
  
  if(player1.pressed(BTN_START) == 1){
    for(int i=0;i<RESX;i++){
      for(int j=0;j<RESY;j++){   
        VGA.drawPixel(i,j,0b00000000);
      }
    }
  }
  
  
  last_x = x;
  last_y = y;
  
}

/*
void loop() {
  delay(1);
  
  
  for(int y = 0;y<240;y++){
    
    int col = VGA.getCPixelFast(320,y);
    VGA.scroll(0,y,320,1,1,0,col);
    VGA.putCPixelFast(0,y,col);
    
  }
  
  
  int a_pressed = 0,
      b_pressed = 0,
      c_pressed = 0,
      start_pressed = 0;
  

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
}*/
