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

//#define DEBUG 1

const int UP = 31,
          DOWN = 32,
          LEFT = 33,
          RIGHT = 34,
          AB = 36,
          STARTC = 38,
          SELECT = 37;
          
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
          
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  while(!Serial)
    ;

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
#ifdef DEBUG
      Serial.println("START released");
#endif
    } 
  }
}
