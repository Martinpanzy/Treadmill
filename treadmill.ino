#define PWM_PIN 10  // PWM signal
#define SLOPE_UP_PIN 9
#define SLOPE_DN_PIN 6
#define SLOPE 3
int state = 0;
int pwm = 0;

void parse_command(String command, int&pwm, int&state) {
  if(command[0] == 'p'){
    command.remove(0, 1);
    pwm = command.toInt();
    Serial.print("New PWM: "); Serial.println(pwm);
   }
   else if((command == "up") || (command == "UP")) {
    if(state == 1){
      digitalWrite(SLOPE_UP_PIN, HIGH);
      for(int i = 0; i < 4; i++){
        digitalWrite(SLOPE, HIGH);
        delay(310);
        digitalWrite(SLOPE, LOW);
        delay(310);
      }
     digitalWrite(SLOPE, HIGH);
     state = 0;
     digitalWrite(SLOPE_UP_PIN, LOW);
    }
    else{
      digitalWrite(SLOPE_UP_PIN, HIGH);
      for(int i = 0; i < 4; i++){
        digitalWrite(SLOPE, LOW);
        delay(310);
        digitalWrite(SLOPE, HIGH);
        delay(310);
      }
     digitalWrite(SLOPE, LOW);
     state = 1;
     digitalWrite(SLOPE_UP_PIN, LOW);
    }
   }
   else if((command == "dn") || (command == "DN")) {
    if(state == 1){
      digitalWrite(SLOPE_DN_PIN, HIGH);
      for(int i = 0; i < 4; i++){
        digitalWrite(SLOPE, HIGH);
        delay(310);
        digitalWrite(SLOPE, LOW);
        delay(310); 
      }
     digitalWrite(SLOPE, HIGH);
     state = 0;
     digitalWrite(SLOPE_DN_PIN, LOW);
    }
    else{
      digitalWrite(SLOPE_DN_PIN, HIGH);
      for(int i = 0; i < 4; i++){
        digitalWrite(SLOPE, LOW);
        delay(310);
        digitalWrite(SLOPE, HIGH);
        delay(310);
      }
     digitalWrite(SLOPE, LOW);
     state = 1;
     digitalWrite(SLOPE_DN_PIN, LOW);
    }
   }
}


void setup() {
  Serial.begin(9600);
  Serial.println("#############################################################################");
  Serial.println("#                                                                           #");
  Serial.println("#                              Treadmill Hack                               #");
  Serial.println("#                          Model: PRO-FORM 450 CX                           #");
  Serial.println("# Serial command:                                                           #");
  Serial.println("#   to set the slope of the treadmill:                                      #");
  Serial.println("#     send \"up\" or \"down\"                                                   #");
  Serial.println("#   to set new PWM value:                                                   #");
  Serial.println("#      send \"p<pwm>\", where \"<pwm>\" is an integer in the range of 0 to 49   #");
  Serial.println("#                                                                           #");
  Serial.println("#############################################################################");
  pinMode(PWM_PIN, OUTPUT);
  pinMode(SLOPE_UP_PIN, OUTPUT);
  pinMode(SLOPE_DN_PIN, OUTPUT);
  //pinMode(SLOPE, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    parse_command(Serial.readString(), pwm, state);
    }
    digitalWrite(PWM_PIN, HIGH);
    delay(pwm);
    digitalWrite(PWM_PIN, LOW);
    delay(49 - pwm);      
}
