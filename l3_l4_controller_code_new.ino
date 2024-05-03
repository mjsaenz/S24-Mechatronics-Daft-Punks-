int RPWM_Output_1 = 11;
int LPWM_Output_1 = 10; 
int R_EN_1 = 13;
int L_EN_1 = 12;

int RPWM_Output_2 = 6; 
int LPWM_Output_2 = 5;
int R_EN_2 = 4;
int L_EN_2 = 3;

int DIR_1 = 9;
int PUL_1 = 8;

int DIR_2 = 7;
int PUL_2 = 2;

int stepper_pos_1 = 0;
int stepper_pos_2 = 0;

int stepper_frd_dir_1 = HIGH;
int stepper_frd_dir_2 = LOW;

int lin_act_time = 2000;

int forward_pos = 2000;
int backwards_pos = -2000;
int slow_frd_pos = 1000;
int slow_bkrd_pos = -1000;

// global variables for readSerial() to set
String userInput = "";
bool stringComplete = false;

void setup() {
  pinMode(DIR_1, OUTPUT); 
  pinMode(PUL_1, OUTPUT);
  pinMode(RPWM_Output_1, OUTPUT);
  pinMode(LPWM_Output_1, OUTPUT);
  pinMode(R_EN_1, OUTPUT);
  pinMode(L_EN_1, OUTPUT);
  pinMode(DIR_2, OUTPUT); 
  pinMode(PUL_2, OUTPUT);
  pinMode(RPWM_Output_2, OUTPUT);
  pinMode(LPWM_Output_2, OUTPUT);
  pinMode(R_EN_2, OUTPUT);
  pinMode(L_EN_2, OUTPUT);

  userInput.reserve(100);

  Serial.begin(115200); // Starts the serial communication

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(R_EN_1, LOW);
  digitalWrite(L_EN_1, LOW);
  digitalWrite(R_EN_2, LOW);
  digitalWrite(L_EN_2, LOW);
  readSerial();

  // commands:
  // extend 1: q
  // retract 1: w
  // extend 2: e
  // retract 2: r

  // forward step 1: t
  // backwards step 1: y
  // forwards step 2: u
  // backwards step 2: i
  // neutral 1: o
  // neutral 2: p

  // small forward step 1: a
  // small backwards step 1: s
  // small forwards step 2: d
  // small backwards step 2: f

  if(stringComplete){
    userInput.trim();
    if(userInput.equals("q")){
      // extend 1
      analogWrite(RPWM_Output_1, 0);
      analogWrite(LPWM_Output_1, 255);
      digitalWrite(R_EN_1, HIGH);
      digitalWrite(L_EN_1, HIGH);
      delay(lin_act_time);
    } else if(userInput.equals("w")){
      // retract 1
      analogWrite(RPWM_Output_1, 255);
      analogWrite(LPWM_Output_1, 0);
      digitalWrite(R_EN_1, HIGH);
      digitalWrite(L_EN_1, HIGH);
      delay(lin_act_time);
    } else if(userInput.equals("e")){
      // extend 2
      analogWrite(RPWM_Output_2, 0);
      analogWrite(LPWM_Output_2, 255);
      digitalWrite(R_EN_2, HIGH);
      digitalWrite(L_EN_2, HIGH);
      delay(lin_act_time);
    } else if (userInput.equals("r")){
      // retract 2
      analogWrite(RPWM_Output_2, 255);
      analogWrite(LPWM_Output_2, 0);
      digitalWrite(R_EN_2, HIGH);
      digitalWrite(L_EN_2, HIGH);
      delay(lin_act_time);
    } else if (userInput.equals("t")){
      // forward step 1
      digitalWrite(DIR_1, stepper_frd_dir_1);
      while((stepper_pos_1 < forward_pos)){
        digitalWrite(PUL_1, HIGH);
        delayMicroseconds(50);
        digitalWrite(PUL_1, LOW);
        delayMicroseconds(500);
        stepper_pos_1++;
      }
    } else if (userInput.equals("y")){
      // backwards step 1
      digitalWrite(DIR_1, !stepper_frd_dir_1);
      while((stepper_pos_1 > backwards_pos)){
        digitalWrite(PUL_1, HIGH);
        delayMicroseconds(50);
        digitalWrite(PUL_1, LOW);
        delayMicroseconds(500);
        stepper_pos_1--;
      }
    } else if (userInput.equals("u")){
      // forward step 2
      digitalWrite(DIR_2, stepper_frd_dir_2);
      while((stepper_pos_2 < forward_pos)){
        digitalWrite(PUL_2, HIGH);
        delayMicroseconds(50);
        digitalWrite(PUL_2, LOW);
        delayMicroseconds(500);
        stepper_pos_2++;
      }
    } else if (userInput.equals("i")){
      // backwards step 2
      digitalWrite(DIR_2, !stepper_frd_dir_2);
      while((stepper_pos_2 > backwards_pos)){
        digitalWrite(PUL_2, HIGH);
        delayMicroseconds(50);
        digitalWrite(PUL_2, LOW);
        delayMicroseconds(500);
        stepper_pos_2--;
      }
    } else if (userInput.equals("o")){
      // neutral 1
      if ((stepper_pos_1 > 0)){
        digitalWrite(DIR_1, !stepper_frd_dir_1);
        while((stepper_pos_1 > 0)){
          digitalWrite(PUL_1, HIGH);
          delayMicroseconds(50);
          digitalWrite(PUL_1, LOW);
          delayMicroseconds(500);
          stepper_pos_1--;
        }
      } else if ((stepper_pos_1 < 0)) {
        digitalWrite(DIR_1, stepper_frd_dir_1);
        while((stepper_pos_1 < 0)){
          digitalWrite(PUL_1, HIGH);
          delayMicroseconds(50);
          digitalWrite(PUL_1, LOW);
          delayMicroseconds(500);
          stepper_pos_1++;
        }
      } 
    } else if (userInput.equals("p")){
      // neutral 2
      if ((stepper_pos_2 > 0)){
        digitalWrite(DIR_2, !stepper_frd_dir_2);
        while((stepper_pos_2 > 0)){
          digitalWrite(PUL_2, HIGH);
          delayMicroseconds(50);
          digitalWrite(PUL_2, LOW);
          delayMicroseconds(500);
          stepper_pos_2--;
        }
      } else if ((stepper_pos_2 < 0)) {
        digitalWrite(DIR_2, stepper_frd_dir_2);
        while((stepper_pos_2 < 0)){
          digitalWrite(PUL_2, HIGH);
          delayMicroseconds(50);
          digitalWrite(PUL_2, LOW);
          delayMicroseconds(500);
          stepper_pos_2++;
        }
      }
    } else if (userInput.equals("a")){
      // small forward step 1
      digitalWrite(DIR_1, stepper_frd_dir_1);
      while((stepper_pos_1 < slow_frd_pos)){
        digitalWrite(PUL_1, HIGH);
        delayMicroseconds(50);
        digitalWrite(PUL_1, LOW);
        delayMicroseconds(500);
        stepper_pos_1++;
      }
    } else if (userInput.equals("s")){
      // small backwards step 1
      digitalWrite(DIR_1, !stepper_frd_dir_1);
      while((stepper_pos_1 > slow_bkrd_pos)){
        digitalWrite(PUL_1, HIGH);
        delayMicroseconds(50);
        digitalWrite(PUL_1, LOW);
        delayMicroseconds(500);
        stepper_pos_1--;
      }
    } else if (userInput.equals("d")){
      // small forwards step 2
      digitalWrite(DIR_2, stepper_frd_dir_2);
      while((stepper_pos_2 < slow_frd_pos)){
        digitalWrite(PUL_2, HIGH);
        delayMicroseconds(50);
        digitalWrite(PUL_2, LOW);
        delayMicroseconds(500);
        stepper_pos_2++;
      }
    } else if (userInput.equals("f")){
      // small backwards step 2
      digitalWrite(DIR_2, !stepper_frd_dir_2);
      while((stepper_pos_2 > slow_bkrd_pos)){
        digitalWrite(PUL_2, HIGH);
        delayMicroseconds(50);
        digitalWrite(PUL_2, LOW);
        delayMicroseconds(500);
        stepper_pos_2--;
      }
    } else {
      digitalWrite(R_EN_1, LOW);
      digitalWrite(L_EN_1, LOW);
      digitalWrite(R_EN_2, LOW);
      digitalWrite(L_EN_2, LOW);
    }
    stringComplete = false;
    userInput = "";
  } else {
    digitalWrite(R_EN_1, LOW);
    digitalWrite(L_EN_1, LOW);
    digitalWrite(R_EN_2, LOW);
    digitalWrite(L_EN_2, LOW);
  }

}


// example from Christian's Microcontroller lecture
// read from serial in a non-blocking manner
void readSerial(){
  if (Serial.available()){
    char inChar = (char)Serial.read();
    userInput += inChar;
    if (inChar == '\n'){
      stringComplete = true;
    }
  }
}