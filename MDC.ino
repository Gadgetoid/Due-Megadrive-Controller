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
      Serial.println('UP pressed');
    }else{
      Keyboard.release('w');
      Serial.println('UP released');
    }
  }
  if(btn_down != last_down){
    if(btn_down == LOW){
      Keyboard.press('s');
      Serial.println('DOWN pressed');
    }else{
      Keyboard.release('s');
      Serial.println('DOWN released');
    } 
  }
  if(btn_left != last_left){
    if(btn_left == LOW){
      Keyboard.press('a');
      Serial.println('LEFT pressed');
    }else{
      Keyboard.release('a');
      Serial.println('LEFT released');
    } 
  }
  if(btn_right != last_right){
    if(btn_right == LOW){
      Keyboard.press('d');
      Serial.println('RIGHT pressed');
    }else{
      Keyboard.release('d');
      Serial.println('RIGHT released');
    } 
  }
  if(btn_a != last_a){
    if(btn_a == LOW){
      Keyboard.press('i');
      Serial.println('A pressed');
    }else{
      Keyboard.release('i');
      Serial.println('A released');
    } 
  }
  if(btn_b != last_b){
    if(btn_b == LOW){
      Keyboard.press('o');
      Serial.println('B pressed');
    }else{
      Keyboard.release('o');
      Serial.println('B released');
    } 
  }
  if(btn_c != last_c){
    if(btn_c == LOW){
      Keyboard.press('c');
      Serial.println('C pressed');
    }else{
      Keyboard.release('c');
      Serial.println('C released');
    } 
  }
  if(btn_start != last_start){
    if(btn_start == LOW){
      Keyboard.press('u');
      Serial.println('START pressed');
    }else{
      Keyboard.release('u');
      Serial.println('START released');
    } 
  }
}
