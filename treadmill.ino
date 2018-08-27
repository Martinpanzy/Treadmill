#define PWM_PIN 10  // PWM signal
#define SLOPE_UP_PIN 9 
#define SLOPE_DN_PIN 6
int pwm = 0;

void parse_command(String command, int&pwm){
  if(command[0] == 'p'){
    command.remove(0, 1);
    pwm = command.toInt();
    Serial.print("New PWM: "); Serial.println(pwm);
   }
   else if((command == "up") || (command == "UP")){
     Serial.print("Inclination Up");
     digitalWrite(SLOPE_UP_PIN, HIGH); //a 2.5-second high signal will be sent out from SLOPE_UP_PIN
     delay(2500);
     digitalWrite(SLOPE_UP_PIN, LOW);
   }
   else if((command == "dn") || (command == "DN")){
     Serial.print("Inclination Down");
     digitalWrite(SLOPE_DN_PIN, HIGH); //a 2.5-second high signal will be sent out from SLOPE_DN_PIN
     delay(2500);
     digitalWrite(SLOPE_DN_PIN, LOW);
   }
   else{
     Serial.print("Command is not recognized :( ");
   }
}


void setup(){
  Serial.begin(9600);
  Serial.println("#############################################################################");
  Serial.println("#                                                                           #");
  Serial.println("#                              Treadmill Hack                               #");
  Serial.println("#                          Model: PRO-FORM 450 CX                           #");
  Serial.println("# Serial command:                                                           #");
  Serial.println("#   to raise or lower the treadmill:                                        #");
  Serial.println("#      send \"up\" or \"dn\"                                                #");
  Serial.println("#   to set new PWM value:                                                   #");
  Serial.println("#      send \"p<pwm>\", where \"<pwm>\" is an integer in the range of 0 to 49   #");
  Serial.println("#                                                                           #");
  Serial.println("#############################################################################");
  pinMode(PWM_PIN, OUTPUT);
  pinMode(SLOPE_UP_PIN, OUTPUT);
  pinMode(SLOPE_DN_PIN, OUTPUT);
}

void loop(){
  if (Serial.available() > 0){
    parse_command(Serial.readString(), pwm);
    }
    digitalWrite(PWM_PIN, HIGH);
    delay(pwm);
    digitalWrite(PWM_PIN, LOW);
    delay(49 - pwm);      
}
